
#ifndef MAGNETIC_ENCODER_TLE5012B_H
#define MAGNETIC_ENCODER_TLE5012B_H

#include "common/base_classes/Sensor.h"
#include <SPI.h>

class MagneticEncoderTLE5012B : public Sensor {
public:
    MagneticEncoderTLE5012B(/*int mosi, int miso, int sclk, int cs*/);
    virtual void init() override;
    virtual float getSensorAngle() override;
    void requestAngle();
    void setBlockingOperation(bool blocking);
private:
    // Encoder can work in two modes, blocking and non-blocking. Non-blocking one uses
    // less MCU time, as it is interrupt-based, but introduces a slight angle time lag
    // Default mode is blocking
    bool blocking = true;
};

#endif // MAGNETIC_ENCODER_TLE5012B_H
