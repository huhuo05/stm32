#include "Callback.h"

extern uint8_t RxData[8];
extern Motor MG513_motor;
extern pids pid1;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim6) // 1000hz
	{
		motor_speed_get(&MG513_motor);
	}
	if (htim == &htim7) // 100hz
	{
		uint16_t pwm = PID_calc(MG513_motor.pid1, MG513_motor.pid1->fdb, MG513_motor.pid1->set);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, pwm);
		printf("%d\n",pwm);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
		uint8_t RxData[8] = {0};
		HAL_UART_Receive_IT(&huart1, RxData, 8);
		printf("RxData:%s\n", RxData);
	}
}


