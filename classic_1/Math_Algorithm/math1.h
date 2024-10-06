#ifndef MATH1_H
#define MATH1_H

#include "math.h"
#include "callback.h"
#include "pid.h"

#define R 0.1 // m
#define p 3.141592
#define k_rpm p *R / 30.0

#define get_motor_measure(ptr, data)                                   \
    {                                                                  \
        (ptr)->last_ecd = (ptr)->ecd;                                  \
        (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
        (ptr)->temperate = (data)[6];                                  \
    }

#endif
