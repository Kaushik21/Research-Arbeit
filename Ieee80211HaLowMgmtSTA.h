/*
 * Ieee80211HaLowMgmtSTA.h
 *
 *  Created on: 21-Jan-2017
 *      Author: KAUSHIK NAGARAJAN
 */

#ifndef IEEE80211HALOWMGMTSTA_H_
#define IEEE80211HALOWMGMTSTA_H_


#include "inet/common/INETDefs.h"

#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.h"
#include "Ieee80211HaLowMgmtFrames_m.h"


namespace inet {

class InterfaceEntry;

namespace ieee80211 {

class INET_API Ieee80211HaLowMgmtSTA : public Ieee80211MgmtSTA
{



protected:
    cModule *host;
    IInterfaceTable *interfaceTable;
    InterfaceEntry *myIface;

    int numChannels;

        // scanning status
        bool isScanning;
        ScanningInfo scanning;

        // APInfo list: we collect scanning results and keep track of ongoing authentications here
        // Note: there can be several ongoing authentications simultaneously
        typedef std::list<APInfo> AccessPointList;
        AccessPointList apList;

        // associated Access Point
        bool isAssociated;
        uint64_t AssociationValue;
        cMessage *assocTimeoutMsg;    // if non-nullptr: association is in progress
        //HaLowAssociatedAPInfo assocAP;


public:
    Ieee80211HaLowMgmtSTA() : host(nullptr), interfaceTable(nullptr), myIface(nullptr), numChannels(-1), isScanning(false), isAssociated(false), assocTimeoutMsg(nullptr) {}

protected:

        virtual int numInitStages() const override { return NUM_INIT_STAGES; }
        virtual void initialize(int stage) override;

        /** Implements abstract Ieee80211MgmtBase method */
        virtual void handleTimer(cMessage *msg) override;

        /** Implements abstract Ieee80211MgmtBase method */
        virtual void handleUpperMessage(cPacket *msg) override;

        /** Implements abstract Ieee80211MgmtBase method */
        virtual void handleCommand(int msgkind, cObject *ctrl) override;

        /** Utility function for handleUpperMessage() */
        virtual Ieee80211DataFrame *encapsulate(cPacket *msg);

        /** Utility method to decapsulate a data frame */
        virtual cPacket *decapsulate(Ieee80211DataFrame *frame);
        /** Utility function: sends authentication request */
        virtual void startAuthentication(APInfo *ap, simtime_t timeout);

        /** Utility function: sends association request */
        virtual void startAssociation(APInfo *ap, simtime_t timeout);

        /** Utility function: looks up AP in our AP list. Returns nullptr if not found. */
        virtual APInfo *lookupAP(const MACAddress& address);

        /** Utility function: clear the AP list, and cancel any pending authentications. */
        virtual void clearAPList();

        /** Broadcasts a Probe Request */
        virtual void sendProbeRequest();

        /** Sends back result of association to the agent */
        virtual void sendAssociationConfirm(APInfo *ap, int resultCode);


        /** Utility function: sends a confirmation to the agent */
        virtual void sendConfirm(Ieee80211PrimConfirm *confirm, int resultCode);



            /** Called by the signal handler whenever a change occurs we're interested in */
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, long value DETAILS_ARG) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj DETAILS_ARG) override;

            /** Utility function: converts Ieee80211StatusCode (->frame) to Ieee80211PrimResultCode (->primitive) */
            virtual int statusCodeToPrimResultCode(int statusCode);

            /** @name Processing of different frame types */
            //@{
            //virtual void handleDataFrame(Ieee80211DataFrame *frame) override;
            virtual void handleAuthenticationFrame(Ieee80211HaLowAuthenticationFrame *frame);
            virtual void handleDeauthenticationFrame(Ieee80211HaLowDeauthenticationFrame *frame);
            virtual void handleAssociationRequestFrame(Ieee80211HaLowAssociationRequestFrame *frame);
            virtual void handleAssociationResponseFrame(Ieee80211HaLowAssociationResponseFrame *frame);
            virtual void handleReassociationRequestFrame(Ieee80211HaLowReassociationRequestFrame *frame);
            virtual void handleReassociationResponseFrame(Ieee80211HaLowReassociationResponseFrame *frame);
            virtual void handleDisassociationFrame(Ieee80211HaLowDisassociationFrame *frame);
            virtual void handleBeaconFrame(Ieee80211HaLowBeaconFrame *frame);
            virtual void handleProbeRequestFrame(Ieee80211HaLowProbeRequestFrame *frame) ;
            virtual void handleProbeResponseFrame(Ieee80211HaLowProbeResponseFrame *frame) ;
            //@}





};

}
}


#endif /* IEEE80211HALOWMGMTSTA_H_ */
