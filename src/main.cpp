#include <Arduino.h>
#include "bsp/cln17_v2.h"
#include "SimpleFOC_setup.h"
#include "config.h"

HardwareTimer foc_timer = HardwareTimer(TIM8);

void foc_timer_interrupt() {
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
    loopFOC();
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
}

void setup() {
    init_pins();
    Serial.begin(115200);
    // delay(5000);
    initSimpleFOC();

    foc_timer.setOverflow(FOC_LOOP_FREQUENCY, HERTZ_FORMAT);
    foc_timer.attachInterrupt(foc_timer_interrupt);
    foc_timer.resume();
}

void loop() {
    runCommander();
    // loopFOC();
    // current_sensor.getPhaseCurrents();
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
}