#include "bsp_tim.h"

void TIM_INIT(void)
{
	// pwm通道开启
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // A
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // B
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); // C
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4); // D
    // 编码器模式开启
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // A
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // B
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); // C
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL); // D
    // 定时器中断
    HAL_TIM_Base_Start_IT(&htim6);//获取编码值
	HAL_TIM_Base_Start_IT(&htim7);//pid计算
}
