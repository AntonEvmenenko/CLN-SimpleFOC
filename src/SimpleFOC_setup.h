#ifndef SIMPLEFOC_SETUP_H
#define SIMPLEFOC_SETUP_H

#include <SimpleFOC.h>
// #include <SimpleFOCDrivers.h>
// #include "SimpleFOC_extended/MagneticEncoderTLE5012B.h"
// #include "SimpleFOC_extended/LowsideCurrentSenseExtended.h"
// #include "SimpleFOC_extended/StepperDriver4PWMExtended.h"
// #include "SimpleFOC_extended/MagneticEncoderTLE5012B.h"
// #include "SimpleFOC_extended/CalibratedSensorExtended.h"

// extern MagneticEncoderTLE5012B encoder;
// extern CalibratedSensorExtended encoder_calibrated;
// extern LowsideCurrentSenseExtended current_sensor;
extern StepperMotor motor;
// extern StepperDriver4PWMExtended driver;

void SimpleFOC_init();
void loopFOC();

#endif // SIMPLEFOC_SETUP_H