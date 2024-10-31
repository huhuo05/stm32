#ifndef __motor_h
#define __motor_h

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "pid.h"

enum MOTOR_MODE
{
    MOTOR_SPEED = 0,
    MOTOR_POSITION
};

typedef struct motordata
{
    pids *pid1;
    pids *pid2;
    uint32_t V[4];
    uint8_t motor_mode;
} Motor;

void motor_init(void);
void motor_pid_init(Motor *motor, pids *pid, uint8_t motor_mode, uint8_t pid_mode, fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout);

#endif
