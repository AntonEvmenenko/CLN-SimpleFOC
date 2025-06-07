#define TARGET_CLN17_V2

#include <Arduino.h>
#include "led_color.h"

namespace PINOUT {
    // Encoder
    // TODO these pins are not actually used, all the pins are hardcoded inside the MagneticEncoderTLE5012B class
    constexpr int ENC_MOSI = PA7;
    constexpr int ENC_MISO = PA6;
    constexpr int ENC_SCLK = PA5;
    constexpr int ENC_CSEL = PC4;

    // LED
    constexpr int LED_RED = PB13;  // OUTPUT; HIGH = OFF, LOW = ON
    constexpr int LED_GRN = PB14;  // OUTPUT; HIGH = OFF, LOW = ON
    constexpr int LED_BLU = PB15;  // OUTPUT; HIGH = OFF, LOW = ON

    // Motor Driver
    constexpr int ISEN_A = PA3;
    constexpr int ISEN_B = PB0;
    constexpr int DRV_RST = PB2;
    constexpr int DRV_ERR = PB1;
    constexpr int DRV_EN = PA4;
    constexpr int DRV_A1 = PA0;
    constexpr int DRV_A2 = PA1;
    constexpr int DRV_B1 = PB10;
    constexpr int DRV_B2 = PB11;

    // Buttons
    constexpr int SYS_SW1 = PA_15;  // INPUT_PULLUP; LOW = PRESSED
    // constexpr int SYS_SW2 = PB_7;   // INPUT_PULLUP; LOW = PRESSED

    constexpr int DEBUG_PIN = PC10;

    // // Ststem telemetry
    // constexpr PinName SYS_VSUP = PA_2;       // INPUT_ANALOG
    // constexpr PinName SYS_VREF = PADC_VREF;  // Core VREF voltage ADC
    // constexpr PinName SYS_TEMP = PADC_TEMP;  // Core VTEMP temperature ADC

    // // CTRL connector
    // constexpr PinName CTRL_ENB = PA_8;   // ENB / 5V / SCL / CS   / 5V
    // constexpr PinName CTRL_STP = PB_5;   // DIR / CK / SDA / MOSI / A
    // constexpr PinName CTRL_DIR = PB_4;   // STP / RX / RX  / MISO / B
    // constexpr PinName CTRL_ERR = PB_3;   // ERR / TX / TX  / SCK  / Z
    // constexpr PinName CTRL_5VO = PB_12;  // 5V output on ENB, OPEN-DRAIN Logic

    // // Expansion connector
    // constexpr PinName EXP_TX = PC_10;  // UART3 RX
    // constexpr PinName EXP_RX = PC_11;  // UART3 TX

    // // CAN-Bus interface
    // constexpr PinName CAN_RX = PB_8;   // Recieve line
    // constexpr PinName CAN_TX = PB_9;   // Trancieve line
    // constexpr PinName CAN_SD = PA_9;   // Shutdown pin (ACTIVE LOW)
    // constexpr PinName CAN_IO = PA_10;  // HIGH for (VIO or EN) or HIGH-Z for (VREF)

    // // USB interface
    // constexpr PinName USB_USB_DP = PA_12;
    // constexpr PinName USB_USB_DN = PA_11;
}

namespace CURRENT_SENSING {
    constexpr float SHUNT_RESISTANCE  = 0.025f; // [Ohm]
    constexpr float GAIN = 20.0f; // [V/V]
}

void init_pins();
bool button_is_pressed(int button_pin);
void set_led_color(LED_COLOR color);