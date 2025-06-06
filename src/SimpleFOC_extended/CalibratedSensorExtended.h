#ifndef CALIBRATED_SENSOR_EXTENDED_H
#define CALIBRATED_SENSOR_EXTENDED_H

#include "encoders/calibrated/CalibratedSensor.h"

class CalibratedSensorExtended : public CalibratedSensor {
public:
    CalibratedSensorExtended(Sensor& wrapped, int n_lut = 200);

    float* getCalibrationLut();
    int getCalibrationLutSize() const;
};

#endif // CALIBRATED_SENSOR_EXTENDED_H