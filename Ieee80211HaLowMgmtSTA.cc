/*
 * Ieee80211HaLowMgmtSTA.cc
 *
 *  Created on: 21-Jan-2017
 *      Author: KAUSHIK NAGARAJAN
 */


//#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.h"

#include "inet/physicallayer/contract/packetlevel/IRadioMedium.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/common/NotifierConsts.h"
#include "inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h"
#include "inet/physicallayer/ieee80211/packetlevel/Ieee80211ControlInfo_m.h"
#include "inet/common/INETUtils.h"
#include "Ieee80211HaLowMgmtSTA.h"






namespace inet {

namespace ieee80211 {

using namespace physicallayer;

//TBD supportedRates!
//TBD use command msg kinds?
//TBD implement bitrate switching (Radio already supports it)
//TBD where to put LCC header (SNAP)..?
//TBD mac should be able to signal when msg got transmitted

Define_Module(Ieee80211HaLowMgmtSTA);

// message kind values for timers
#define MK_AUTH_TIMEOUT           1
#define MK_ASSOC_TIMEOUT          2
#define MK_SCAN_SENDPROBE         3
#define MK_SCAN_MINCHANNELTIME    4
#define MK_SCAN_MAXCHANNELTIME    5
#define MK_BEACON_TIMEOUT         6

#define MAX_BEACONS_MISSED        3.5  // beacon lost timeout, in beacon intervals (doesn't need to be integer)





void Ieee80211HaLowMgmtSTA::initialize(int stage)
{
    Ieee80211MgmtBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        isScanning = false;
        isAssociated = false;
        assocTimeoutMsg = nullptr;
        myIface = nullptr;
        numChannels = par("numChannels");

        host = getContainingNode(this);
        host->subscribe(NF_LINK_FULL_PROMISCUOUS, this);

        WATCH(isScanning);
        WATCH(isAssociated);

        WATCH(scanning);
        WATCH(assocAP);
        WATCH_LIST(apList);
    }
    else if (stage == INITSTAGE_LINK_LAYER_2) {
        IInterfaceTable *ift = findModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        if (ift) {
            myIface = ift->getInterfaceByName(utils::stripnonalnum(findModuleUnderContainingNode(this)->getFullName()).c_str());
        }
    }
}




void Ieee80211HaLowMgmtSTA::handleTimer(cMessage *msg)
{
    if (msg->getKind() == MK_AUTH_TIMEOUT) {
        // authentication timed out
        APInfo *ap = (APInfo *)msg->getContextPointer();
        EV << "Authentication timed out, AP address = " << ap->address << "\n";

        // send back failure report to agent
        sendAuthenticationConfirm(ap, PRC_TIMEOUT);
    }
    else if (msg->getKind() == MK_ASSOC_TIMEOUT) {
        // association timed out
        APInfo *ap = (APInfo *)msg->getContextPointer();
        EV << "Association timed out, AP address = " << ap->address << "\n";

        // send back failure report to agent
        sendAssociationConfirm(ap, PRC_TIMEOUT);
    }
    else if (msg->getKind() == MK_SCAN_MAXCHANNELTIME) {
        // go to next channel during scanning
        bool done = scanNextChannel();
        if (done)
            sendScanConfirm(); // send back response to agents' "scan" command
        delete msg;
    }
    else if (msg->getKind() == MK_SCAN_SENDPROBE) {
        // Active Scan: send a probe request, then wait for minChannelTime (11.1.3.2.2)
        delete msg;
        sendProbeRequest();
        cMessage *timerMsg = new cMessage("minChannelTime", MK_SCAN_MINCHANNELTIME);
        scheduleAt(simTime() + scanning.minChannelTime, timerMsg);    //XXX actually, we should start waiting after ProbeReq actually got transmitted
    }
    else if (msg->getKind() == MK_SCAN_MINCHANNELTIME) {
        // Active Scan: after minChannelTime, possibly listen for the remaining time until maxChannelTime
        delete msg;
        if (scanning.busyChannelDetected) {
            EV << "Busy channel detected during minChannelTime, continuing listening until maxChannelTime elapses\n";
            cMessage *timerMsg = new cMessage("maxChannelTime", MK_SCAN_MAXCHANNELTIME);
            scheduleAt(simTime() + scanning.maxChannelTime - scanning.minChannelTime, timerMsg);
        }
        else {
            EV << "Channel was empty during minChannelTime, going to next channel\n";
            bool done = scanNextChannel();
            if (done)
                sendScanConfirm(); // send back response to agents' "scan" command
        }
    }
    else if (msg->getKind() == MK_BEACON_TIMEOUT) {
        // missed a few consecutive beacons
        beaconLost();
    }
    else {
        throw cRuntimeError("internal error: unrecognized timer '%s'", msg->getName());
    }



}


void Ieee80211HaLowMgmtSTA::handleUpperMessage(cPacket *msg)
{
    if (!isAssociated || assocAP.address.isUnspecified()) {
        EV << "STA is not associated with an access point, discarding packet" << msg << "\n";
        delete msg;
        return;
    }

    Ieee80211DataFrame *frame = encapsulate(msg);
    sendDown(frame);
}

void Ieee80211HaLowMgmtSTA::handleCommand(int msgkind, cObject *ctrl)
{
    if (dynamic_cast<Ieee80211Prim_ScanRequest *>(ctrl))
        processScanCommand((Ieee80211Prim_ScanRequest *)ctrl);
    else if (dynamic_cast<Ieee80211Prim_AuthenticateRequest *>(ctrl))
        processAuthenticateCommand((Ieee80211Prim_AuthenticateRequest *)ctrl);
    else if (dynamic_cast<Ieee80211Prim_DeauthenticateRequest *>(ctrl))
        processDeauthenticateCommand((Ieee80211Prim_DeauthenticateRequest *)ctrl);
    else if (dynamic_cast<Ieee80211Prim_AssociateRequest *>(ctrl))
        processAssociateCommand((Ieee80211Prim_AssociateRequest *)ctrl);
    else if (dynamic_cast<Ieee80211Prim_ReassociateRequest *>(ctrl))
        processReassociateCommand((Ieee80211Prim_ReassociateRequest *)ctrl);
    else if (dynamic_cast<Ieee80211Prim_DisassociateRequest *>(ctrl))
        processDisassociateCommand((Ieee80211Prim_DisassociateRequest *)ctrl);
    else if (ctrl)
        throw cRuntimeError("handleCommand(): unrecognized control info class `%s'", ctrl->getClassName());
    else
        throw cRuntimeError("handleCommand(): control info is nullptr");
    delete ctrl;
}


Ieee80211DataFrame *Ieee80211HaLowMgmtSTA::encapsulate(cPacket *msg)
{
    Ieee80211DataFrameWithSNAP *frame = new Ieee80211DataFrameWithSNAP(msg->getName());

    // frame goes to the AP
    frame->setToDS(true);

    // receiver is the AP
    frame->setReceiverAddress(assocAP.address);

    // destination address is in address3
    Ieee802Ctrl *ctrl = check_and_cast<Ieee802Ctrl *>(msg->removeControlInfo());
    frame->setAddress3(ctrl->getDest());
    frame->setEtherType(ctrl->getEtherType());
    int up = ctrl->getUserPriority();
    if (up >= 0) {
        // make it a QoS frame, and set TID
        frame->setType(ST_DATA_WITH_QOS);
        frame->addBitLength(QOSCONTROL_BITS);
        frame->setTid(up);
    }
    delete ctrl;

    frame->encapsulate(msg);
    return frame;
}

cPacket *Ieee80211HaLowMgmtSTA::decapsulate(Ieee80211DataFrame *frame)
{
    cPacket *payload = frame->decapsulate();

    Ieee802Ctrl *ctrl = new Ieee802Ctrl();
    ctrl->setSrc(frame->getAddress3());
    ctrl->setDest(frame->getReceiverAddress());
    if (frame->getType() == ST_DATA_WITH_QOS) {
        int tid = frame->getTid();
        if (tid < 8)
            ctrl->setUserPriority(tid); // TID values 0..7 are UP
    }
    Ieee80211DataFrameWithSNAP *frameWithSNAP = dynamic_cast<Ieee80211DataFrameWithSNAP *>(frame);
    if (frameWithSNAP)
        ctrl->setEtherType(frameWithSNAP->getEtherType());
    payload->setControlInfo(ctrl);

    delete frame;
    return payload;
}


Ieee80211HaLowMgmtSTA::APInfo *Ieee80211HaLowMgmtSTA::lookupAP(const MACAddress& address)
{
    for (auto & elem : apList)
        if (elem.address == address)
            return &(elem);

    return nullptr;
}
void Ieee80211HaLowMgmtSTA::clearAPList()
{
    for (auto & elem : apList)
        if (elem.authTimeoutMsg)
            delete cancelEvent(elem.authTimeoutMsg);

    apList.clear();
}


void Ieee80211HaLowMgmtSTA::receiveSignal(cComponent *source, simsignal_t signalID, long value DETAILS_ARG)
{
    Enter_Method_Silent();
    // Note that we are only subscribed during scanning!
    if (signalID == IRadio::receptionStateChangedSignal) {
        IRadio::ReceptionState newReceptionState = (IRadio::ReceptionState)value;
        if (newReceptionState != IRadio::RECEPTION_STATE_UNDEFINED && newReceptionState != IRadio::RECEPTION_STATE_IDLE) {
            EV << "busy radio channel detected during scanning\n";
            scanning.busyChannelDetected = true;
        }
    }
}

void Ieee80211HaLowMgmtSTA::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj DETAILS_ARG)
{
    Enter_Method_Silent();
    printNotificationBanner(signalID, obj);

    // Note that we are only subscribed during scanning!
    if (signalID == NF_LINK_FULL_PROMISCUOUS) {
        Ieee80211DataOrMgmtFrame *frame = dynamic_cast<Ieee80211DataOrMgmtFrame *>(obj);
        if (!frame || frame->getControlInfo() == nullptr)
            return;
        if (frame->getType() != ST_BEACON)
            return;
        Ieee80211ReceptionIndication *ctl = dynamic_cast<Ieee80211ReceptionIndication *>(frame->getControlInfo());
        if (ctl == nullptr)
            return;
        Ieee80211HaLowBeaconFrame *beacon = (check_and_cast<Ieee80211HaLowBeaconFrame *>(frame));
        APInfo *ap = lookupAP(beacon->getTransmitterAddress());
        if (ap)
            ap->rxPower = ctl->getRecPow();
    }
}


