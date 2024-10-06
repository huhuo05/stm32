#ifndef PRINT_TO_PC_H
#define PRINT_TO_PC_H

#include "gpio.h"
#include "usart.h"
#include "bsp_usart.h"
#include "APP_classis.h"


void print_to_PC_Transmit(UART_HandleTypeDef *_huart, CLASSIC *_group);
void commond_to_change(UART_HandleTypeDef *_huart);

#endif
