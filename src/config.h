#ifndef CONFIG_H
#define CONFIG_H

// Motor

#define MOTOR_POLE_PAIR_NUMBER      50
#define MOTOR_PHASE_RESISTANCE      1.3f // [Ohms]
#define MOTOR_KV_RATING             NOT_SET // [RPM/V] (RMS value)
#define MOTOR_PHASE_INDUCTANCE      0.0024f // [H]
#define MOTOR_SENSOR_ALIGN_VOLTAGE  5.0f // [V]

// Encoder

#define ENCODER_CALIBRATION_LUT_SIZE    200

#endif // CONFIG_H