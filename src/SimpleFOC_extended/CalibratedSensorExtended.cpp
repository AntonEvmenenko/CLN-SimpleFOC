#include "CalibratedSensorExtended.h"

CalibratedSensorExtended::CalibratedSensorExtended(Sensor& wrapped, int n_lut) : CalibratedSensor(wrapped, n_lut) {}

float* CalibratedSensorExtended::getCalibrationLut() {
    return calibrationLut;
}

int CalibratedSensorExtended::getCalibrationLutSize() const {
    return n_lut;
}