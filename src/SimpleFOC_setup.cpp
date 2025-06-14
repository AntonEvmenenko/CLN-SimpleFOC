#include "SimpleFOC_setup.h"

#include <SimpleFOC.h>
#include <SimpleFOCDrivers.h>
#include "utilities/stm32math/STM32G4CORDICTrigFunctions.h"
#include "SimpleFOC_extended/LowsideCurrentSenseExtended.h"
#include "SimpleFOC_extended/StepperDriver4PWMExtended.h"
#include "SimpleFOC_extended/MagneticEncoderTLE5012B.h"
#include "SimpleFOC_extended/CalibratedSensorExtended.h"
#include "config.h"
#include "bsp/cln17_v2.h"
#include "motor_calibration.h"

MagneticEncoderTLE5012B encoder = MagneticEncoderTLE5012B(
    // PINOUT::ENC_MOSI, 
    // PINOUT::ENC_MISO, 
    // PINOUT::ENC_SCLK, 
    // PINOUT::ENC_CSEL
);
CalibratedSensorExtended encoder_calibrated = CalibratedSensorExtended(
    encoder, 
    ENCODER_CALIBRATION_LUT_SIZE
);
LowsideCurrentSenseExtended current_sensor = LowsideCurrentSenseExtended(
    CURRENT_SENSING::SHUNT_RESISTANCE, 
    CURRENT_SENSING::GAIN, 
    PINOUT::ISEN_A, 
    PINOUT::ISEN_B, 
    PINOUT::SYS_VSUP // This is a hack. We use third current sensing channel to measure the supply voltage
);
StepperMotor motor = StepperMotor(
    MOTOR_POLE_PAIR_NUMBER, 
    MOTOR_PHASE_RESISTANCE, 
    MOTOR_KV_RATING, 
    MOTOR_PHASE_INDUCTANCE
);
StepperDriver4PWMExtended driver = StepperDriver4PWMExtended(
    PINOUT::DRV_A1, 
    PINOUT::DRV_A2, 
    PINOUT::DRV_B1, 
    PINOUT::DRV_B2, 
    PINOUT::DRV_EN
);
MotorCalibration motor_calibration;
float supply_voltage = POWER_SUPPLY_VOLTAGE;

void initMotorParameters()
{
    // control mode
    motor.torque_controller = TorqueControlType::foc_current;
    motor.controller = MotionControlType::angle;
    // motor.controller = MotionControlType::velocity_openloop;

    // current
    motor.PID_current_q.P =     3.0f;
    motor.PID_current_q.I =     100.0f;
    motor.PID_current_d.P =     60.0f;
    motor.PID_current_d.I =     100.0f;
    motor.LPF_current_q.Tf =    0.01f;
    motor.LPF_current_d.Tf =    0.01f;

    motor.current_limit =       1.5f;

    // velocity
    motor.PID_velocity.P =      0.5f;
    motor.PID_velocity.I =      10.0f;
    motor.PID_velocity.D =      0.0f;
    motor.LPF_velocity.Tf =     0.05f;
    motor.velocity_limit =      20.0f;

    // position
    motor.P_angle.P =           10.0f;
    motor.P_angle.D =           0.01f;
}

void initSimpleFOC()
{
    Serial.println("Starting SimpleFOC");

    bool calibration_needed = button_is_pressed(PINOUT::SYS_SW1);

    if (!calibration_needed) {
        Serial.println("Reading the calibration data from EEPROM");

        if (!motor_calibration.load_from_eeprom()) {
            Serial.println("Failed to read the calibration data from EEPROM");
            Serial.println("Calibration will be performed");
            calibration_needed = true;
        }
    }

    SimpleFOC_CORDIC_Config();
    initMotorParameters();
    motor.voltage_limit = supply_voltage;
    motor.PID_current_q.limit = supply_voltage;
    motor.PID_current_d.limit = supply_voltage;

    extern uint8_t tim_downsample[5];
    for (int i = 0; i < 5; ++i) {
        tim_downsample[i] = 1;
    }

    motor.useMonitoring(Serial);
    motor.monitor_variables =  _MON_VEL; 
    motor.monitor_downsample = 10;

    SimpleFOCDebug::enable(&Serial);

    digitalWrite(PINOUT::DRV_RST, LOW);
    delay(100);
    digitalWrite(PINOUT::DRV_RST, HIGH);

    encoder.init();
    motor.linkSensor(&encoder);
    
    driver.pwm_frequency = 20000;
    driver.voltage_power_supply = supply_voltage;
    driver.voltage_limit = supply_voltage;
    driver.init();
    
    motor.linkDriver(&driver);
    current_sensor.linkDriver(&driver);
    current_sensor.skip_align = true;

    motor.voltage_sensor_align = MOTOR_SENSOR_ALIGN_VOLTAGE;

    motor.init();

    if (calibration_needed) {
        set_led_color(LED_COLOR::BLUE);
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

    encoder.setBlockingOperation(false);

    Serial.print("Current sensor A offset: ");
    Serial.println(current_sensor.offset_ia);
    Serial.print("Current sensor B offset: ");
    Serial.println(current_sensor.offset_ib);

    Serial.println("Ready");
    set_led_color(LED_COLOR::GREEN);
}

void loopFOC()
{
    supply_voltage = (current_sensor.getPhaseCurrents().c / current_sensor.gain_c + current_sensor.offset_ic) * VOLTAGE_SENSING::VM_SENSE_SCALE;
    driver.voltage_power_supply = supply_voltage;
    driver.voltage_limit = supply_voltage;
    motor.PID_current_q.limit = supply_voltage;
    motor.PID_current_d.limit = supply_voltage;
    motor.voltage_limit = supply_voltage;

    motor.loopFOC();
    motor.move();
}