#include "APP_classic.h"

void classis_calculate(pids *MOTOR_PID[4], float *cout[4])
{

        MOTOR_PID[0]->wheel_speed = (fp32)cout[0][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        MOTOR_PID[1]->wheel_speed = (fp32)cout[1][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        MOTOR_PID[2]->wheel_speed = (fp32)cout[2][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        MOTOR_PID[3]->wheel_speed = (fp32)cout[3][10] * p * D / 4.0f / Redu_Ratio / Line_number;

        //?
        PID_calc(MOTOR_PID[0], MOTOR_PID[0]->wheel_speed, MOTOR_PID[0]->set);
        PID_calc(MOTOR_PID[1], MOTOR_PID[1]->wheel_speed, MOTOR_PID[1]->set);
        PID_calc(MOTOR_PID[2], MOTOR_PID[2]->wheel_speed, MOTOR_PID[2]->set);
        PID_calc(MOTOR_PID[3], MOTOR_PID[3]->wheel_speed, MOTOR_PID[3]->set);
}

void MG513_pwm_set(pids *MOTOR_PID[4])
{
        // 判断运动方向并发送数据
        if (MOTOR_PID[0]->out > 0 && MOTOR_PID[0]->out == 0)
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MOTOR_PID[0]->out);

        else
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -MOTOR_PID[0]->out);
        if (MOTOR_PID[1]->out > 0 && MOTOR_PID[1]->out == 0)
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MOTOR_PID[1]->out);
        else
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, -MOTOR_PID[1]->out);
        if (MOTOR_PID[2]->out > 0 && MOTOR_PID[2]->out == 0)
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, MOTOR_PID[2]->out);
        else
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, -MOTOR_PID[2]->out);
        if (MOTOR_PID[3]->out > 0 && MOTOR_PID[3]->out == 0)
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, MOTOR_PID[3]->out);
        else
                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, -MOTOR_PID[3]->out);
}

void Action_solution(uint8_t model, float v[4], float v_goal[3], Car *car)
{
        switch (model)
        {
        case 0:
                v[0] = (v_goal[0] - v_goal[1]) / 1.4142 + v_goal[2];
                v[1] = (-v_goal[0] - v_goal[1]) / 1.4142 + v_goal[2];
                v[2] = (-v_goal[0] + v_goal[1]) / 1.4142 + v_goal[2];
                v[3] = (v_goal[0] + v_goal[1]) / 1.4142 + v_goal[2];
                break;
        case 1:
                car->V[0] = (v[0] - v[1] + v[2] - v[3]) / 1.4142;
                car->V[1] = (v[0] - v[1] + v[2] - v[3]) / 1.4142;
                car->V[2] = v[0] + v[1] + v[2] + v[3];

                break;
        }
}
