#ifndef CALLBACK_H
#define CALLBACK_H

#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "pid.h"
#include "ps2.h"

typedef struct callbackDate
{
    fp32 cout[4][11];
	pids PID[4];
}Callback;

extern Callback callback;

#include "math1.h"
#include "APP_classic.h"

#endif
