#ifndef MATH_H
#define MATH_H

#include "main.h"

#define R 0.1f // �����ĵ����ӵľ��� ��λ��m��
#define p 3.141592f
#define k_rpm p *R / 30.0f

#define D 0.06f           // ��λ��m
#define Redu_Ratio 30.0f  // ���ٱ�
#define Line_number 13.0f // ����
#define T 0.0001f         // ��������

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
