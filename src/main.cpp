#include <Arduino.h>
#include "target/cln17_v2/target.h"
#include "debug_variables.h"
#include "SimpleFOCSetup.h"

// HardwareTimer timer = HardwareTimer(TIM8);

// void timerInterrupt() {
//     loopFOC();
// }

void setup() {
    Serial.begin(9600);
    delay(2000);
    pinMode(PINOUT::DEBUG_PIN, OUTPUT);
    SimpleFOCInit();

    // timer.setOverflow(5000, HERTZ_FORMAT);
    // timer.attachInterrupt(timerInterrupt);
    // timer.resume();
}

float motor_torque_setpoint = 0.0f;

void loop() {
    loopFOC();
    motor.target = motor_torque_setpoint;
    update_debug_variables();
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
}