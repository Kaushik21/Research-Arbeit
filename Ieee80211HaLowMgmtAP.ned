//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package networktest;//inet.linklayer.ieee80211.mgmt;//networktest;
//package inet.linklayer.ieee80211.mgmt;
import inet.linklayer.ieee80211.mgmt.IIeee80211Mgmt;
import inet.linklayer.ieee80211.mgmt.Ieee80211MgmtAP;


//simple Ieee80211HaLowMgmtAP extends Ieee80211MgmtAP
//{
   // parameters:
    //    string TIMindex @enum("TIM1","TIM2","TIM3","TIM4","TIM5","TIM6","TIM7","TIM8") = default("TIM1");
  //      @class(inet::ieee80211::Ieee80211HaLowMgmtAP);
//}



simple Ieee80211HaLowMgmtAP like IIeee80211Mgmt

{
    parameters:
        string ssid = default("SSID");
        double beaconInterval @unit("s") = default(100ms);
        int numAuthSteps = default(4); // use 2 for Open System auth, 4 for WEP
        string encapDecap = default("eth") @enum("true", "false", "eth");   // if "eth", frames sent up are converted to EthernetIIFrame
        //dataRate: numeric; XXX TBD
        string radioModule = default("^.radio");   // The path to the Radio module  //FIXME remove default value
        string macModule;               // The path to the MAC module
        //string TIMindex = default("TIM1") @enum("TIM1","TIM2","TIM3","TIM4","TIM5","TIM6","TIM7","TIM8");
        @display("i=block/cogwheel");
        @class(inet::ieee80211::Ieee80211HaLowMgmtAP);
        @signal[NF_L2_AP_ASSOCIATED](type="Ieee80211HaLowMgmtAP::NotificationInfoSta");
        @signal[NF_L2_AP_DISASSOCIATED](type="Ieee80211HaLowMgmtAP::NotificationInfoSta");
    gates:
        input upperLayerIn; // from ~IMACRelayUnit; can be left unconnected
        output upperLayerOut; // to ~IMACRelayUnit; can be left unconnected
        input macIn @labels(Ieee80211Frame); // from ~Ieee80211Mac
        output macOut @labels(Ieee80211Frame); // to ~Ieee80211Mac
        input agentIn @loose;   // unused dummy to statisfy the IIeee80211Mgmt interface
        output agentOut @loose; // unused dummy to statisfy the IIeee80211Mgmt interface
}
