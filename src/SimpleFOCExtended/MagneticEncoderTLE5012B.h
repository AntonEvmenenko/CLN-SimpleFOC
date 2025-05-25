
#ifndef MAGNETIC_ENCODER_TLE5012B_H
#define MAGNETIC_ENCODER_TLE5012B_H

#include "common/base_classes/Sensor.h"
#include <SPI.h>

class MagneticEncoderTLE5012B : public Sensor {
    public:
        MagneticEncoderTLE5012B(int mosi, int miso, int sclk, int cs);
        virtual void init() override;
        virtual float getSensorAngle() override;

    private:
        SPIClass spi;
        int cs;
};

#endif // MAGNETIC_ENCODER_TLE5012B_H
