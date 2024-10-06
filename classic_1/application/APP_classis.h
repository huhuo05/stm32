#ifndef APP_CLASSIC_H
#define APP_CLASSIC_H

#include "bsp_can.h"
#include "bsp_tim.h"
#include "math.h"
#include "pid.h"

typedef struct motor_data {

  uint16_t last_ecd;
  int16_t ecd;
  int16_t speed_rpm;
  int16_t given_current;
  uint16_t temperate;
} classic_motor;

typedef struct APP_classicDate {
  CAN_HandleTypeDef *_canHandler;  // CAN���
  uint32_t FIFO;                   // FIFOͨ��
  uint8_t mode;                    // ����ģʽ
  uint8_t Rxdata[8];               // ���̵��CAN�߽��յ�����
  uint8_t Txdata[8];               // ���̵��CAN�߷��͵�����
  pids PID[4];                     //  ���̵��PID
  classic_motor motor[4];          //  ���̵������
  float V[4];  // V[0]-x�����ϵķ��ٶȴ�С��V[1]-y�����ϵķ��ٶȴ�С// V[2]-z�����ϵķ��ٶȴ�С//
               // V[3]-�ٶȴ�С
  float
    V_goal[4];  // ����ң�ص����ݣ�V_goal[0]-x�����ϵķ��ٶȴ�С��V_goal[1]-y�����ϵķ��ٶȴ�С//
                // V_goal[2]-z�����ϵķ��ٶȴ�С// V_goal[3]-�ٶȴ�С
  float Location[4];  // 0-x;1-y;3-z;4-w
} CLASSIC;

void Classic_Init(CLASSIC *_group, CAN_HandleTypeDef *_canHandler, uint32_t _FIFO,
                  uint32_t _MSG_PENDING);
void Action_solution(CLASSIC *_group, uint8_t mode, fp32 x, fp32 y, fp32 z);
// void Classic_Init(void);
// void Action_solution(uint8_t mode);
// void valve_change(Callback *callback, CLASSIC *group);

#endif