void Ieee80211HaLowMgmtSTA::handleAssociationResponseFrame(Ieee80211HaLowAssociationResponseFrame *frame)
{
    EV << "Received Association Response frame\n";

    if (!assocTimeoutMsg) {
        EV << "No association in progress, ignoring frame\n";
        delete frame;
        return;
    }

    // extract frame contents
    MACAddress address = frame->getTransmitterAddress();
    int statusCode = frame->getBody().getStatusCode();
    //XXX short aid;
    //XXX Ieee80211SupportedRatesElement supportedRates;
    delete frame;

    // look up AP data structure
    APInfo *ap = lookupAP(address);
    if (!ap)
        throw cRuntimeError("handleAssociationResponseFrame: AP not known: address=%s", address.str().c_str());

    if (isAssociated) {
        EV << "Breaking existing association with AP address=" << assocAP.address << "\n";
        isAssociated = false;
        delete cancelEvent(assocAP.beaconTimeoutMsg);
        assocAP.beaconTimeoutMsg = nullptr;
        assocAP = AssociatedAPInfo();
    }

    delete cancelEvent(assocTimeoutMsg);
    assocTimeoutMsg = nullptr;

    if (statusCode != SC_SUCCESSFUL) {
        EV << "Association failed with AP address=" << ap->address << "\n";
    }
    else {
        EV << "Association successful, AP address=" << ap->address << "\n";

        // change our state to "associated"
        isAssociated = true;
        AssociationValue = frame->getBody().getassociationID();
        (APInfo&)assocAP = (*ap);

        emit(NF_L2_ASSOCIATED, myIface);

        assocAP.beaconTimeoutMsg = new cMessage("beaconTimeout", MK_BEACON_TIMEOUT);
        scheduleAt(simTime() + MAX_BEACONS_MISSED * assocAP.beaconInterval, assocAP.beaconTimeoutMsg);
    }

    // report back to agent
    sendAssociationConfirm(ap, statusCodeToPrimResultCode(statusCode));
}

