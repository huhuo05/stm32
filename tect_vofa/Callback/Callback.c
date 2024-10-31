#include "Callback.h"

extern Motor MG513_motor;
extern pids pid1;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim6) // 1000hz
	{
	}
	if (htim == &htim7) // 100hz
	{
		uint16_t pwm = PID_calc(&pid1, MG513_motor.pid1->fdb, MG513_motor.pid1->set);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}
