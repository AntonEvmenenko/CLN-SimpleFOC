#ifndef MOTOR_CALIBRATION_H
#define MOTOR_CALIBRATION_H

#include <SimpleFOC.h>
#include <EEPROM.h>
#include "config.h"

#define SERIALIZABLE_FIELDS(X)  \
    X(encoder_calibration_lut)  \
    X(zero_electric_angle)      \
    X(sensor_derection)         \
    X(checksum)

class MotorCalibration {
public:
    MotorCalibration();
    
    float encoder_calibration_lut[ENCODER_CALIBRATION_LUT_SIZE];
    float zero_electric_angle;
    Direction sensor_derection;
    uint8_t checksum;

    void save_to_eeprom();
    bool load_from_eeprom();

private:
    size_t serialized_size() const;
    void serialize(uint8_t* dst) const;
    void deserialize(const uint8_t* src);

    uint8_t calculate_checksum();
    uint8_t fletcher_checksum(uint8_t const * const data, uint16_t const size) const;

    uint8_t* serialization_buffer;
    size_t serialization_buffer_size;
};

static_assert(sizeof(MotorCalibration) < E2END, "MotorCalibration structure does not fit into EEPROM!");

#endif // MOTOR_CALIBRATION_H