void Ieee80211HaLowMgmtSTA::sendAssociationConfirm(APInfo *ap, int resultCode)
{
    sendConfirm(new Ieee80211Prim_AssociateConfirm(), resultCode);
}

void Ieee80211HaLowMgmtSTA::sendConfirm(Ieee80211PrimConfirm *confirm, int resultCode)
{
    confirm->setResultCode(resultCode);
    cMessage *msg = new cMessage(confirm->getClassName());
    msg->setControlInfo(confirm);
    send(msg, "agentOut");
}


void Ieee80211HaLowMgmtSTA::startAuthentication(APInfo *ap, simtime_t timeout)
{
    if (ap->authTimeoutMsg)
        throw cRuntimeError("startAuthentication: authentication currently in progress with AP address=", ap->address.str().c_str());
    if (ap->isAuthenticated)
        throw cRuntimeError("startAuthentication: already authenticated with AP address=", ap->address.str().c_str());

    changeChannel(ap->channel);

    EV << "Sending initial Authentication frame with seqNum=1\n";

    // create and send first authentication frame
    Ieee80211HaLowAuthenticationFrame *frame = new Ieee80211HaLowAuthenticationFrame("Auth");
    frame->getBody().setSequenceNumber(1);
    //XXX frame length could be increased to account for challenge text length etc.
    sendManagementFrame(frame, ap->address);

    ap->authSeqExpected = 2;

    // schedule timeout
    ASSERT(ap->authTimeoutMsg == nullptr);
    ap->authTimeoutMsg = new cMessage("authTimeout", MK_AUTH_TIMEOUT);
    ap->authTimeoutMsg->setContextPointer(ap);
    scheduleAt(simTime() + timeout, ap->authTimeoutMsg);
}


