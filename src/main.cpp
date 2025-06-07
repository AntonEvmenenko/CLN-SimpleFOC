#include <Arduino.h>
#include "bsp/cln17_v2.h"
#include "SimpleFOC_setup.h"

// HardwareTimer timer = HardwareTimer(TIM8);

// void timerInterrupt() {
//     loopFOC();
// }

void setup() {
    init_pins();
    Serial.begin(115200);
    // delay(5000);
    initSimpleFOC();

    // timer.setOverflow(5000, HERTZ_FORMAT);
    // timer.attachInterrupt(timerInterrupt);
    // timer.resume();
}

void loop() {
    loopFOC();
    // current_sensor.getPhaseCurrents();
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
}