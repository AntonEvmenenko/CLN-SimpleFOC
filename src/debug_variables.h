#ifndef DEBUG_VARIABLES_H
#define DEBUG_VARIABLES_H

// extern float motor_shaft_angle_setpoint;
extern float motor_shaft_angle;
extern float motor_electrical_angle;
// extern float motor_shaft_velocity_setpoint;
// extern float motor_shaft_velocity;
extern float motor_current_q_setpoint;
extern float motor_current_d;
extern float motor_current_q;
extern float motor_current_a;
extern float motor_current_b;
extern float motor_voltage_d;
extern float motor_voltage_q;
extern float motor_voltage_a;
extern float motor_voltage_b;

void update_debug_variables();
    
#endif /* DEBUG_VARIABLES_H */
