#ifndef APP_classic_h
#define APP_classic_h

#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "pid.h"
#include "math1.h"

typedef struct APP_classicDate
{
    fp32 V[4]; // V[0]-x�����ϵķ��ٶȴ�С��V[1]-y�����ϵķ��ٶȴ�С// V[2]-z�����ϵķ��ٶȴ�С// V[3]-�ٶȴ�С
} APP_classic;

#define D 0.06           // m
#define Redu_Ratio 30.0f  // 
#define Line_number 13.0f // 

extern void classic_init(void);

#endif
