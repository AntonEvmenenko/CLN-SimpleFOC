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
    canopen_app_interrupt();
}

void setup() {
    GPIO_init();
    FDCAN1_init();

    foc_timer.setOverflow(FOC_LOOP_FREQUENCY, HERTZ_FORMAT);
    foc_timer.attachInterrupt(foc_timer_interrupt);

    canopen_timer.setOverflow(CANOPEN_TIMER_FREQUENCY, HERTZ_FORMAT);
    canopen_timer.attachInterrupt(canopen_interrupt);

    CANopen_init(&hfdcan1, FDCAN1_init, canopen_timer.getHandle(), CANOPEN_NODE_ID, CANOPEN_BAUDRATE);

    Serial.begin(115200);
    // delay(5000);
    SimpleFOC_init();

    foc_timer.resume();
}

void loop() {
    // loopFOC();
    // current_sensor.getPhaseCurrents();
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
    canopen_app_process();
}