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

void Mean_filtering(float a[11]);

#endif