void Ieee80211HaLowMgmtSTA::startAssociation(APInfo *ap, simtime_t timeout)
{
    if (isAssociated || assocTimeoutMsg)
        throw cRuntimeError("startAssociation: already associated or association currently in progress");
    if (!ap->isAuthenticated)
        throw cRuntimeError("startAssociation: not yet authenticated with AP address=", ap->address.str().c_str());

    // switch to that channel
    changeChannel(ap->channel);

    // create and send association request
    Ieee80211HaLowAssociationRequestFrame *frame = new Ieee80211HaLowAssociationRequestFrame("Assoc");

    //XXX set the following too?
    // string SSID
    // Ieee80211SupportedRatesElement supportedRates;

    sendManagementFrame(frame, ap->address);

    // schedule timeout
    ASSERT(assocTimeoutMsg == nullptr);
    assocTimeoutMsg = new cMessage("assocTimeout", MK_ASSOC_TIMEOUT);
    assocTimeoutMsg->setContextPointer(ap);
    scheduleAt(simTime() + timeout, assocTimeoutMsg);
}


void Ieee80211HaLowMgmtSTA::sendProbeRequest()
{
    EV << "Sending Probe Request, BSSID=" << scanning.bssid << ", SSID=\"" << scanning.ssid << "\"\n";
    Ieee80211HaLowProbeRequestFrame *frame = new Ieee80211HaLowProbeRequestFrame("ProbeReq");
    frame->getBody().setSSID(scanning.ssid.c_str());
    sendManagementFrame(frame, scanning.bssid);
}


void Ieee80211HaLowMgmtSTA::handleAuthenticationFrame(Ieee80211HaLowAuthenticationFrame *frame)
{
    MACAddress address = frame->getTransmitterAddress();
    int frameAuthSeq = frame->getBody().getSequenceNumber();
    EV << "Received Authentication frame from address=" << address << ", seqNum=" << frameAuthSeq << "\n";

    APInfo *ap = lookupAP(address);
    if (!ap) {
        EV << "AP not known, discarding authentication frame\n";
        delete frame;
        return;
    }

    // what if already authenticated with AP
    if (ap->isAuthenticated) {
        EV << "AP already authenticated, ignoring frame\n";
        delete frame;
        return;
    }

    // is authentication is in progress with this AP?
    if (!ap->authTimeoutMsg) {
        EV << "No authentication in progress with AP, ignoring frame\n";
        delete frame;
        return;
    }

    // check authentication sequence number is OK
    if (frameAuthSeq != ap->authSeqExpected) {
        // wrong sequence number: send error and return
        EV << "Wrong sequence number, " << ap->authSeqExpected << " expected\n";
        Ieee80211HaLowAuthenticationFrame *resp = new Ieee80211HaLowAuthenticationFrame("Auth-ERROR");
        resp->getBody().setStatusCode(SC_AUTH_OUT_OF_SEQ);
        sendManagementFrame(resp, frame->getTransmitterAddress());
        delete frame;

        // cancel timeout, send error to agent
        delete cancelEvent(ap->authTimeoutMsg);
        ap->authTimeoutMsg = nullptr;
        sendAuthenticationConfirm(ap, PRC_REFUSED);    //XXX or what resultCode?
        return;
    }

    // check if more exchanges are needed for auth to be complete
    int statusCode = frame->getBody().getStatusCode();

    if (statusCode == SC_SUCCESSFUL && !frame->getBody().getIsLast()) {
        EV << "More steps required, sending another Authentication frame\n";

        // more steps required, send another Authentication frame
        Ieee80211HaLowAuthenticationFrame *resp = new Ieee80211HaLowAuthenticationFrame("Auth");
        resp->getBody().setSequenceNumber(frameAuthSeq + 1);
        resp->getBody().setStatusCode(SC_SUCCESSFUL);
        // XXX frame length could be increased to account for challenge text length etc.
        sendManagementFrame(resp, address);
        ap->authSeqExpected += 2;
    }
    else {
        if (statusCode == SC_SUCCESSFUL)
            EV << "Authentication successful\n";
        else
            EV << "Authentication failed\n";

        // authentication completed
        ap->isAuthenticated = (statusCode == SC_SUCCESSFUL);
        delete cancelEvent(ap->authTimeoutMsg);
        ap->authTimeoutMsg = nullptr;
        sendAuthenticationConfirm(ap, statusCodeToPrimResultCode(statusCode));
    }

    delete frame;
}

