#include "SimpleFOC_setup.h"

#include "config.h"
#include "bsp/cln17_v2.h"
#include "motor_calibration.h"

#define POWER_SUPPLY_VOLTAGE 12.0f

MagneticEncoderTLE5012B encoder(PINOUT::ENC_MOSI, PINOUT::ENC_MISO, PINOUT::ENC_SCLK, PINOUT::ENC_CSEL);
CalibratedSensorExtended encoder_calibrated = CalibratedSensorExtended(encoder, ENCODER_CALIBRATION_LUT_SIZE);
LowsideCurrentSenseExtended current_sensor = LowsideCurrentSenseExtended(CURRENT_SENSING::SHUNT_RESISTANCE, CURRENT_SENSING::GAIN, PINOUT::ISEN_A, PINOUT::ISEN_B, _NC);
StepperMotor motor = StepperMotor(MOTOR_POLE_PAIR_NUMBER, MOTOR_PHASE_RESISTANCE, MOTOR_KV_RATING, MOTOR_PHASE_INDUCTANCE);
StepperDriver4PWMExtended driver = StepperDriver4PWMExtended(PINOUT::DRV_A1, PINOUT::DRV_A2, PINOUT::DRV_B1, PINOUT::DRV_B2, PINOUT::DRV_EN);

MotorCalibration motor_calibration;

void SimpleFOCInit(bool calibration_needed)
{
    Serial.println("Starting SimpleFOC");

    if (!calibration_needed) {
        Serial.println("Reading the calibration data from EEPROM");

        if (!motor_calibration.load_from_eeprom()) {
            Serial.println("Failed to read the calibration data from EEPROM");
            Serial.println("Calibration will be performed");
            calibration_needed = true;
        }
    }

    motor.torque_controller = TorqueControlType::foc_current;
    motor.controller = MotionControlType::angle;
    // motor.controller = MotionControlType::velocity_openloop;

    // voltage
    motor.voltage_limit = POWER_SUPPLY_VOLTAGE;

    // current
    motor.PID_current_q.P = 3;
    motor.PID_current_q.I = 100;
    motor.PID_current_d.P = 3;
    motor.PID_current_d.I = 100;
    motor.LPF_current_q.Tf = 0.01;
    motor.LPF_current_d.Tf = 0.01;
    motor.PID_current_q.limit = POWER_SUPPLY_VOLTAGE;
    motor.PID_current_d.limit = POWER_SUPPLY_VOLTAGE;
    motor.current_limit = 1.5f;

    // velocity
    motor.PID_velocity.P = 0.5;
    motor.PID_velocity.I = 10;
    motor.PID_velocity.D = 0.0f;
    motor.LPF_velocity.Tf = 0.05;
    motor.velocity_limit = 20;

    // position
    motor.P_angle.P = 10.0f;
    motor.P_angle.D = 0.01f;

    extern uint8_t tim_downsample[5];
    for (int i = 0; i < 5; ++i) {
        tim_downsample[i] = 1;
    }

    motor.useMonitoring(Serial);
    motor.monitor_variables =  _MON_VEL; 
    motor.monitor_downsample = 10;

    SimpleFOCDebug::enable(&Serial);

    pinMode(PINOUT::DRV_RST, OUTPUT);
    digitalWrite(PINOUT::DRV_RST, LOW);
    delay(100);
    digitalWrite(PINOUT::DRV_RST, HIGH);
    pinMode(PINOUT::DRV_ERR, INPUT_PULLUP);

    encoder.init();
    motor.linkSensor(&encoder);
    
    driver.pwm_frequency = 20000;
    driver.voltage_power_supply = POWER_SUPPLY_VOLTAGE;
    driver.voltage_limit = POWER_SUPPLY_VOLTAGE;
    driver.init();
    
    motor.linkDriver(&driver);
    current_sensor.linkDriver(&driver);
    current_sensor.skip_align = true;

    motor.voltage_sensor_align = MOTOR_SENSOR_ALIGN_VOLTAGE;

    motor.init();

    if (calibration_needed) {
        encoder_calibrated.voltage_calibration = MOTOR_SENSOR_ALIGN_VOLTAGE;
        encoder_calibrated.calibrate(motor);
        memcpy(motor_calibration.encoder_calibration_lut, encoder_calibrated.getCalibrationLut(), ENCODER_CALIBRATION_LUT_SIZE * sizeof(float));
        motor_calibration.zero_electric_angle = motor.zero_electric_angle;
        motor_calibration.sensor_derection = motor.sensor_direction;
        motor_calibration.save_to_eeprom();
        Serial.println("Calibration data saved to EEPROM");
    } else {
        encoder_calibrated.calibrate(motor, motor_calibration.encoder_calibration_lut, motor_calibration.zero_electric_angle, motor_calibration.sensor_derection);
    }
    
    motor.linkSensor(&encoder_calibrated);

    current_sensor.init();
    motor.linkCurrentSense(&current_sensor);

    motor.initFOC();

    Serial.print("Current sensor A offset: ");
    Serial.println(current_sensor.offset_ia);
    Serial.print("Current sensor B offset: ");
    Serial.println(current_sensor.offset_ib);
}

void loopFOC()
{
    motor.loopFOC();
    motor.move();
}