#include "gpio.h"

#include <Arduino.h>
#include "cln17_v2.h"

void GPIO_init() {
    pinMode(PINOUT::DEBUG_PIN, OUTPUT);
    pinMode(PINOUT::SYS_SW1, INPUT_PULLUP);
    pinMode(PINOUT::LED_RED, OUTPUT);
    pinMode(PINOUT::LED_GRN, OUTPUT);
    pinMode(PINOUT::LED_BLU, OUTPUT);
    pinMode(PINOUT::DRV_RST, OUTPUT);
    pinMode(PINOUT::DRV_ERR, INPUT_PULLUP);
    pinMode(PINOUT::CAN_IO, OUTPUT);
    pinMode(PINOUT::CAN_SD, OUTPUT);
}