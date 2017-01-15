/*
 * Ieee80211HaLowMgmtFrames_m.cc
 *
 *  Created on: 10-Jan-2017
 *      Author: KAUSHIK NAGARAJAN
 */



#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"
#include "Ieee80211HaLowMgmtFrames_m.h"

USING_NAMESPACE


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


Register_Class(Ieee80211HaLowAssociationResponseFrameBody);

Ieee80211HaLowAssociationResponseFrameBody::Ieee80211HaLowAssociationResponseFrameBody() : ::inet::ieee80211::Ieee80211FrameBody()
{
    this->setBodyLength(26);

    this->statusCode_var = 0;
    this->aid_var = 0;
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
    doPacking(b,this->supportedRates_var);
    doPacking(b,this->AssociationID_var);
}

void Ieee80211HaLowAssociationResponseFrameBody::parsimUnpack(cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211FrameBody::parsimUnpack(b);
    doUnpacking(b,this->statusCode_var);
    doUnpacking(b,this->aid_var);
    doUnpacking(b,this->supportedRates_var);
    doUnpacking(b,this->AssociationID_var);

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

int Ieee80211HaLowAssociationResponseFrameBody::getassociationID() const
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
        case 2: return long2string(pp->getassociationID());
        case 3: {std::stringstream out; out << pp->getSupportedRates(); return out.str();}
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
        case 2: pp->getassociationID(string2long(value)); return true;
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
        case 3: return opp_typename(typeid(Ieee80211SupportedRatesElement));
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
    this->setType(ST_ASSOCIATIONREQUEST);
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


}//ieee80211
}//inet
