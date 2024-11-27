#ifndef __Callback_h
#define __Callback_h

#include "tim.h"
#include "usart.h"
#include "motor.h"
#include "main.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
