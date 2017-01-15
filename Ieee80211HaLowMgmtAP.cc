/*
 * Ieee80211HaLowMgmtAP.cc

 *
 *  Created on: 19-Dec-2016
 *      Author: KAUSHIK NAGARAJAN
 */

#include "Ieee80211HaLowMgmtAP.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"
#include "Ieee80211HaLowMgmtFrames_m.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/physicallayer/ieee80211/packetlevel/Ieee80211Radio.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/NotifierConsts.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h"

#define TIMcount 8


namespace inet {



namespace ieee80211 {



using namespace physicallayer;

Define_Module(Ieee80211HaLowMgmtAP);
Register_Class(Ieee80211HaLowMgmtAP::NotificationInfoSta);

void Ieee80211HaLowMgmtAP::handleTimer(cMessage *msg)
{
    if (msg == beaconTimer) {
        sendBeacon();
        scheduleAt(simTime() + beaconInterval, beaconTimer);
    }
    else {
        throw cRuntimeError("internal error: unrecognized timer '%s'", msg->getName());
    }
}

void Ieee80211HaLowMgmtAP::handleUpperMessage(cPacket *msg)
{
    Ieee80211DataFrame *frame = encapsulate(msg);
    MACAddress macAddr = frame->getReceiverAddress();
    if (!macAddr.isMulticast()) {
        auto it = staList.find(macAddr);
        if (it == staList.end() || it->second.status != ASSOCIATED) {
            EV << "STA with MAC address " << macAddr << " not associated with this AP, dropping frame\n";
            delete frame;    // XXX count drops?
            return;
        }
    }

    sendDown(frame);
}

void Ieee80211HaLowMgmtAP::handleCommand(int msgkind, cObject *ctrl)
{
    throw cRuntimeError("handleCommand(): no commands supported");
}

void Ieee80211HaLowMgmtAP::receiveSignal(cComponent *source, simsignal_t signalID, long value DETAILS_ARG)
{
    Enter_Method_Silent();
    if (signalID == Ieee80211Radio::radioChannelChangedSignal) {
        EV << "updating channel number\n";
        channelNumber = value;
    }
}



Ieee80211HaLowMgmtAP::HaLowSTAInfo *Ieee80211HaLowMgmtAP::lookupHaLowSenderSTA(Ieee80211ManagementFrame *frame)
{
    auto it = staList.find(frame->getTransmitterAddress());
    return it == staList.end() ? nullptr : &(it->second);
    //EV << "CompleteInfo" << HaLowSTAInfo  << "\n" ;
}

void Ieee80211HaLowMgmtAP::sendManagementFrame(Ieee80211ManagementFrame *frame, const MACAddress& destAddr)
{
    frame->setFromDS(true);
    frame->setReceiverAddress(destAddr);
    frame->setAddress3(myAddress);
    sendDown(frame);
}

void Ieee80211HaLowMgmtAP::sendAssocNotification(const MACAddress& addr)
{
    NotificationInfoSta notif;
    notif.setApAddress(myAddress);
    notif.setStaAddress(addr);
    emit(NF_L2_AP_ASSOCIATED, &notif);
}

void Ieee80211HaLowMgmtAP::sendDisAssocNotification(const MACAddress& addr)
{
    NotificationInfoSta notif;
    notif.setApAddress(myAddress);
    notif.setStaAddress(addr);
    emit(NF_L2_AP_DISASSOCIATED, &notif);
}

void Ieee80211HaLowMgmtAP :: handleAuthenticationFrame(Ieee80211AuthenticationFrame *frame)
{
    static int STAcount = 0;
    int frameAuthSeq = frame->getBody().getSequenceNumber();
        EV << "Processing Authentication frame, seqNum=" << frameAuthSeq << "\n";

        // create STA entry if needed
        HaLowSTAInfo *sta = lookupHaLowSenderSTA(frame);
        if (!sta) {
            MACAddress staAddress = frame->getTransmitterAddress();
            sta = &staList[staAddress];    // this implicitly creates a new entry
            sta->address = staAddress;
            sta->status = NOT_AUTHENTICATED;
            sta->authSeqExpected = 1;
            STAcount = STAcount + 1;

            int STAmod = STAcount % TIMcount;

            switch (STAmod)
            {
            case 0 :
                sta->TIMindex = TIM1;
                break;

            case 1 :
               sta->TIMindex = TIM2;
                break;

            case 2 :
                sta ->TIMindex = TIM3;
                break;

            case 3 :
                sta -> TIMindex = TIM4;
                break;

            case 4 :
                sta -> TIMindex = TIM5;
                break;

            case 5 :
                sta -> TIMindex = TIM6;
                break;

            case 6 :
                sta -> TIMindex = TIM7;
                break;

            case 7 :
                sta -> TIMindex = TIM8;
                break;

            default :
                sta -> TIMindex = TIM1;
                break;


            }

            sta->PAGEindex = PAGE1;

            sta->AssociationID = getassociationID(frame);
            EV << "StationInfo" << sta << "\n" ;
            EV << "Association Identifier of Station" << sta->AssociationID << "\n";

        }

        // reset authentication status, when starting a new auth sequence
        // The statements below are added because the L2 handover time was greater than before when
        // a STA wants to re-connect to an AP with which it was associated before. When the STA wants to
        // associate again with the previous AP, then since the AP is already having an entry of the STA
        // because of old association, and thus it is expecting an authentication frame number 3 but it
        // receives authentication frame number 1 from STA, which will cause the AP to return an Auth-Error
        // making the MN STA to start the handover process all over again.
        if (frameAuthSeq == 1) {
            if (sta->status == ASSOCIATED)
                sendDisAssocNotification(sta->address);
            sta->status = NOT_AUTHENTICATED;
            sta->authSeqExpected = 1;
        }

        // check authentication sequence number is OK
        if (frameAuthSeq != sta->authSeqExpected) {
            // wrong sequence number: send error and return
            EV << "Wrong sequence number, " << sta->authSeqExpected << " expected\n";

            Ieee80211AuthenticationFrame *resp = new Ieee80211AuthenticationFrame("Auth-ERROR");
            resp->getBody().setStatusCode(SC_AUTH_OUT_OF_SEQ);
            sendManagementFrame(resp, frame->getTransmitterAddress());
            delete frame;
            sta->authSeqExpected = 1;    // go back to start square
            return;
        }

        // station is authenticated if it made it through the required number of steps
        bool isLast = (frameAuthSeq + 1 == numAuthSteps);

        // send OK response (we don't model the cryptography part, just assume
        // successful authentication every time)
        EV << "Sending Authentication frame, seqNum=" << (frameAuthSeq + 1) << "\n";
        Ieee80211AuthenticationFrame *resp = new Ieee80211AuthenticationFrame(isLast ? "Auth-OK" : "Auth");
        resp->getBody().setSequenceNumber(frameAuthSeq + 1);
        resp->getBody().setStatusCode(SC_SUCCESSFUL);
        resp->getBody().setIsLast(isLast);

        // XXX frame length could be increased to account for challenge text length etc.
        sendManagementFrame(resp, frame->getTransmitterAddress());

        delete frame;

        // update status
        if (isLast) {
            if (sta->status == ASSOCIATED)
                sendDisAssocNotification(sta->address);
            sta->status = AUTHENTICATED;    // XXX only when ACK of this frame arrives
            EV << "STA authenticated\n";
        }
        else {
            sta->authSeqExpected += 2;
            EV << "Expecting Authentication frame " << sta->authSeqExpected << "\n";
        }
}


void Ieee80211HaLowMgmtAP::handleDeauthenticationFrame(Ieee80211DeauthenticationFrame *frame)
{
    EV << "Processing Deauthentication frame\n";

    // create STA entry if needed
    HaLowSTAInfo *sta = lookupHaLowSenderSTA(frame);
    delete frame;

    if (sta) {
        // mark STA as not authenticated; alternatively, it could also be removed from staList
        if (sta->status == ASSOCIATED)
            sendDisAssocNotification(sta->address);
        sta->status = NOT_AUTHENTICATED;
        sta->authSeqExpected = 1;
    }
}

void Ieee80211HaLowMgmtAP::handleAssociationRequestFrame(Ieee80211AssociationRequestFrame *frame)
{
    EV << "Processing AssociationRequest frame\n";

    // "11.3.2 AP association procedures"
    // create STA entry if needed
        HaLowSTAInfo *sta = lookupHaLowSenderSTA(frame);
    if (!sta || sta->status == NOT_AUTHENTICATED) {
        // STA not authenticated: send error and return
        Ieee80211DeauthenticationFrame *resp = new Ieee80211DeauthenticationFrame("Deauth");
        resp->getBody().setReasonCode(RC_NONAUTH_ASS_REQUEST);
        sendManagementFrame(resp, frame->getTransmitterAddress());
        delete frame;
        return;
    }

    delete frame;

    // mark STA as associated
    if (sta->status != ASSOCIATED)
        sendAssocNotification(sta->address);
    sta->status = ASSOCIATED;    // XXX this should only take place when MAC receives the ACK for the response
    uint64_t AssociationIdentifier = sta->AssociationID;



    // send OK response
    Ieee80211HaLowAssociationResponseFrame *resp = new Ieee80211HaLowAssociationResponseFrame("AssocResp-OK");
    Ieee80211HaLowAssociationResponseFrameBody& body = resp->getBody();
    body.setStatusCode(SC_SUCCESSFUL);
    body.setAid(0);    //XXX
    body.setSupportedRates(supportedRates);
    body.setassociationID(AssociationIdentifier);// reason is there is no extension directly for assocrespframe
    sendManagementFrame(resp, sta->address);
}



void Ieee80211HaLowMgmtAP::handleReassociationRequestFrame(Ieee80211ReassociationRequestFrame *frame)
{
    EV << "Processing ReassociationRequest frame\n";

    // "11.3.4 AP reassociation procedures" -- almost the same as AssociationRequest processing
    // create STA entry if needed
        HaLowSTAInfo *sta = lookupHaLowSenderSTA(frame);
    if (!sta || sta->status == NOT_AUTHENTICATED) {
        // STA not authenticated: send error and return
        Ieee80211DeauthenticationFrame *resp = new Ieee80211DeauthenticationFrame("Deauth");
        resp->getBody().setReasonCode(RC_NONAUTH_ASS_REQUEST);
        sendManagementFrame(resp, frame->getTransmitterAddress());
        delete frame;
        return;
    }

    delete frame;

    // mark STA as associated
    sta->status = ASSOCIATED;    // XXX this should only take place when MAC receives the ACK for the response

    // send OK response
    Ieee80211ReassociationResponseFrame *resp = new Ieee80211ReassociationResponseFrame("ReassocResp-OK");
    Ieee80211ReassociationResponseFrameBody& body = resp->getBody();
    body.setStatusCode(SC_SUCCESSFUL);
    body.setAid(0);    //XXX
    body.setSupportedRates(supportedRates);
    sendManagementFrame(resp, sta->address);
}


uint64_t Ieee80211HaLowMgmtAP:: getassociationID(Ieee80211AuthenticationFrame *frame)
{
    uint64_t Associationindex;
    static uint8_t STAindex = 0x01;
    EV << "STA index1  " << STAindex << "\n";
    uint16_t pageID;
    uint16_t TIMID;
    HaLowSTAInfo *sta = lookupHaLowSenderSTA(frame);


if (sta->PAGEindex == PAGE1)
{
     pageID = 0x00;

     EV << "Page index  " << pageID << "\n";

}
else {
     pageID = 1;
}

switch (sta->TIMindex)
{

case TIM1 :
        TIMID = 0x00;
break;

case TIM2 :
        TIMID = 0x01;
break;

case TIM3 :
        TIMID = 0x02;
break;

case TIM4 :
        TIMID = 0x03;
break;

case TIM5 :
        TIMID = 0x04;
break;

case TIM6 :
        TIMID = 0x05;
break;

case TIM7 :
        TIMID = 0x06;
break;

case TIM8 :
        TIMID = 0x07;
 break;

default :
        TIMID = 0x00;
 break;

}


STAindex = STAindex + 1;

EV << "Station index2  " << STAindex << "\n";


Associationindex = pageID;
Associationindex = Associationindex << 3 | TIMID;
Associationindex = Associationindex << 8 | STAindex;

EV << "Association index  " << Associationindex << "\n";

 return Associationindex;
}


}

}







