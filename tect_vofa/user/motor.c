#include "motor.h"

void motor_init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
    // 100hz
    HAL_TIM_Base_Start_IT(&htim6);
}

void motor_pid_init(Motor *motor, pids *pid, uint8_t motor_mode, uint8_t pid_mode, fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout)
{
    if (motor->motor_mode != MOTOR_POSITION)
    {
        motor->motor_mode = motor_mode;
    } // 电机模式
    switch (motor->motor_mode)
    {
    case MOTOR_SPEED:
    {
        motor->pid1 = pid;
        motor->pid1->mode = pid_mode;
        motor->pid1->Kp = KP;
        motor->pid1->Ki = KI;
        motor->pid1->Kd = KD;
        motor->pid1->max_out = maxOut;
        motor->pid1->max_iout = maxIout;
    }
    break;
    case MOTOR_POSITION:
    {
        motor->pid2 = pid;
        motor->pid2->mode = pid_mode;
        motor->pid2->Kp = KP;
        motor->pid2->Ki = KI;
        motor->pid2->Kd = KD;
        motor->pid2->max_out = maxOut;
        motor->pid2->max_iout = maxIout;
    }
    break;
    default:
        break;
    }
}

void motor_speed_cal(Motor *motor)
{
    // 滤波
    uint32_t a = 0;
    uint32_t temp[10] = {0};
    temp[9] = temp[8];
    temp[8] = temp[7];
    temp[7] = temp[6];
    temp[6] = temp[5];
    temp[5] = temp[4];
    temp[4] = temp[3];
    temp[3] = temp[2];
    temp[2] = temp[1];
    temp[1] = temp[0];
    temp[0] = __HAL_TIM_GetCounter(&htim1);
    a = (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7] + temp[8] + temp[9]) / 10.0f;
    // 计算轮的角速度
    motor->pid1->fdb = a * 100 / 4.0f / 30.0f / 13.0f;
    __HAL_TIM_SET_COUNTER(&htim1, 0);
}