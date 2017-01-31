/*
 * Ieee80211HaLowMgmtFrames_m.h
 *
 *  Created on: 24-Jan-2017
 *      Author: KAUSHIK NAGARAJAN
 */

#ifndef IEEE80211HALOWMGMTFRAMES_M_H_
#define IEEE80211HALOWMGMTFRAMES_M_H_

#include <omnetpp.h>



// cplusplus {{
#include "inet/linklayer/common/MACAddress.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"
#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.h"
// }}

USING_NAMESPACE


namespace inet {
namespace ieee80211 {



class Ieee80211HaLowAuthenticationFrame : public Ieee80211AuthenticationFrame
{
  protected:
    Ieee80211AuthenticationFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowAuthenticationFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowAuthenticationFrame&);

  public:
    Ieee80211HaLowAuthenticationFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowAuthenticationFrame(const Ieee80211HaLowAuthenticationFrame& other);
    virtual ~Ieee80211HaLowAuthenticationFrame();
    Ieee80211HaLowAuthenticationFrame& operator=(const Ieee80211HaLowAuthenticationFrame& other);
    virtual Ieee80211HaLowAuthenticationFrame *dup() const {return new Ieee80211HaLowAuthenticationFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211AuthenticationFrameBody& getBody();
    virtual const Ieee80211AuthenticationFrameBody& getBody() const {return const_cast<Ieee80211HaLowAuthenticationFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211AuthenticationFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowAuthenticationFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowAuthenticationFrame& obj) {obj.parsimUnpack(b);}


class Ieee80211HaLowDeauthenticationFrame : public Ieee80211DeauthenticationFrame
{
  protected:
    Ieee80211DeauthenticationFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowDeauthenticationFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowDeauthenticationFrame&);

  public:
    Ieee80211HaLowDeauthenticationFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowDeauthenticationFrame(const Ieee80211HaLowDeauthenticationFrame& other);
    virtual ~Ieee80211HaLowDeauthenticationFrame();
    Ieee80211HaLowDeauthenticationFrame& operator=(const Ieee80211HaLowDeauthenticationFrame& other);
    virtual Ieee80211HaLowDeauthenticationFrame *dup() const {return new Ieee80211HaLowDeauthenticationFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211DeauthenticationFrameBody& getBody();
    virtual const Ieee80211DeauthenticationFrameBody& getBody() const {return const_cast<Ieee80211HaLowDeauthenticationFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211DeauthenticationFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowDeauthenticationFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowDeauthenticationFrame& obj) {obj.parsimUnpack(b);}


class Ieee80211HaLowDisassociationFrame : public Ieee80211DisassociationFrame
{
  protected:
    Ieee80211DisassociationFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowDisassociationFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowDisassociationFrame&);

  public:
    Ieee80211HaLowDisassociationFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowDisassociationFrame(const Ieee80211HaLowDisassociationFrame& other);
    virtual ~Ieee80211HaLowDisassociationFrame();
    Ieee80211HaLowDisassociationFrame& operator=(const Ieee80211HaLowDisassociationFrame& other);
    virtual Ieee80211HaLowDisassociationFrame *dup() const {return new Ieee80211HaLowDisassociationFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211DisassociationFrameBody& getBody();
    virtual const Ieee80211DisassociationFrameBody& getBody() const {return const_cast<Ieee80211HaLowDisassociationFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211DisassociationFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowDisassociationFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowDisassociationFrame& obj) {obj.parsimUnpack(b);}


class Ieee80211HaLowProbeRequestFrame : public Ieee80211ProbeRequestFrame
{
  protected:
    Ieee80211ProbeRequestFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowProbeRequestFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowProbeRequestFrame&);

  public:
    Ieee80211HaLowProbeRequestFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowProbeRequestFrame(const Ieee80211HaLowProbeRequestFrame& other);
    virtual ~Ieee80211HaLowProbeRequestFrame();
    Ieee80211HaLowProbeRequestFrame& operator=(const Ieee80211HaLowProbeRequestFrame& other);
    virtual Ieee80211HaLowProbeRequestFrame *dup() const {return new Ieee80211HaLowProbeRequestFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211ProbeRequestFrameBody& getBody();
    virtual const Ieee80211ProbeRequestFrameBody& getBody() const {return const_cast<Ieee80211HaLowProbeRequestFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211ProbeRequestFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowProbeRequestFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowProbeRequestFrame& obj) {obj.parsimUnpack(b);}



class Ieee80211HaLowAssociationRequestFrame : public Ieee80211AssociationRequestFrame
{
  protected:
    Ieee80211AssociationRequestFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowAssociationRequestFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowAssociationRequestFrame&);

  public:
    Ieee80211HaLowAssociationRequestFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowAssociationRequestFrame(const Ieee80211HaLowAssociationRequestFrame& other);
    virtual ~Ieee80211HaLowAssociationRequestFrame();
    Ieee80211HaLowAssociationRequestFrame& operator=(const Ieee80211HaLowAssociationRequestFrame& other);
    virtual Ieee80211HaLowAssociationRequestFrame *dup() const {return new Ieee80211HaLowAssociationRequestFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211AssociationRequestFrameBody& getBody();
    virtual const Ieee80211AssociationRequestFrameBody& getBody() const {return const_cast<Ieee80211HaLowAssociationRequestFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211AssociationRequestFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowAssociationRequestFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowAssociationRequestFrame& obj) {obj.parsimUnpack(b);}


class Ieee80211HaLowReassociationRequestFrame : public Ieee80211ReassociationRequestFrame
{
  protected:
    Ieee80211ReassociationRequestFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowReassociationRequestFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowReassociationRequestFrame&);

  public:
    Ieee80211HaLowReassociationRequestFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowReassociationRequestFrame(const Ieee80211HaLowReassociationRequestFrame& other);
    virtual ~Ieee80211HaLowReassociationRequestFrame();
    Ieee80211HaLowReassociationRequestFrame& operator=(const Ieee80211HaLowReassociationRequestFrame& other);
    virtual Ieee80211HaLowReassociationRequestFrame *dup() const {return new Ieee80211HaLowReassociationRequestFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211ReassociationRequestFrameBody& getBody();
    virtual const Ieee80211ReassociationRequestFrameBody& getBody() const {return const_cast<Ieee80211HaLowReassociationRequestFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211ReassociationRequestFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowReassociationRequestFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowReassociationRequestFrame& obj) {obj.parsimUnpack(b);}



class Ieee80211HaLowAssociationResponseFrameBody : public ::inet::ieee80211::Ieee80211FrameBody
{
  protected:
    int statusCode_var;
    short aid_var;
    Ieee80211SupportedRatesElement supportedRates_var;
    uint64_t AssociationID_var;

  private:
    void copy(const Ieee80211HaLowAssociationResponseFrameBody& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowAssociationResponseFrameBody&);

  public:
    Ieee80211HaLowAssociationResponseFrameBody();
    Ieee80211HaLowAssociationResponseFrameBody(const Ieee80211HaLowAssociationResponseFrameBody& other);
    virtual ~Ieee80211HaLowAssociationResponseFrameBody();
    Ieee80211HaLowAssociationResponseFrameBody& operator=(const Ieee80211HaLowAssociationResponseFrameBody& other);
    virtual Ieee80211HaLowAssociationResponseFrameBody *dup() const {return new Ieee80211HaLowAssociationResponseFrameBody(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getStatusCode() const;
    virtual void setStatusCode(int statusCode);
    virtual short getAid() const;
    virtual void setAid(short aid);
    virtual Ieee80211SupportedRatesElement& getSupportedRates();
    virtual const Ieee80211SupportedRatesElement& getSupportedRates() const {return const_cast<Ieee80211HaLowAssociationResponseFrameBody*>(this)->getSupportedRates();}
    virtual void setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates);
    virtual uint64_t getassociationID() const;
    virtual void setassociationID(uint64_t AssociationIdentifier);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowAssociationResponseFrameBody& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowAssociationResponseFrameBody& obj) {obj.parsimUnpack(b);

}



class Ieee80211HaLowAssociationResponseFrame : public ::inet::ieee80211::Ieee80211ManagementFrame
{
  protected:
    Ieee80211HaLowAssociationResponseFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowAssociationResponseFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowAssociationResponseFrame&);

  public:
    Ieee80211HaLowAssociationResponseFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowAssociationResponseFrame(const Ieee80211HaLowAssociationResponseFrame& other);
    virtual ~Ieee80211HaLowAssociationResponseFrame();
    Ieee80211HaLowAssociationResponseFrame& operator=(const Ieee80211HaLowAssociationResponseFrame& other);
    virtual Ieee80211HaLowAssociationResponseFrame *dup() const {return new Ieee80211HaLowAssociationResponseFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211HaLowAssociationResponseFrameBody& getBody();
    virtual const Ieee80211HaLowAssociationResponseFrameBody& getBody() const {return const_cast<Ieee80211HaLowAssociationResponseFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211HaLowAssociationResponseFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowAssociationResponseFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowAssociationResponseFrame& obj) {obj.parsimUnpack(b);}



class Ieee80211HaLowReassociationResponseFrame : public Ieee80211ReassociationResponseFrame
{
  protected:
    Ieee80211ReassociationResponseFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowReassociationResponseFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowReassociationResponseFrame&);

  public:
    Ieee80211HaLowReassociationResponseFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowReassociationResponseFrame(const Ieee80211HaLowReassociationResponseFrame& other);
    virtual ~Ieee80211HaLowReassociationResponseFrame();
    Ieee80211HaLowReassociationResponseFrame& operator=(const Ieee80211HaLowReassociationResponseFrame& other);
    virtual Ieee80211HaLowReassociationResponseFrame *dup() const {return new Ieee80211HaLowReassociationResponseFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211ReassociationResponseFrameBody& getBody();
    virtual const Ieee80211ReassociationResponseFrameBody& getBody() const {return const_cast<Ieee80211HaLowReassociationResponseFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211ReassociationResponseFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowReassociationResponseFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowReassociationResponseFrame& obj) {obj.parsimUnpack(b);}


class Ieee80211HaLowBeaconFrame : public Ieee80211BeaconFrame
{
  protected:
    Ieee80211BeaconFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowBeaconFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowBeaconFrame&);

  public:
    Ieee80211HaLowBeaconFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowBeaconFrame(const Ieee80211HaLowBeaconFrame& other);
    virtual ~Ieee80211HaLowBeaconFrame();
    Ieee80211HaLowBeaconFrame& operator=(const Ieee80211HaLowBeaconFrame& other);
    virtual Ieee80211HaLowBeaconFrame *dup() const {return new Ieee80211HaLowBeaconFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211BeaconFrameBody& getBody();
    virtual const Ieee80211BeaconFrameBody& getBody() const {return const_cast<Ieee80211HaLowBeaconFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211BeaconFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowBeaconFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowBeaconFrame& obj) {obj.parsimUnpack(b);}

class Ieee80211HaLowProbeResponseFrame : public Ieee80211ProbeResponseFrame
{
  protected:
    Ieee80211ProbeResponseFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowProbeResponseFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowProbeResponseFrame&);

  public:
    Ieee80211HaLowProbeResponseFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowProbeResponseFrame(const Ieee80211HaLowProbeResponseFrame& other);
    virtual ~Ieee80211HaLowProbeResponseFrame();
    Ieee80211HaLowProbeResponseFrame& operator=(const Ieee80211HaLowProbeResponseFrame& other);
    virtual Ieee80211HaLowProbeResponseFrame *dup() const {return new Ieee80211HaLowProbeResponseFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211ProbeResponseFrameBody& getBody();
    virtual const Ieee80211ProbeResponseFrameBody& getBody() const {return const_cast<Ieee80211HaLowProbeResponseFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211ProbeResponseFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowProbeResponseFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowProbeResponseFrame& obj) {obj.parsimUnpack(b);}


class Ieee80211HaLowActionFrame : public Ieee80211ActionFrame
{
  protected:
    Ieee80211ActionFrameBody body_var;

  private:
    void copy(const Ieee80211HaLowActionFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211HaLowActionFrame&);

  public:
    Ieee80211HaLowActionFrame(const char *name=NULL, int kind=0);
    Ieee80211HaLowActionFrame(const Ieee80211HaLowActionFrame& other);
    virtual ~Ieee80211HaLowActionFrame();
    Ieee80211HaLowActionFrame& operator=(const Ieee80211HaLowActionFrame& other);
    virtual Ieee80211HaLowActionFrame *dup() const {return new Ieee80211HaLowActionFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual Ieee80211ActionFrameBody& getBody();
    virtual const Ieee80211ActionFrameBody& getBody() const {return const_cast<Ieee80211HaLowActionFrame*>(this)->getBody();}
    virtual void setBody(const Ieee80211ActionFrameBody& body);
};

inline void doPacking(cCommBuffer *b, Ieee80211HaLowActionFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211HaLowActionFrame& obj) {obj.parsimUnpack(b);}



}//ieee80211
}//inet
#endif /* IEEE80211HALOWMGMTFRAMES_M_H_ */
