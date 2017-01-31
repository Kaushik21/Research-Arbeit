/*
 * Ieee80211HaLowMgmtFrames_m.cc
 *
 *  Created on: 24-Jan-2017
 *      Author: KAUSHIK NAGARAJAN
 */

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Ieee80211HaLowMgmtFrames_m.h"

USING_NAMESPACE

// Another default rule (prevents compiler from choosing base class' doPacking())

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

namespace inet {
namespace ieee80211 {

// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}




Register_Class(Ieee80211HaLowAuthenticationFrame);

Ieee80211HaLowAuthenticationFrame::Ieee80211HaLowAuthenticationFrame(const char *name, int kind) : Ieee80211AuthenticationFrame::Ieee80211AuthenticationFrame(name,kind)
{
    this->setType(ST_AUTHENTICATION);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowAuthenticationFrame::Ieee80211HaLowAuthenticationFrame(const Ieee80211HaLowAuthenticationFrame& other) : Ieee80211AuthenticationFrame::Ieee80211AuthenticationFrame(other)
{
    copy(other);
}

Ieee80211HaLowAuthenticationFrame::~Ieee80211HaLowAuthenticationFrame()
{
}

Ieee80211HaLowAuthenticationFrame& Ieee80211HaLowAuthenticationFrame::operator=(const Ieee80211HaLowAuthenticationFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowAuthenticationFrame::copy(const Ieee80211HaLowAuthenticationFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowAuthenticationFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowAuthenticationFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211AuthenticationFrameBody& Ieee80211HaLowAuthenticationFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowAuthenticationFrame::setBody(const Ieee80211AuthenticationFrameBody& body)
{
    this->body_var = body;
}






Register_Class(Ieee80211HaLowDeauthenticationFrame);

Ieee80211HaLowDeauthenticationFrame::Ieee80211HaLowDeauthenticationFrame(const char *name, int kind) :  Ieee80211DeauthenticationFrame::Ieee80211DeauthenticationFrame(name,kind)
{
    this->setType(ST_DEAUTHENTICATION);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowDeauthenticationFrame::Ieee80211HaLowDeauthenticationFrame(const Ieee80211HaLowDeauthenticationFrame& other) : Ieee80211DeauthenticationFrame::Ieee80211DeauthenticationFrame(other)
{
    copy(other);
}

Ieee80211HaLowDeauthenticationFrame::~Ieee80211HaLowDeauthenticationFrame()
{
}

Ieee80211HaLowDeauthenticationFrame& Ieee80211HaLowDeauthenticationFrame::operator=(const Ieee80211HaLowDeauthenticationFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowDeauthenticationFrame::copy(const Ieee80211HaLowDeauthenticationFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowDeauthenticationFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowDeauthenticationFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211DeauthenticationFrameBody& Ieee80211HaLowDeauthenticationFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowDeauthenticationFrame::setBody(const Ieee80211DeauthenticationFrameBody& body)
{
    this->body_var = body;
}



Register_Class(Ieee80211HaLowDisassociationFrame);

Ieee80211HaLowDisassociationFrame::Ieee80211HaLowDisassociationFrame(const char *name, int kind) : Ieee80211DisassociationFrame::Ieee80211DisassociationFrame(name,kind)
{
    this->setType(ST_DISASSOCIATION);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowDisassociationFrame::Ieee80211HaLowDisassociationFrame(const Ieee80211HaLowDisassociationFrame& other) : Ieee80211DisassociationFrame::Ieee80211DisassociationFrame(other)
{
    copy(other);
}

Ieee80211HaLowDisassociationFrame::~Ieee80211HaLowDisassociationFrame()
{
}

Ieee80211HaLowDisassociationFrame& Ieee80211HaLowDisassociationFrame::operator=(const Ieee80211HaLowDisassociationFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowDisassociationFrame::copy(const Ieee80211HaLowDisassociationFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowDisassociationFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowDisassociationFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211DisassociationFrameBody& Ieee80211HaLowDisassociationFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowDisassociationFrame::setBody(const Ieee80211DisassociationFrameBody& body)
{
    this->body_var = body;
}



Register_Class(Ieee80211HaLowProbeRequestFrame);

Ieee80211HaLowProbeRequestFrame::Ieee80211HaLowProbeRequestFrame(const char *name, int kind) : Ieee80211ProbeRequestFrame::Ieee80211ProbeRequestFrame(name,kind)
{
    this->setType(ST_PROBEREQUEST);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowProbeRequestFrame::Ieee80211HaLowProbeRequestFrame(const Ieee80211HaLowProbeRequestFrame& other) : Ieee80211ProbeRequestFrame::Ieee80211ProbeRequestFrame(other)
{
    copy(other);
}

Ieee80211HaLowProbeRequestFrame::~Ieee80211HaLowProbeRequestFrame()
{
}

Ieee80211HaLowProbeRequestFrame& Ieee80211HaLowProbeRequestFrame::operator=(const Ieee80211HaLowProbeRequestFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowProbeRequestFrame::copy(const Ieee80211HaLowProbeRequestFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowProbeRequestFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowProbeRequestFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211ProbeRequestFrameBody& Ieee80211HaLowProbeRequestFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowProbeRequestFrame::setBody(const Ieee80211ProbeRequestFrameBody& body)
{
    this->body_var = body;
}



Register_Class(Ieee80211HaLowAssociationRequestFrame);

Ieee80211HaLowAssociationRequestFrame::Ieee80211HaLowAssociationRequestFrame(const char *name, int kind) : Ieee80211AssociationRequestFrame::Ieee80211AssociationRequestFrame(name,kind)
{
    this->setType(ST_ASSOCIATIONREQUEST);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowAssociationRequestFrame::Ieee80211HaLowAssociationRequestFrame(const Ieee80211HaLowAssociationRequestFrame& other) : Ieee80211AssociationRequestFrame::Ieee80211AssociationRequestFrame(other)
{
    copy(other);
}

Ieee80211HaLowAssociationRequestFrame::~Ieee80211HaLowAssociationRequestFrame()
{
}

Ieee80211HaLowAssociationRequestFrame& Ieee80211HaLowAssociationRequestFrame::operator=(const Ieee80211HaLowAssociationRequestFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowAssociationRequestFrame::copy(const Ieee80211HaLowAssociationRequestFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowAssociationRequestFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowAssociationRequestFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211AssociationRequestFrameBody& Ieee80211HaLowAssociationRequestFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowAssociationRequestFrame::setBody(const Ieee80211AssociationRequestFrameBody& body)
{
    this->body_var = body;
}


Register_Class(Ieee80211HaLowReassociationRequestFrame);

Ieee80211HaLowReassociationRequestFrame::Ieee80211HaLowReassociationRequestFrame(const char *name, int kind) : Ieee80211ReassociationRequestFrame::Ieee80211ReassociationRequestFrame(name,kind)
{
    this->setType(ST_REASSOCIATIONREQUEST);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowReassociationRequestFrame::Ieee80211HaLowReassociationRequestFrame(const Ieee80211HaLowReassociationRequestFrame& other) : Ieee80211ReassociationRequestFrame::Ieee80211ReassociationRequestFrame(other)
{
    copy(other);
}

Ieee80211HaLowReassociationRequestFrame::~Ieee80211HaLowReassociationRequestFrame()
{
}

Ieee80211HaLowReassociationRequestFrame& Ieee80211HaLowReassociationRequestFrame::operator=(const Ieee80211HaLowReassociationRequestFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowReassociationRequestFrame::copy(const Ieee80211HaLowReassociationRequestFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowReassociationRequestFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowReassociationRequestFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211ReassociationRequestFrameBody& Ieee80211HaLowReassociationRequestFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowReassociationRequestFrame::setBody(const Ieee80211ReassociationRequestFrameBody& body)
{
    this->body_var = body;
}


Register_Class(Ieee80211HaLowAssociationResponseFrameBody);

Ieee80211HaLowAssociationResponseFrameBody::Ieee80211HaLowAssociationResponseFrameBody() : ::inet::ieee80211::Ieee80211FrameBody()
{
    this->setBodyLength(26);

    this->statusCode_var = 0;
    this->aid_var = 0;
    this->AssociationID_var = 0;
}

Ieee80211HaLowAssociationResponseFrameBody::Ieee80211HaLowAssociationResponseFrameBody(const Ieee80211HaLowAssociationResponseFrameBody& other) : ::inet::ieee80211::Ieee80211FrameBody(other)
{
    copy(other);
}

Ieee80211HaLowAssociationResponseFrameBody::~Ieee80211HaLowAssociationResponseFrameBody()
{
}

Ieee80211HaLowAssociationResponseFrameBody& Ieee80211HaLowAssociationResponseFrameBody::operator=(const Ieee80211HaLowAssociationResponseFrameBody& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211FrameBody::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowAssociationResponseFrameBody::copy(const Ieee80211HaLowAssociationResponseFrameBody& other)
{
    this->statusCode_var = other.statusCode_var;
    this->aid_var = other.aid_var;
    this->supportedRates_var = other.supportedRates_var;
    this->AssociationID_var = other.AssociationID_var;
}

void Ieee80211HaLowAssociationResponseFrameBody::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211FrameBody::parsimPack(b);
    doPacking(b,this->statusCode_var);
    doPacking(b,this->aid_var);
    doPacking(b,this->AssociationID_var);
    doPacking(b,this->supportedRates_var);

}

void Ieee80211HaLowAssociationResponseFrameBody::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211FrameBody::parsimUnpack(b);
    doUnpacking(b,this->statusCode_var);
    doUnpacking(b,this->aid_var);
    doUnpacking(b,this->AssociationID_var);
    doUnpacking(b,this->supportedRates_var);


}

int Ieee80211HaLowAssociationResponseFrameBody::getStatusCode() const
{
    return statusCode_var;
}

void Ieee80211HaLowAssociationResponseFrameBody::setStatusCode(int statusCode)
{
    this->statusCode_var = statusCode;
}

short Ieee80211HaLowAssociationResponseFrameBody::getAid() const
{
    return aid_var;
}

void Ieee80211HaLowAssociationResponseFrameBody::setAid(short aid)
{
    this->aid_var = aid;
}

Ieee80211SupportedRatesElement& Ieee80211HaLowAssociationResponseFrameBody::getSupportedRates()
{
    return supportedRates_var;
}

void Ieee80211HaLowAssociationResponseFrameBody::setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates)
{
    this->supportedRates_var = supportedRates;
}

uint64_t Ieee80211HaLowAssociationResponseFrameBody::getassociationID() const
{
    return AssociationID_var;
}

void Ieee80211HaLowAssociationResponseFrameBody::setassociationID(uint64_t AssociationIdentifier)
{
    this->AssociationID_var = AssociationIdentifier;
}



class Ieee80211HaLowAssociationResponseFrameBodyDescriptor : public cClassDescriptor
{
  public:
    Ieee80211HaLowAssociationResponseFrameBodyDescriptor();
    virtual ~Ieee80211HaLowAssociationResponseFrameBodyDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Ieee80211HaLowAssociationResponseFrameBodyDescriptor);

Ieee80211HaLowAssociationResponseFrameBodyDescriptor::Ieee80211HaLowAssociationResponseFrameBodyDescriptor() : cClassDescriptor("inet::ieee80211::Ieee80211AssociationResponseFrameBody", "inet::ieee80211::Ieee80211FrameBody")
{
}

Ieee80211HaLowAssociationResponseFrameBodyDescriptor::~Ieee80211HaLowAssociationResponseFrameBodyDescriptor()
{
}

bool Ieee80211HaLowAssociationResponseFrameBodyDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Ieee80211HaLowAssociationResponseFrameBody *>(obj)!=NULL;
}

const char *Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "statusCode",
        "aid",
        "supportedRates",
        "AssociationIdentifier",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int Ieee80211HaLowAssociationResponseFrameBodyDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "statusCode")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "aid")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "supportedRates")==0) return base+2;
    if (fieldName[0]=='A' && strcmp(fieldName, "AssociationIdentifier")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "short",
        "Ieee80211SupportedRatesElement",
        "uint64_t",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "inet::ieee80211::Ieee80211StatusCode";
            return NULL;
        default: return NULL;
    }
}

int Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211AssociationResponseFrameBody *pp = (Ieee80211AssociationResponseFrameBody *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrameBody *pp = (Ieee80211HaLowAssociationResponseFrameBody *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getStatusCode());
        case 1: return long2string(pp->getAid());
        case 2: {
            std::stringstream out;
        out << pp->getSupportedRates();
        return out.str();
        }
        case 3: return uint642string(pp->getassociationID());
        //case 3: return long2string(pp->getassociationID());
        default: return "";
    }
}

bool Ieee80211HaLowAssociationResponseFrameBodyDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrameBody *pp = (Ieee80211HaLowAssociationResponseFrameBody *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatusCode(string2long(value)); return true;
        case 1: pp->setAid(string2long(value)); return true;
        case 2: pp->setassociationID(string2uint64(value)); return true;
        default: return false;
    }
}

const char *Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(Ieee80211SupportedRatesElement));
        default: return NULL;
    };
}

void *Ieee80211HaLowAssociationResponseFrameBodyDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrameBody *pp = (Ieee80211HaLowAssociationResponseFrameBody *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getSupportedRates()); break;
        default: return NULL;
    }
}


Register_Class(Ieee80211HaLowAssociationResponseFrame);

Ieee80211HaLowAssociationResponseFrame::Ieee80211HaLowAssociationResponseFrame(const char *name, int kind) : ::inet::ieee80211::Ieee80211ManagementFrame(name,kind)
{
    this->setType(ST_ASSOCIATIONRESPONSE);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowAssociationResponseFrame::Ieee80211HaLowAssociationResponseFrame(const Ieee80211HaLowAssociationResponseFrame& other) : ::inet::ieee80211::Ieee80211ManagementFrame(other)
{
    copy(other);
}

Ieee80211HaLowAssociationResponseFrame::~Ieee80211HaLowAssociationResponseFrame()
{
}

Ieee80211HaLowAssociationResponseFrame& Ieee80211HaLowAssociationResponseFrame::operator=(const Ieee80211HaLowAssociationResponseFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowAssociationResponseFrame::copy(const Ieee80211HaLowAssociationResponseFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowAssociationResponseFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowAssociationResponseFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211HaLowAssociationResponseFrameBody& Ieee80211HaLowAssociationResponseFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowAssociationResponseFrame::setBody(const Ieee80211HaLowAssociationResponseFrameBody& body)
{
    this->body_var = body;
}



class Ieee80211HaLowAssociationResponseFrameDescriptor : public cClassDescriptor
{
  public:
    Ieee80211HaLowAssociationResponseFrameDescriptor();
    virtual ~Ieee80211HaLowAssociationResponseFrameDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Ieee80211HaLowAssociationResponseFrameDescriptor);

Ieee80211HaLowAssociationResponseFrameDescriptor::Ieee80211HaLowAssociationResponseFrameDescriptor() : cClassDescriptor("inet::ieee80211::Ieee80211HaLowAssociationResponseFrame", "inet::ieee80211::Ieee80211ManagementFrame")
{
}

Ieee80211HaLowAssociationResponseFrameDescriptor::~Ieee80211HaLowAssociationResponseFrameDescriptor()
{
}

bool Ieee80211HaLowAssociationResponseFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Ieee80211HaLowAssociationResponseFrame *>(obj)!=NULL;
}

const char *Ieee80211HaLowAssociationResponseFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "body",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int Ieee80211HaLowAssociationResponseFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "body")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "Ieee80211HaLowAssociationResponseFrameBody",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Ieee80211HaLowAssociationResponseFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrame *pp = (Ieee80211HaLowAssociationResponseFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrame *pp = (Ieee80211HaLowAssociationResponseFrame *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getBody(); return out.str();}
        default: return "";
    }
}

bool Ieee80211HaLowAssociationResponseFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrame *pp = (Ieee80211HaLowAssociationResponseFrame *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(Ieee80211HaLowAssociationResponseFrameBody));
        default: return NULL;
    };
}

void *Ieee80211HaLowAssociationResponseFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Ieee80211HaLowAssociationResponseFrame *pp = (Ieee80211HaLowAssociationResponseFrame *)object; (void)pp;
    switch (field) {
        case 0: return (void *)static_cast<cObject *>(&pp->getBody()); break;
        default: return NULL;
    }
}



Register_Class(Ieee80211HaLowReassociationResponseFrame);

Ieee80211HaLowReassociationResponseFrame::Ieee80211HaLowReassociationResponseFrame(const char *name, int kind) : Ieee80211ReassociationResponseFrame::Ieee80211ReassociationResponseFrame(name,kind)
{
    this->setType(ST_REASSOCIATIONRESPONSE);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowReassociationResponseFrame::Ieee80211HaLowReassociationResponseFrame(const Ieee80211HaLowReassociationResponseFrame& other) : Ieee80211ReassociationResponseFrame::Ieee80211ReassociationResponseFrame(other)
{
    copy(other);
}

Ieee80211HaLowReassociationResponseFrame::~Ieee80211HaLowReassociationResponseFrame()
{
}

Ieee80211HaLowReassociationResponseFrame& Ieee80211HaLowReassociationResponseFrame::operator=(const Ieee80211HaLowReassociationResponseFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowReassociationResponseFrame::copy(const Ieee80211HaLowReassociationResponseFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowReassociationResponseFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowReassociationResponseFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211ReassociationResponseFrameBody& Ieee80211HaLowReassociationResponseFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowReassociationResponseFrame::setBody(const Ieee80211ReassociationResponseFrameBody& body)
{
    this->body_var = body;
}



Register_Class(Ieee80211HaLowBeaconFrame);

Ieee80211HaLowBeaconFrame::Ieee80211HaLowBeaconFrame(const char *name, int kind) : Ieee80211BeaconFrame::Ieee80211BeaconFrame(name,kind)
{
    this->setType(ST_BEACON);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowBeaconFrame::Ieee80211HaLowBeaconFrame(const Ieee80211HaLowBeaconFrame& other) : Ieee80211BeaconFrame::Ieee80211BeaconFrame(other)
{
    copy(other);
}

Ieee80211HaLowBeaconFrame::~Ieee80211HaLowBeaconFrame()
{
}

Ieee80211HaLowBeaconFrame& Ieee80211HaLowBeaconFrame::operator=(const Ieee80211HaLowBeaconFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowBeaconFrame::copy(const Ieee80211HaLowBeaconFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowBeaconFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowBeaconFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211BeaconFrameBody& Ieee80211HaLowBeaconFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowBeaconFrame::setBody(const Ieee80211BeaconFrameBody& body)
{
    this->body_var = body;
}


Register_Class(Ieee80211HaLowProbeResponseFrame);

Ieee80211HaLowProbeResponseFrame::Ieee80211HaLowProbeResponseFrame(const char *name, int kind) : Ieee80211ProbeResponseFrame::Ieee80211ProbeResponseFrame(name,kind)
{
    this->setType(ST_PROBERESPONSE);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowProbeResponseFrame::Ieee80211HaLowProbeResponseFrame(const Ieee80211HaLowProbeResponseFrame& other) : Ieee80211ProbeResponseFrame::Ieee80211ProbeResponseFrame(other)
{
    copy(other);
}

Ieee80211HaLowProbeResponseFrame::~Ieee80211HaLowProbeResponseFrame()
{
}

Ieee80211HaLowProbeResponseFrame& Ieee80211HaLowProbeResponseFrame::operator=(const Ieee80211HaLowProbeResponseFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowProbeResponseFrame::copy(const Ieee80211HaLowProbeResponseFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowProbeResponseFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowProbeResponseFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211ProbeResponseFrameBody& Ieee80211HaLowProbeResponseFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowProbeResponseFrame::setBody(const Ieee80211ProbeResponseFrameBody& body)
{
    this->body_var = body;
}



Register_Class(Ieee80211HaLowActionFrame);

Ieee80211HaLowActionFrame::Ieee80211HaLowActionFrame(const char *name, int kind) : Ieee80211ActionFrame::Ieee80211ActionFrame(name,kind)
{
    this->setType(ST_ACTION);
    this->setByteLength(18+getBody().getBodyLength());

}

Ieee80211HaLowActionFrame::Ieee80211HaLowActionFrame(const Ieee80211HaLowActionFrame& other) : Ieee80211ActionFrame::Ieee80211ActionFrame(other)
{
    copy(other);
}

Ieee80211HaLowActionFrame::~Ieee80211HaLowActionFrame()
{
}

Ieee80211HaLowActionFrame& Ieee80211HaLowActionFrame::operator=(const Ieee80211HaLowActionFrame& other)
{
    if (this==&other) return *this;
    ::inet::ieee80211::Ieee80211ManagementFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HaLowActionFrame::copy(const Ieee80211HaLowActionFrame& other)
{
    this->body_var = other.body_var;
}

void Ieee80211HaLowActionFrame::parsimPack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimPack(b);
    doPacking(b,this->body_var);
}

void Ieee80211HaLowActionFrame::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ManagementFrame::parsimUnpack(b);
    doUnpacking(b,this->body_var);
}

Ieee80211ActionFrameBody& Ieee80211HaLowActionFrame::getBody()
{
    return body_var;
}

void Ieee80211HaLowActionFrame::setBody(const Ieee80211ActionFrameBody& body)
{
    this->body_var = body;
}

}//ieee80211
}//inet


