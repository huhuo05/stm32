#include "motor.h"

void MG513_Motor_pwm_init(void)
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
    HAL_TIM_Base_Start_IT(&htim6); // 获取编码值
    HAL_TIM_Base_Start_IT(&htim7); // pid计算
}

void motor_pid_init(MG513 *motor, pids *PID, uint8_t motor_mode, uint8_t pid_mode, fp32 goal, fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout)
{
    if (motor->motor_mode != MOTOR_POSITION)
    {
        motor->motor_mode = motor_mode;
    } // 电机模式
    switch (motor->motor_mode)
    {
    case MOTOR_SPEED:
    {
        motor->pid1 = PID;
        motor->pid1->mode = pid_mode;
        motor->pid1->Kp = KP;
        motor->pid1->Ki = KI;
        motor->pid1->Kd = KD;
        motor->pid1->max_out = maxOut;
        motor->pid1->max_iout = maxIout;
        pidINIT(motor->pid1, PID_POSITION, motor->pid1->Kp, motor->pid1->Ki, motor->pid1->Kd, motor->pid1->max_out, motor->pid1->max_iout);
    }
    break;
    case MOTOR_POSITION:
    {
        motor->pid2 = PID;
        motor->pid2->mode = pid_mode;
        motor->pid2->Kp = KP;
        motor->pid2->Ki = KI;
        motor->pid2->Kd = KD;
        motor->pid2->max_out = maxOut;
        motor->pid2->max_iout = maxIout;
        pidINIT(motor->pid2, PID_POSITION, motor->pid2->Kp, motor->pid2->Ki, motor->pid2->Kd, motor->pid2->max_out, motor->pid2->max_iout);
    }
    break;
    default:
        break;
    }
}

void MG513_encodervalue_get(float a[11], TIM_HandleTypeDef *_tim)
{
    Mean_filtering(a);
    a[0] = (float)__HAL_TIM_GET_COUNTER(_tim);
    __HAL_TIM_SET_COUNTER(_tim, 0);
}

void MG513_Motor_stop(void)
{
    // A
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
}

void MG513_forword_A(void)
{
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET);
}

void MG513_forword_B(void)
{
    HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_RESET);
}

void MG513_forword_C(void)
{
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
}

void MG513_forword_D(void)
{
    HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
}

void MG513_back_A(void)
{
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_SET);
}

void MG513_back_B(void)
{
    HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_SET);
}

void MG513_back_C(void)
{
    HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_SET);
}

void MG513_back_D(void)
{
    HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
}
