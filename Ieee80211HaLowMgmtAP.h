/*
 * Ieee80211HaLowMgmtAP.h
 *
 *  Created on: 19-Dec-2016
 *      Author: KAUSHIK NAGARAJAN
 */

#ifndef IEEE80211HALOWMGMTAP_H_
#define IEEE80211HALOWMGMTAP_H_


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>



#include "inet/common/INETDefs.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h"
#include "Ieee80211HaLowMgmtFrames_m.cc"



namespace inet {



namespace ieee80211 {




class INET_API Ieee80211HaLowMgmtAP : public Ieee80211MgmtAP
{

public:
        enum TIMGROUP { TIM1,TIM2,TIM3,TIM4,TIM5,TIM6,TIM7,TIM8};
        enum PAGEGROUP {PAGE1,PAGE2,PAGE3,PAGE4};
        enum STAStatus { NOT_AUTHENTICATED, AUTHENTICATED, ASSOCIATED };
        uint64_t getassociationID(Ieee80211AuthenticationFrame *frame);

        struct HaLowSTAInfo
            {
                MACAddress address;
                STAStatus status;
                int authSeqExpected;    // when NOT_AUTHENTICATED: transaction sequence number of next expected auth frame
                //int consecFailedTrans;  //XXX
                //double expiry;          //XXX association should expire after a while if STA is silent?

                PAGEGROUP PAGEindex; // PAGE implementation
                TIMGROUP TIMindex; // TIM implementation
                uint64_t AssociationID;
            };

        class NotificationInfoSta : public cObject
           {
               MACAddress apAddress;
               MACAddress staAddress;

             public:
               void setApAddress(const MACAddress& a) { apAddress = a; }
               void setStaAddress(const MACAddress& a) { staAddress = a; }
               const MACAddress& getApAddress() const { return apAddress; }
               const MACAddress& getStaAddress() const { return staAddress; }
           };

           struct MAC_compare
           {
               bool operator()(const MACAddress& u1, const MACAddress& u2) const { return u1.compareTo(u2) < 0; }
           };
           typedef std::map<MACAddress, HaLowSTAInfo, MAC_compare> STAList;

protected:
           int numAuthSteps = 0;
           //state
           STAList staList;
           MACAddress myAddress;
           /** Implements abstract Ieee80211MgmtBase method */
              virtual void handleTimer(cMessage *msg) override;

              /** Implements abstract Ieee80211MgmtBase method */
              virtual void handleUpperMessage(cPacket *msg) override;

              /** Implements abstract Ieee80211MgmtBase method -- throws an error (no commands supported) */
              virtual void handleCommand(int msgkind, cObject *ctrl) override;

              /** Called by the signal handler whenever a change occurs we're interested in */
              virtual void receiveSignal(cComponent *source, simsignal_t signalID, long value DETAILS_ARG) override;

         /** Utility function: set fields in the given frame and send it out to the address */
        virtual void sendManagementFrame(Ieee80211ManagementFrame *frame, const MACAddress& destAddr);
        virtual HaLowSTAInfo *lookupHaLowSenderSTA(Ieee80211ManagementFrame *frame);
        virtual void handleAuthenticationFrame(Ieee80211AuthenticationFrame *frame);
        virtual void handleDeauthenticationFrame(Ieee80211DeauthenticationFrame *frame);
        virtual void handleAssociationRequestFrame(Ieee80211AssociationRequestFrame *frame);
        virtual void handleReassociationRequestFrame(Ieee80211ReassociationRequestFrame *frame) ;
        /**virtual void handleDisassociationFrame(Ieee80211DisassociationFrame *frame) override;**/


        void sendAssocNotification(const MACAddress& addr);
        void sendDisAssocNotification(const MACAddress& addr);

};


}
}






#endif /* IEEE80211HALOWMGMTAP_H_ */
