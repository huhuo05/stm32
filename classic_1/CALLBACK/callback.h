#ifndef CALLBACK_H
#define CALLBACK_H

#include "usart.h"
#include "gpio.h"
#include "bsp_can.h"
#include "bsp_tim.h"
#include "APP_classis.h"
#include "print_to_PC.h"
#include "remote_control.h"


#define SBUS_RX_BUF_NUM 36u

#define RC_FRAME_LENGTH 18u

#define get_motor_measure(ptr, data)                               \
  {                                                                \
    (ptr)->last_ecd = (ptr)->ecd;                                  \
    (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
    (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
    (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
    (ptr)->temperate = (data)[6];                                  \
  }

/*
typedef struct callback_date
{
    uint8_t Rxdata[8]; // ���̵��CAN�߽��յ�������
    classic_motor motor[4];
    float *V_goal[4];   //
����ң�ص����ݣ�V_goal[0]-x�����ϵķ��ٶȴ�С��V_goal[1]-y�����ϵķ��ٶȴ�С//
V_goal[2]-z�����ϵķ��ٶȴ�С// V_goal[3]-�ٶȴ�С float Location[4]; // 0-x;1-y;3-z;4-w RC_ctrl_t
*rc; } Callback;*/

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
