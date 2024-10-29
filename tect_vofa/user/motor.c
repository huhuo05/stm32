#include "motor.h"

void motor_init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
}

void motor_pid_init(Motor *motor, pids *pid, uint8_t motor_mode, uint8_t pid_mode, fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout)
{
    motor->motor_mode = motor_mode; // 电机模式
    switch (motor->motor_mode)
    {
    case MOTOR_SPEED:
    {
        motor->pid = pid;
        motor->pid->mode = pid_mode;
        motor->pid->Kp = KP;
        motor->pid->Ki = KI;
        motor->pid->Kd = KD;
        motor->pid->max_out = maxOut;
        motor->pid->max_iout = maxIout;
    }
    break;
    case MOTOR_POSITION:
    {
        motor->pid = pid;
        motor->pid->mode = pid_mode;
        motor->pid->Kp = KP;
        motor->pid->Ki = KI;
        motor->pid->Kd = KD;
        motor->pid->max_out = maxOut;
        motor->pid->max_iout = maxIout;
    }
    break;
    default:
        break;
    }
}
