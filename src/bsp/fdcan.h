#ifndef FDCAN_H
#define FDCAN_H

#include "stm32g4xx_hal_fdcan.h"

extern FDCAN_HandleTypeDef hfdcan1;

void FDCAN1_init(void);

#endif // FDCAN_H