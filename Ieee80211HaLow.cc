#include "Ieee80211HaLow.h"
#include "inet/physicallayer/ieee80211/mode/Ieee80211Band.h"

namespace inet {

namespace physicallayer {

namespace HaLow {

Ieee80211HaLowBandBase::Ieee80211HaLowBandBase(const char *name) :
    name(name)
{
}

Ieee80211HaLowEnumeratedBand::Ieee80211HaLowEnumeratedBand(const char *name, const std::vector<Hz> centers) :
    Ieee80211HaLowBandBase(name),
    centers(centers)
{
}

Hz Ieee80211HaLowEnumeratedBand::getCenterFreqency(int channelNumber) const
{
    if (channelNumber < 0 || channelNumber >= (int)centers.size())
        throw cRuntimeError("Invalid channel number: %d", channelNumber);
    return centers[channelNumber];
}

const Ieee80211HaLowEnumeratedBand HaLow_Band::band862MHz("862 MHz",
{
       MHz(864), //1
       MHz(866), //2
       MHz(868), //3
       MHz(870), //4

});


const std::vector<const IIeee80211HaLowBand *> HaLow_Band::bands = {&band862MHz};

}
}

}
