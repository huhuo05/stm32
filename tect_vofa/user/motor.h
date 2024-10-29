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
    pids *pid;
    uint32_t V[4];
    uint8_t motor_mode;
} Motor;

#endif
