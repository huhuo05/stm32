#include "callback.h"

Callback callback;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim7) // 100HZ
    {
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
