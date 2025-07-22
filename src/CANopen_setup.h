#ifndef CANOPEN_SETUP_H
#define CANOPEN_SETUP_H

#include "CO_app_STM32.h"

void CANopen_init(
    FDCAN_HandleTypeDef* can_handle, 
    void (*hw_init_function)(), 
    TIM_HandleTypeDef* timer_handle, 
    uint8_t desired_node_it, 
    uint16_t can_baudrate, 
    void (*sync_callback)(void *object)
);

#endif // CANOPEN_SETUP_H