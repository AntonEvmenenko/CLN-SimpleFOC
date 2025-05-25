#ifndef SIMPLEFOC_SETUP_H
#define SIMPLEFOC_SETUP_H

#include <SimpleFOC.h>
#include <SimpleFOCDrivers.h>
#include "encoders/tle5012b/MagneticSensorTLE5012B.h"
#include "SimpleFOCExtended/STM32HWEncoderExtended.h"
#include "encoders/calibrated/CalibratedSensor.h"
#include "SimpleFOCExtended/LowsideCurrentSenseExtended.h"
#include "SimpleFOCExtended/StepperDriver4PWMExtended.h"
#include "SimpleFOCExtended/MagneticEncoderTLE5012B.h"

extern MagneticEncoderTLE5012B encoder;
extern CalibratedSensor encoder_calibrated;
extern LowsideCurrentSenseExtended current_sensor;
extern StepperMotor motor;
extern StepperDriver4PWMExtended driver;

void SimpleFOCInit();
void loopFOC();

#endif // SIMPLEFOC_SETUP_H