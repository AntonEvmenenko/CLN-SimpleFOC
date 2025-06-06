#include "MagneticEncoderTLE5012B.h"

#define _2PI 6.28318530718f
#define TLE5012B_CPR 32768.0f

MagneticEncoderTLE5012B::MagneticEncoderTLE5012B(int mosi, int miso, int sclk, int cs) : spi(mosi, miso, sclk), cs(cs) {};

void MagneticEncoderTLE5012B::init() {
    spi.begin();
    spi.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE1));
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
};

float MagneticEncoderTLE5012B::getSensorAngle() {
    digitalWrite(cs, LOW); // Start spi
    spi.transfer16(0x8020); // Send command word
    uint16_t respond = spi.transfer16(0x0000); // Recieve position
    digitalWrite(cs, HIGH); // End spi
    respond = respond & 0x7FFF; // Remove useless bit
    return respond * _2PI / TLE5012B_CPR; // Convert to radians
};
