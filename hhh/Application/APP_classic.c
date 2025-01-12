#include "APP_classic.h"

void MG513_Init(MG513 *motor, pids *PID, uint8_t motor_mode, fp32 goal,
                fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout)
{
        motor_pid_init(motor, PID, motor_mode, goal, KP, KI, KD, maxOut, maxIout);
}

void Classic_init(Car *car, MG513 *MOTORA, MG513 *MOTORB, MG513 *MOTORC, MG513 *MOTORD)
{
        car->motorgroup[0] = MOTORA;
        car->motorgroup[1] = MOTORB;
        car->motorgroup[2] = MOTORC;
        car->motorgroup[3] = MOTORD;
        car->init = 1;
}

void MG513_pwm_send(pids *MOTOR_PID[4])
{
        // 判断运动方向并发送数据
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
        if (MOTOR_PID[2]->out > 0 || MOTOR_PID[2]->out == 0)
        {
                HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_RESET);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, MOTOR_PID[2]->out);
        }
        else
        {
                HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, GPIO_PIN_SET);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, -MOTOR_PID[2]->out);
        }
        if (MOTOR_PID[3]->out > 0 || MOTOR_PID[3]->out == 0)
        {
                HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, MOTOR_PID[3]->out);
        }
        else
        {
                HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, -MOTOR_PID[3]->out);
        }
}

/// @brief
/// @param v
/// @param v_goal
void Action_Positive_solution(float v[4], float v_goal[3])
{
        v[0] = (v_goal[0] - v_goal[1]) / 1.4142f + v_goal[2];
        v[1] = (v_goal[0] + v_goal[1]) / 1.4142f + v_goal[2];
        v[2] = (-v_goal[0] + v_goal[1]) / 1.4142f + v_goal[2];
        v[3] = (-v_goal[0] - v_goal[1]) / 1.4142f + v_goal[2];
}

void Action_Negative_solution(float v[4], float v_recent[3])
{
        v_recent[0] = (v[0] - v[1] + v[2] - v[3]) / 1.4142f;
        v_recent[1] = (v[0] - v[1] + v[2] - v[3]) / 1.4142f;
        v_recent[2] = v[0] + v[1] + v[2] + v[3];
}

void classic_control(Car *car, float x, float y, float z)
{
        float v_temp[3] = {x, y, z};
        float v[4] = {0, 0, 0, 0};
        Action_Positive_solution(v, v_temp);
        for (uint8_t i = 0; i < 4; i++)
        {
                car->motorgroup[i]->pid1.set = v[i];
        }
        //        MG513_pwm_send(pid);
}
