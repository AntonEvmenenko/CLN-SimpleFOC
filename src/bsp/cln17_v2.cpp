#include "cln17_v2.h"

void init_pins() {
    pinMode(PINOUT::DEBUG_PIN, OUTPUT);
    pinMode(PINOUT::SYS_SW1, INPUT_PULLUP);
    pinMode(PINOUT::LED_RED, OUTPUT);
    pinMode(PINOUT::LED_GRN, OUTPUT);
    pinMode(PINOUT::LED_BLU, OUTPUT);
    pinMode(PINOUT::DRV_RST, OUTPUT);
    pinMode(PINOUT::DRV_ERR, INPUT_PULLUP);
}

bool button_is_pressed(int button_pin) {
    return digitalRead(button_pin) == LOW;
}

void set_led_color(LED_COLOR color) {
    // Turn off all LEDs first (HIGH = OFF)
    digitalWrite(PINOUT::LED_RED, HIGH);
    digitalWrite(PINOUT::LED_GRN, HIGH);
    digitalWrite(PINOUT::LED_BLU, HIGH);

    // Turn on the selected color (LOW = ON)
    switch (color) {
    case LED_COLOR::RED:
        digitalWrite(PINOUT::LED_RED, LOW);
        break;
    case LED_COLOR::GREEN:
        digitalWrite(PINOUT::LED_GRN, LOW);
        break;
    case LED_COLOR::BLUE:
        digitalWrite(PINOUT::LED_BLU, LOW);
        break;
    default:
        // Unknown color — keep all LEDs off
        break;
    }
}