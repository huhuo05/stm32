#ifndef PID_H
#define PID_H

#include "main.h"
#include "stdio.h"
#include "struct_typedef.h"

enum PID_MODE
{
  PID_POSITION = 0,
  PID_DELTA
};
#pragma pack(1)
typedef struct pidData
{
  uint8_t mode;
  // PID参数
  fp32 Kp;
  fp32 Ki;
  fp32 Kd;

  fp32 max_out;  //
  fp32 max_iout; //

  fp32 set;
  fp32 fdb;

  fp32 out;
  fp32 Pout;
  fp32 Iout;
  fp32 Dout;
  fp32 Dbuf[3];
  fp32 error[3];

  // 速度环相关参数
  fp32 wheel_speed; // 轮子线速度
  // 位置环相关参数
  fp32 wheel_degree_speed; // 轮角速度
  int8_t wheel_degree;     // 转子机械角度总值
} pids;

#pragma pack()
extern void PID_init(pids *pid, uint8_t mode, const fp32 PID[3], fp32 max_out,
                     fp32 max_iout);
extern fp32 PID_calc(pids *pid, fp32 ref, fp32 set);
extern void PID_clear(pids *pid);
void pidINIT(pids *pid, uint8_t mode, fp32 KP, fp32 KI, fp32 KD, fp32 maxOut,
             fp32 maxIout);

extern pids motor1;
#endif
