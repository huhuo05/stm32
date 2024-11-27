#include "callback.h"

Callback callback;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6) // 1000HZ
    {
        // 获得计数值
        callback.cout[0][9] = callback.cout[0][8];
        callback.cout[0][8] = callback.cout[0][7];
        callback.cout[0][7] = callback.cout[0][6];
        callback.cout[0][6] = callback.cout[0][5];
        callback.cout[0][5] = callback.cout[0][4];
        callback.cout[0][4] = callback.cout[0][3];
        callback.cout[0][3] = callback.cout[0][2];
        callback.cout[0][2] = callback.cout[0][1];
        callback.cout[0][1] = callback.cout[0][0];
        callback.cout[0][0] = (int8_t)__HAL_TIM_GET_COUNTER(&htim2);
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        callback.cout[1][9] = callback.cout[1][8];
        callback.cout[1][8] = callback.cout[1][7];
        callback.cout[1][7] = callback.cout[1][6];
        callback.cout[1][6] = callback.cout[1][5];
        callback.cout[1][5] = callback.cout[1][4];
        callback.cout[1][4] = callback.cout[1][3];
        callback.cout[1][3] = callback.cout[1][2];
        callback.cout[1][2] = callback.cout[1][1];
        callback.cout[1][1] = callback.cout[1][0];
        callback.cout[1][0] = (int8_t)__HAL_TIM_GET_COUNTER(&htim3);
        __HAL_TIM_SET_COUNTER(&htim3, 0);
        callback.cout[2][9] = callback.cout[2][8];
        callback.cout[2][8] = callback.cout[2][7];
        callback.cout[2][7] = callback.cout[2][6];
        callback.cout[2][6] = callback.cout[2][5];
        callback.cout[2][5] = callback.cout[2][4];
        callback.cout[2][4] = callback.cout[2][3];
        callback.cout[2][3] = callback.cout[2][2];
        callback.cout[2][2] = callback.cout[2][1];
        callback.cout[2][1] = callback.cout[2][0];
        callback.cout[2][0] = (int8_t)__HAL_TIM_GET_COUNTER(&htim4);
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        callback.cout[3][9] = callback.cout[3][8];
        callback.cout[3][8] = callback.cout[3][7];
        callback.cout[3][7] = callback.cout[3][6];
        callback.cout[3][6] = callback.cout[3][5];
        callback.cout[3][5] = callback.cout[3][4];
        callback.cout[3][4] = callback.cout[3][3];
        callback.cout[3][3] = callback.cout[3][2];
        callback.cout[3][2] = callback.cout[3][1];
        callback.cout[3][1] = callback.cout[3][0];
        callback.cout[3][0] = (int8_t)__HAL_TIM_GET_COUNTER(&htim5);
        __HAL_TIM_SET_COUNTER(&htim5, 0);
    }
    if (htim == &htim7) // 100HZ
    {
        // 滤波
//        callback.cout[0][10] = (callback.cout[0][0] + callback.cout[0][1] + callback.cout[0][2] + callback.cout[0][3] + callback.cout[0][4] + callback.cout[0][5] + callback.cout[0][6] + callback.cout[0][7] + callback.cout[0][8] + callback.cout[0][9]) / 10;
//        callback.cout[1][10] = (callback.cout[1][0] + callback.cout[1][1] + callback.cout[1][2] + callback.cout[1][3] + callback.cout[1][4] + callback.cout[1][5] + callback.cout[1][6] + callback.cout[1][7] + callback.cout[1][8] + callback.cout[1][9]) / 10;
//        callback.cout[2][10] = (callback.cout[2][0] + callback.cout[2][1] + callback.cout[2][2] + callback.cout[2][3] + callback.cout[2][4] + callback.cout[2][5] + callback.cout[2][6] + callback.cout[2][7] + callback.cout[2][8] + callback.cout[2][9]) / 10;
//        callback.cout[3][10] = (callback.cout[3][0] + callback.cout[3][1] + callback.cout[3][2] + callback.cout[3][3] + callback.cout[3][4] + callback.cout[3][5] + callback.cout[3][6] + callback.cout[3][7] + callback.cout[3][8] + callback.cout[3][9]) / 10;
       // 计算速度
        callback.PID[0].wheel_speed = (fp32)callback.cout[0][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        callback.PID[1].wheel_speed = (fp32)callback.cout[1][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        callback.PID[2].wheel_speed = (fp32)callback.cout[2][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        callback.PID[3].wheel_speed = (fp32)callback.cout[3][10] * p * D / 4.0f / Redu_Ratio / Line_number;
        PID_calc(&callback.PID[0], callback.PID[0].wheel_speed, callback.PID[0].set);
        PID_calc(&callback.PID[1], callback.PID[1].wheel_speed, callback.PID[1].set);
        PID_calc(&callback.PID[2], callback.PID[2].wheel_speed, callback.PID[2].set);
        PID_calc(&callback.PID[3], callback.PID[3].wheel_speed, callback.PID[3].set);
        // 判断运动方向并发送数据
        if (callback.PID[0].out > 0 && callback.PID[0].out == 0)
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, callback.PID[0].out);
        else
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -callback.PID[0].out);
        if (callback.PID[1].out > 0 && callback.PID[1].out == 0)
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, callback.PID[1].out);
        else
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, -callback.PID[1].out);
        if (callback.PID[2].out > 0 && callback.PID[2].out == 0)
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, callback.PID[2].out);
        else
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, -callback.PID[2].out);
        if (callback.PID[3].out > 0 && callback.PID[3].out == 0)
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, callback.PID[3].out);
        else
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, -callback.PID[3].out);
    }
    if (htim == &htim11)
    {
        PS2_Receive();
    }
}
