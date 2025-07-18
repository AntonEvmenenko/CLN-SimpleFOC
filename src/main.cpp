#include <Arduino.h>
#include "bsp/cln17_v2.h"
#include "bsp/gpio.h"
#include "bsp/fdcan.h"
#include "SimpleFOC_setup.h"
#include "config.h"
#include "CO_app_STM32.h"
#include "CANopen_setup.h"

HardwareTimer foc_timer = HardwareTimer(TIM8);
HardwareTimer canopen_timer = HardwareTimer(TIM17);

void foc_timer_interrupt() {
    // set_debug_pin();
    loopFOC();
    // reset_debug_pin();
}

void canopen_interrupt() {
    // set_debug_pin();
    canopen_app_interrupt();
    // reset_debug_pin();
}

void timers_init() {
    foc_timer.setOverflow(FOC_LOOP_FREQUENCY, HERTZ_FORMAT);
    foc_timer.attachInterrupt(foc_timer_interrupt);
    foc_timer.setInterruptPriority(0, 0);

    canopen_timer.setOverflow(CANOPEN_TIMER_FREQUENCY, HERTZ_FORMAT);
    canopen_timer.attachInterrupt(canopen_interrupt);
    canopen_timer.setInterruptPriority(1, 0);
}

void setup() {
    Serial.begin(115200);
    // delay(5000);

    GPIO_init();
    FDCAN1_init();
    timers_init();

    CANopen_init(&hfdcan1, FDCAN1_init, canopen_timer.getHandle(), CANOPEN_NODE_ID, CANOPEN_BAUDRATE);
    SimpleFOC_init();

    foc_timer.resume();
}

void loop() {
    // set_debug_pin();
    canopen_app_process();
    // reset_debug_pin();
}