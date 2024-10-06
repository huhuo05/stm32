#ifndef PIDDATA_H
#define PIDDATA_H

#include "struct_typedef.h"

// 3508速度环
#define M3508_Speed_PID_KP       1.0f
#define M3508_Speed_PID_KI       0.05f
#define M3508_Speed_PID_KD       0.1f
#define M3508_Speed_PID_MAX_OUT  16384.0f
#define M3508_Speed_PID_MAX_IOUT 1000.0f

// 底盘跟随速度环
#define Chassis_Speed_PID_KP       2.0f
#define Chassis_Speed_PID_KI       0.0f
#define Chassis_Speed_PID_KD       0.00f
#define Chassis_Speed_PID_MAX_OUT  5000.0f
#define Chassis_Speed_PID_MAX_IOUT 1000.0f

// 底盘跟随角度环
#define Chassis_Angle_PID_KP       2.5f
#define Chassis_Angle_PID_KI       0.00f
#define Chassis_Angle_PID_KD       0.0f
#define Chassis_Angle_PID_MAX_OUT  5000.0f
#define Chassis_Angle_PID_MAX_IOUT 1000.0f
#endif
