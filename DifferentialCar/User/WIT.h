#include "main.h"

#ifndef __WIT_h__
#define __WIT_h__

typedef struct WITDATA
{
    // 标志位
    uint8_t Flag; // 0x00:无数据，0x01:有数据
    // 原始数据
    uint8_t Time;                // 时间
    uint8_t Acceleration[8];     // 加速度
    uint8_t Angular_velocity[8]; // 角速度
    uint8_t Angle[8];            // 角度
    uint8_t Quaternion[8];       // 四元数
    // 处理后数据
    int16_t Temperature;    // 温度
    int16_t Final_data[14]; // 最终数据
} WIT;

void WIT_resolving(WIT *wit);

#endif
