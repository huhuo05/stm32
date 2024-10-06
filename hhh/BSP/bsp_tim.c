#include "bsp_tim.h"

void TIM_INIT(void)
{
	// pwmͨ������
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // A
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // B
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); // C
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4); // D
    // ������ģʽ����
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // A
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // B
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); // C
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL); // D
    // ��ʱ���ж�
    HAL_TIM_Base_Start_IT(&htim6);//��ȡ����ֵ
	HAL_TIM_Base_Start_IT(&htim7);//pid����
}
