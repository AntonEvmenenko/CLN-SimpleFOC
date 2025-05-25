#ifndef STM32_HW_ENCODER_EXTENDED_H
#define STM32_HW_ENCODER_EXTENDED_H

#include "encoders/stm32hwencoder/STM32HWEncoder.h"

class STM32HWEncoderExtended : public STM32HWEncoder {
  public:
    STM32HWEncoderExtended(unsigned int ppr, int pinA, int pinB, int pinI=-1);
};

#endif // STM32_HW_ENCODER_EXTENDED_H