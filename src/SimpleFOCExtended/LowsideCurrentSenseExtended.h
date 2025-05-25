#ifndef LOWSIDE_CS_LIB_EXTENDED_H
#define LOWSIDE_CS_LIB_EXTENDED_H

#include "current_sense/LowsideCurrentSense.h"

class LowsideCurrentSenseExtended: public LowsideCurrentSense {
  public:
    LowsideCurrentSenseExtended(float shunt_resistor, float gain, int pinA, int pinB, int pinC = _NC);
    PhaseCurrent_s getPhaseCurrents() override;
};

#endif // LOWSIDE_CS_LIB_EXTENDED_H