void Ieee80211HaLowMgmtSTA::handleDeauthenticationFrame(Ieee80211HaLowDeauthenticationFrame *frame)
{
    EV << "Received Deauthentication frame\n";
    const MACAddress& address = frame->getAddress3();    // source address
    APInfo *ap = lookupAP(address);
    if (!ap || !ap->isAuthenticated) {
        EV << "Unknown AP, or not authenticated with that AP -- ignoring frame\n";
        delete frame;
        return;
    }
    if (ap->authTimeoutMsg) {
        delete cancelEvent(ap->authTimeoutMsg);
        ap->authTimeoutMsg = nullptr;
        EV << "Cancelling pending authentication\n";
        delete frame;
        return;
    }

    EV << "Setting isAuthenticated flag for that AP to false\n";
    ap->isAuthenticated = false;
    delete frame;
}

void Ieee80211HaLowMgmtSTA::handleAssociationRequestFrame(Ieee80211HaLowAssociationRequestFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211HaLowMgmtSTA::handleReassociationRequestFrame(Ieee80211HaLowReassociationRequestFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211HaLowMgmtSTA::handleReassociationResponseFrame(Ieee80211HaLowReassociationResponseFrame *frame)
{
    EV << "Received Reassociation Response frame\n";
    //TBD handle with the same code as Association Response?
}

void Ieee80211HaLowMgmtSTA::handleDisassociationFrame(Ieee80211HaLowDisassociationFrame *frame)
{
    EV << "Received Disassociation frame\n";
    const MACAddress& address = frame->getAddress3();    // source address

    if (assocTimeoutMsg) {
        // pending association
        delete cancelEvent(assocTimeoutMsg);
        assocTimeoutMsg = nullptr;
    }
    if (!isAssociated || address != assocAP.address) {
        EV << "Not associated with that AP -- ignoring frame\n";
        delete frame;
        return;
    }

    EV << "Setting isAssociated flag to false\n";
    isAssociated = false;
    delete cancelEvent(assocAP.beaconTimeoutMsg);
    assocAP.beaconTimeoutMsg = nullptr;
}


void Ieee80211HaLowMgmtSTA::handleBeaconFrame(Ieee80211HaLowBeaconFrame *frame)
{
    EV << "Received Beacon frame\n";
    storeAPInfo(frame->getTransmitterAddress(), frame->getBody());

    // if it is out associate AP, restart beacon timeout
    if (isAssociated && frame->getTransmitterAddress() == assocAP.address) {
        EV << "Beacon is from associated AP, restarting beacon timeout timer\n";
        ASSERT(assocAP.beaconTimeoutMsg != nullptr);
        cancelEvent(assocAP.beaconTimeoutMsg);
        scheduleAt(simTime() + MAX_BEACONS_MISSED * assocAP.beaconInterval, assocAP.beaconTimeoutMsg);

        //APInfo *ap = lookupAP(frame->getTransmitterAddress());
        //ASSERT(ap!=nullptr);
    }

    delete frame;
}

void Ieee80211HaLowMgmtSTA::handleProbeRequestFrame(Ieee80211HaLowProbeRequestFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211HaLowMgmtSTA::handleProbeResponseFrame(Ieee80211HaLowProbeResponseFrame *frame)
{
    EV << "Received Probe Response frame\n";
    storeAPInfo(frame->getTransmitterAddress(), frame->getBody());
    delete frame;
}


}
}
