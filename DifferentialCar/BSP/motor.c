#include "motor.h"

void MG513_Motor_pwm_init(void)
{
    // 启动PWM
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // A
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // B
    // 启动编码器
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // A
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // B
    // 编码器初始化
    __HAL_TIM_SET_COUNTER(&htim2, 30000);
    __HAL_TIM_SET_COUNTER(&htim3, 30000);
}

void motor_pid_init(MG513 *motor, uint8_t motor_mode, fp32 goal,
                    fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout) // 设置PID相关参数
{
    if (motor->motor_mode != MOTOR_POSITION)
    {
        motor->motor_mode = motor_mode;
    }
    // PID模式切换
    switch (motor->motor_mode)
    {
    case MOTOR_SPEED:
    {
        motor->motor_mode_sign[0] = 1;
        //        motor->pid1 = PID;
        motor->pid1.mode = motor_mode;
        motor->pid1.Kp = KP;
        motor->pid1.Ki = KI;
        motor->pid1.Kd = KD;
        motor->pid1.max_out = maxOut;
        motor->pid1.max_iout = maxIout;
        pidINIT(&motor->pid1, PID_POSITION, motor->pid1.Kp, motor->pid1.Ki,
                motor->pid1.Kd, motor->pid1.max_out, motor->pid1.max_iout);
        motor->pid1.set = goal;
    }
    break;
    case MOTOR_POSITION:
    {
        motor->motor_mode_sign[1] = 1;
        //        motor->pid2 = PID;
        motor->pid2.mode = motor_mode;
        motor->pid2.Kp = KP;
        motor->pid2.Ki = KI;
        motor->pid2.Kd = KD;
        motor->pid2.max_out = maxOut;
        motor->pid2.max_iout = maxIout;
        pidINIT(&motor->pid2, PID_POSITION, motor->pid2.Kp, motor->pid2.Ki,
                motor->pid2.Kd, motor->pid2.max_out, motor->pid2.max_iout);
        motor->pid2.set = goal;
    }
    break;
    default:
        break;
    }
}

/// @brief
/// @param a
/// @param _tim
void MG513_encodervalue_get(float a[11], TIM_HandleTypeDef *_tim)
{
    a[0] = (float)__HAL_TIM_GET_COUNTER(_tim) - 30000;
    if (a[0] < 10000.0f && a[0] > -10000.0f)
    {
        __HAL_TIM_SET_COUNTER(_tim, 30000);
        Mean_filtering(a);
    }
    else
        a[0] = 0;
}

/// @brief
/// @param MOTOR_PID
/// @param cout
void MG513_Calculate(pids *MOTOR_PID, float cout[11])
{
    MOTOR_PID->wheel_speed = (fp32)cout[10] * p * D / 4.0f / Redu_Ratio / Line_number / Ti;
    MOTOR_PID->out = PID_calc(MOTOR_PID, MOTOR_PID->wheel_speed, MOTOR_PID->set);
}

/// @brief
/// @param
void MG513_Motor_stop(void)
{
    // A
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_RESET);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
}

/// @brief
/// @param MOTOR_PID
void MG513_pwm_send(pids *MOTOR_PID[4])
{
    if (MOTOR_PID[0]->out > 0 || MOTOR_PID[0]->out == 0)
    {
        HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MOTOR_PID[0]->out);
    }
    else
    {
        HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -MOTOR_PID[0]->out);
    }
    if (MOTOR_PID[1]->out > 0 || MOTOR_PID[1]->out == 0)
    {
        HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MOTOR_PID[1]->out);
    }
    else
    {
        HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, -MOTOR_PID[1]->out);
    }
}

void MG513_SET(pids *MOTOR_PID, float goal)
{
    MOTOR_PID->set = goal;
}
