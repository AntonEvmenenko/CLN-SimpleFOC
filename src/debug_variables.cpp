#include "debug_variables.h"

#include <SimpleFOC.h>

// float motor_shaft_angle_setpoint;
float motor_shaft_angle;
float motor_electrical_angle;
// float motor_shaft_velocity_setpoint;
// float motor_shaft_velocity;
float motor_current_q_setpoint;
float motor_current_d;
float motor_current_q;
float motor_current_a;
float motor_current_b;
float motor_voltage_d;
float motor_voltage_q;
float motor_voltage_a;
float motor_voltage_b;

extern StepperMotor motor;

void update_debug_variables() {
    // motor_shaft_angle_setpoint =       motor.shaft_angle_sp;
    motor_shaft_angle =                motor.shaft_angle;
    motor_electrical_angle =           motor.electrical_angle;
    // motor_shaft_velocity_setpoint =    motor.shaft_velocity_sp;
    // motor_shaft_velocity =             motor.shaft_velocity;
    motor_current_q_setpoint =         motor.current_sp;
    motor_current_d =                  motor.current.d;
    motor_current_q =                  motor.current.q;
    motor_voltage_d =                  motor.voltage.d;
    motor_voltage_q =                  motor.voltage.q;
}