#include "motor.h"

#ifndef __APP_classic_h
#define __APP_classic_h

typedef struct APP_CarDate
{
    uint8_t init;
    MG513 *motorgroup[4];
} Car;

void MG513_Init(MG513 *motor, uint8_t motor_mode, fp32 goal,
                fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout);
void Classic_init(Car *car, MG513 *MOTORA, MG513 *MOTORB, MG513 *MOTORC, MG513 *MOTORD);
void classic_control(Car *car, float x, float y, float z);

#endif
