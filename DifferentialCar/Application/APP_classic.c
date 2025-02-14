#include "APP_classic.h"

void MG513_Init(MG513 *motor, uint8_t motor_mode, fp32 goal,
                fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout)
{
        motor_pid_init(motor, motor_mode, goal, KP, KI, KD, maxOut, maxIout);
}

void Classic_init(Car *car, MG513 *MOTORA, MG513 *MOTORB, MG513 *MOTORC, MG513 *MOTORD)
{
        car->motorgroup[0] = MOTORA;
        car->motorgroup[1] = MOTORB;
        car->motorgroup[2] = MOTORC;
        car->motorgroup[3] = MOTORD;
        car->init = 1;
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
