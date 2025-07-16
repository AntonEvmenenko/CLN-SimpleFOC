#include "CANopen_setup.h"

void CANopen_init(FDCAN_HandleTypeDef* can_handle, void (*hw_init_function)(), TIM_HandleTypeDef* timer_handle, uint8_t desired_node_it, uint16_t can_baudrate)
{
    CANopenNodeSTM32 canOpenNodeSTM32;
    canOpenNodeSTM32.CANHandle = can_handle;
    canOpenNodeSTM32.HWInitFunction = hw_init_function;
    canOpenNodeSTM32.timerHandle = timer_handle;
    canOpenNodeSTM32.desiredNodeID = desired_node_it;
    canOpenNodeSTM32.baudrate = can_baudrate; // kbit/s
    canopen_app_init(&canOpenNodeSTM32);
}