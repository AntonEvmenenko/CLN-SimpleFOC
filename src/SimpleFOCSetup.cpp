#include "SimpleFOCSetup.h"

#include "motor_config.h"
#include "target/cln17_v2/target.h"

#define POWER_SUPPLY_VOLTAGE 12.0f
#define SENSOR_ALIGN_VOLTAGE 4.0f
#define CURRENT_SENSOR_SHUNT_RESISTANCE 0.025f // [Ohm]
#define CURRENT_SENSOR_GAIN 20.0f // [V/V]

float encoder_calibration_lut[200] = {0.000503, 0.000720, 0.000977, 0.001431, 0.001668, 0.001886, 0.002104, 0.002578, 0.002834, 0.003090, 0.003270, 0.003648, 0.003808, 0.003968, 0.004167, 0.004390, 0.004473, 0.004536, 0.004522, 0.004514, 0.004481, 0.004428, 0.004395, 0.004214, 0.004105, 0.003937, 0.003713, 0.003283, 0.003000, 0.002718, 0.002512, 0.001967, 0.001685, 0.001441, 0.001139, 0.000556, 0.000273, -0.000047, -0.000368, -0.001028, -0.001330, -0.001612, -0.001913, -0.002516, -0.002818, -0.003061, -0.003305, -0.003582, -0.003596, -0.003610, -0.003547, -0.003441, -0.003435, -0.003391, -0.003348, -0.003337, -0.003312, -0.003326, -0.003321, -0.003253, -0.003190, -0.003108, -0.003026, -0.002842, -0.002741, -0.002602, -0.002462, -0.002144, -0.002005, -0.001865, -0.001764, -0.001485, -0.001403, -0.001302, -0.001200, -0.001094, -0.001012, -0.000949, -0.000828, -0.000626, -0.000544, -0.000443, -0.000380, -0.000197, -0.000095, -0.000032, 0.000069, 0.000214, 0.000296, 0.000416, 0.000537, 0.000873, 0.000994, 0.001133, 0.001254, 0.001667, 0.001941, 0.002196, 0.002508, 0.003017, 0.003329, 0.003622, 0.003915, 0.004539, 0.004775, 0.005049, 0.005342, 0.005928, 0.006182, 0.006399, 0.006577, 0.006837, 0.006976, 0.007097, 0.007179, 0.007343, 0.007367, 0.007334, 0.007282, 0.007063, 0.006934, 0.006786, 0.006580, 0.006150, 0.005868, 0.005585, 0.005303, 0.004643, 0.004284, 0.003886, 0.003470, 0.002656, 0.002240, 0.001804, 0.001349, 0.000439, 0.000004, -0.000470, -0.000867, -0.001758, -0.002232, -0.002648, -0.003103, -0.003879, -0.004257, -0.004597, -0.004898, -0.005367, -0.005476, -0.005548, -0.005562, -0.005570, -0.005603, -0.005636, -0.005688, -0.005716, -0.005730, -0.005724, -0.005738, -0.005727, -0.005684, -0.005640, -0.005539, -0.005260, -0.005120, -0.004980, -0.004802, -0.004523, -0.004345, -0.004167, -0.004009, -0.003653, -0.003494, -0.003355, -0.003234, -0.002993, -0.002854, -0.002785, -0.002716, -0.002613, -0.002527, -0.002424, -0.002340, -0.002135, -0.002032, -0.001929, -0.001769, -0.001583, -0.001518, -0.001454, -0.001409, -0.001261, -0.001139, -0.001017, -0.000952, -0.000709, -0.000529, -0.000311, -0.000074, 0.000323};
float zero_electric_angle = 0.293368;
Direction sensor_direction = Direction::CCW;

MagneticEncoderTLE5012B encoder(PINOUT::ENC_MOSI, PINOUT::ENC_MISO, PINOUT::ENC_SCLK, PINOUT::ENC_CSEL);
CalibratedSensor encoder_calibrated = CalibratedSensor(encoder);
LowsideCurrentSenseExtended current_sensor = LowsideCurrentSenseExtended(CURRENT_SENSOR_SHUNT_RESISTANCE, CURRENT_SENSOR_GAIN, PINOUT::ISEN_A, PINOUT::ISEN_B, _NC);
StepperMotor motor = StepperMotor(MOTOR_POLE_PAIR_NUMBER, MOTOR_PHASE_RESISTANCE, MOTOR_KV_RATING, MOTOR_PHASE_INDUCTANCE);
StepperDriver4PWMExtended driver = StepperDriver4PWMExtended(PINOUT::DRV_A1, PINOUT::DRV_A2, PINOUT::DRV_B1, PINOUT::DRV_B2, PINOUT::DRV_EN);

void SimpleFOCInit() 
{
    Serial.println("Starting SimpleFOC");

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
    // current_sensor.skip_align = true;

    motor.voltage_sensor_align = SENSOR_ALIGN_VOLTAGE;

    motor.torque_controller = TorqueControlType::foc_current;
    motor.controller = MotionControlType::torque;

    motor.PID_current_q.P = 3;
    motor.PID_current_q.I = 100;
    motor.PID_current_d.P = 3;
    motor.PID_current_d.I = 100;
    motor.LPF_current_q.Tf = 0.01;
    motor.LPF_current_d.Tf = 0.01;
    motor.PID_current_q.limit = POWER_SUPPLY_VOLTAGE;
    motor.PID_current_d.limit = POWER_SUPPLY_VOLTAGE;
    motor.voltage_limit = POWER_SUPPLY_VOLTAGE;

    motor.init();

    encoder_calibrated.voltage_calibration = SENSOR_ALIGN_VOLTAGE;
    encoder_calibrated.calibrate(motor/*, encoder_calibration_lut, zero_electric_angle, sensor_direction*/);
    motor.linkSensor(&encoder_calibrated);

    current_sensor.init();
    motor.linkCurrentSense(&current_sensor);

    motor.initFOC();

    Serial.print("Current sensor A offset: ");
    Serial.println(current_sensor.offset_ia);
    Serial.print("Current sensor B offset: ");
    Serial.println(current_sensor.offset_ib);

    motor.target = 0.0f;
}

void loopFOC()
{
    motor.loopFOC();
    motor.move();
}