#ifndef STEPPER_DRIVER_4PWM_EXTENDED_H
#define STEPPER_DRIVER_4PWM_EXTENDED_H

#include "drivers/StepperDriver4PWM.h"

class StepperDriver4PWMExtended: public StepperDriver4PWM
{
  public:
    StepperDriver4PWMExtended(int ph1A,int ph1B,int ph2A,int ph2B, int en1 = NOT_SET, int en2 = NOT_SET);
    
    void setPwm(float Ua, float Ub) override;

    float Ua;
    float Ub;
};


#endif // STEPPER_DRIVER_4PWM_EXTENDED_H
