#include "motor_calibration.h"

MotorCalibration::MotorCalibration()
{
    serialization_buffer_size = serialized_size();
    serialization_buffer = new uint8_t[serialization_buffer_size]();
}

void MotorCalibration::save_to_eeprom() {
    checksum = calculate_checksum();

    serialize(serialization_buffer);

    for (size_t i = 0; i < serialization_buffer_size; i++) {
        eeprom_buffered_write_byte(i, serialization_buffer[i]);
    }

    eeprom_buffer_flush();
}

bool MotorCalibration::load_from_eeprom() {
    eeprom_buffer_fill();

    for (size_t i = 0; i < serialization_buffer_size; i++) {
        serialization_buffer[i] = eeprom_buffered_read_byte(i);
    }

    deserialize(serialization_buffer);

    return (checksum == calculate_checksum());
}

size_t MotorCalibration::serialized_size() const {
    size_t total = 0;
    #define X(field) total += sizeof(this->field);
    SERIALIZABLE_FIELDS(X);
    #undef X
    return total;
}

void MotorCalibration::serialize(uint8_t* dst) const {
    uint8_t* p = dst;
    #define X(field) memcpy(p, &this->field, sizeof(this->field)); p += sizeof(this->field);
    SERIALIZABLE_FIELDS(X);
    #undef X
}

void MotorCalibration::deserialize(const uint8_t* src) {
    const uint8_t* p = src;
    #define X(field) memcpy(&this->field, p, sizeof(this->field)); p += sizeof(this->field);
    SERIALIZABLE_FIELDS(X);
    #undef X
}

uint8_t MotorCalibration::calculate_checksum() {
    uint8_t first_checksum = checksum;
    checksum = 0;
    serialize(serialization_buffer);
    uint8_t second_checksum = fletcher_checksum(serialization_buffer, serialization_buffer_size);
    checksum = first_checksum;
    return second_checksum;
}

uint8_t MotorCalibration::fletcher_checksum(uint8_t const * const data, uint16_t const size) const {
    uint8_t sum1 = 0;
    uint8_t sum2 = 0;
    for (uint16_t i = 0; i < size; i++) {
        sum1 += data[i];
        sum2 += sum1;
    }
    return (sum1 & 0xF) | (sum2 << 4);
}