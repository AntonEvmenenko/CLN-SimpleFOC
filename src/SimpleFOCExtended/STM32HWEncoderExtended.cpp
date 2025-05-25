#include "STM32HWEncoderExtended.h"

STM32HWEncoderExtended::STM32HWEncoderExtended(unsigned int _ppr, int pinA, int pinB, int pinI) : STM32HWEncoder(_ppr, pinA, pinB, pinI) {
    _pinA = digitalPinToPinName(pinA);
    _pinB = digitalPinToPinName(pinB);
    _pinI = digitalPinToPinName(pinI);
}