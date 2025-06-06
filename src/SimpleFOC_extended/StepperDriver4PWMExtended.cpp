#include "StepperDriver4PWMExtended.h"

StepperDriver4PWMExtended::StepperDriver4PWMExtended(int ph1A,int ph1B,int ph2A,int ph2B,int en1, int en2) : StepperDriver4PWM(ph1A, ph1B, ph2A, ph2B, en1, en2) {
}

void StepperDriver4PWMExtended::setPwm(float Ua_, float Ub_) {
  Ua = Ua_;
  Ub = Ub_;

  StepperDriver4PWM::setPwm(Ua, Ub);
}