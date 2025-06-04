#include "LowsideCurrentSenseExtended.h"

#include "StepperDriver4PWMExtended.h"

LowsideCurrentSenseExtended::LowsideCurrentSenseExtended(float _shunt_resistor, float _gain, int _pinA, int _pinB, int _pinC) : LowsideCurrentSense(_shunt_resistor, _gain, _pinA, _pinB, _pinC) {
}

PhaseCurrent_s LowsideCurrentSenseExtended::getPhaseCurrents(){
    PhaseCurrent_s current = LowsideCurrentSense::getPhaseCurrents();
    
    if (driver_type == DriverType::Stepper){
        static StepperDriver4PWMExtended *d = static_cast<StepperDriver4PWMExtended*>(driver);
        current.a *= _sign(d->Ua);
        current.b *= _sign(d->Ub);
    }

    this->current = current;
    return current;
}
