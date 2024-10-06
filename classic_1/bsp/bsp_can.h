#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "can.h"
#include "main.h"

// void Classis_can_init(void);
void Classis_can_init(CAN_HandleTypeDef *_canHandler, uint32_t _FIFO, uint32_t _FIFOMask);

#endif
