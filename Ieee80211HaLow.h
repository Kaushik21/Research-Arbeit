/*
 * HaLow_Band.h
 *
 *  Created on: 20-Nov-2016
 *      Author: KAUSHIK NAGARAJAN
 */

#ifndef HALOW_BAND_H_
#define HALOW_BAND_H_



#include "inet/physicallayer/contract/packetlevel/IPrintableObject.h"

namespace inet {

namespace physicallayer {

namespace HaLow {
class INET_API IIeee80211HaLowBand : public IPrintableObject
{
  public:
    virtual std::ostream& printToStream(std::ostream& stream, int level) const override { return stream << "Ieee80211Band, name = " << getName(); }
    virtual const char *getName() const = 0;
    virtual int getNumChannels() const = 0;
    virtual Hz getCenterFreqency(int channelNumber) const = 0;
};

class INET_API Ieee80211HaLowBandBase : public IIeee80211HaLowBand
{
  protected:
    const char *name;

  public:
    Ieee80211HaLowBandBase(const char *name);

    virtual const char *getName() const override { return name; }
};


class INET_API Ieee80211HaLowEnumeratedBand : public Ieee80211HaLowBandBase
{
  protected:
    std::vector<Hz> centers;

  public:
    Ieee80211HaLowEnumeratedBand(const char *name, const std::vector<Hz> centers);

    virtual int getNumChannels() const override { return centers.size(); }
    virtual Hz getCenterFreqency(int channelNumber) const override;
};

class INET_API HaLow_Band
{
protected:
   static const std::vector<const IIeee80211HaLowBand *> bands;
public:
   static const Ieee80211HaLowEnumeratedBand band862MHz;

   static const IIeee80211HaLowBand *findBand(const char *name);
       static const IIeee80211HaLowBand *getBand(const char *name);
};


}

}

}





#endif /* HALOW_BAND_H_ */
