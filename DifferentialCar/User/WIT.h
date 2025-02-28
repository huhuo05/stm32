#include "main.h"
#include "usart.h"

#ifndef __WIT_h__
#define __WIT_h__

typedef struct WITDATA
{
    uint8_t Flag;      // 标志位  0x00:无数据，0x01:有数据
    uint8_t email[44]; // 邮箱
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
void WIT_GET_value(WIT *wit);
void WIT_Init(UART_HandleTypeDef *huartx);                     // 初始化(自动校准)
void WIT_Acceleration_calibration(UART_HandleTypeDef *huartx); // 加速度校准
void WIT_Angle_calibration(UART_HandleTypeDef *huartx);        // 角度校准
void WIT_Z_calibration(UART_HandleTypeDef *huartx);            // Z轴校准

#endif
