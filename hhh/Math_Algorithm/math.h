#ifndef MATH_H
#define MATH_H

#include "main.h"

#define R 0.1f // 车中心到轮子的距离 单位：m；
#define p 3.141592f
#define k_rpm p *R / 30.0f

#define D 0.06f           // 单位：m
#define Redu_Ratio 30.0f  // 减速比
#define Line_number 13.0f // 线数
#define T 0.0001f         // 采样周期

// #define get_motor_measure(ptr, data)                                   \
//     {                                                                  \
//         (ptr)->last_ecd = (ptr)->ecd;                                  \
//         (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
//         (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
//         (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
//         (ptr)->temperate = (data)[6];                                  \
//     }

// void DIJ3508_send_motor_measure(float out[4], uint8_t data[8]);
void Mean_filtering(float a[11]);

#endif
