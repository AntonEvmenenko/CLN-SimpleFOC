#ifndef SIMPLEFOC_SETUP_H
#define SIMPLEFOC_SETUP_H

#include <SimpleFOC.h>
#include <SimpleFOCDrivers.h>
#include "encoders/tle5012b/MagneticSensorTLE5012B.h"
#include "encoders/calibrated/CalibratedSensor.h"
#include "SimpleFOC_extended/LowsideCurrentSenseExtended.h"
#include "SimpleFOC_extended/StepperDriver4PWMExtended.h"
#include "SimpleFOC_extended/MagneticEncoderTLE5012B.h"

extern MagneticEncoderTLE5012B encoder;
extern CalibratedSensor encoder_calibrated;
extern LowsideCurrentSenseExtended current_sensor;
extern StepperMotor motor;
extern StepperDriver4PWMExtended driver;

void SimpleFOCInit();
void loopFOC();

#endif // SIMPLEFOC_SETUP_H