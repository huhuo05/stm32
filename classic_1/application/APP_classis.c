#include "APP_classis.h"

extern CAN_TxHeaderTypeDef CAN1_TxHander;
extern CAN_TxHeaderTypeDef CAN2_TxHander;

void Classic_Init(CLASSIC *_group, CAN_HandleTypeDef *_canHandler, uint32_t _FIFO,
                  uint32_t _MSG_PENDING) {
  // Classis_can_init();
  _group->_canHandler = _canHandler;
  _group->FIFO = _FIFO;
  Classis_can_init(_group->_canHandler, _FIFO, CAN_IT_RX_FIFO0_MSG_PENDING);
  for (uint8_t i = 0; i < 4; i++) {
    // pidINIT(&group1.PID[i], PID_POSITION, M3508_Speed_PID_KP, M3508_Speed_PID_KI,
    //         M3508_Speed_PID_KD, M3508_Speed_PID_MAX_OUT, M3508_Speed_PID_MAX_IOUT);
    pidINIT(&_group->PID[i], PID_POSITION, M3508_Speed_PID_KP, M3508_Speed_PID_KI,
            M3508_Speed_PID_KD, M3508_Speed_PID_MAX_OUT, M3508_Speed_PID_MAX_IOUT);
  }
  _group->V_goal[0] = 0;
  _group->V_goal[1] = 0;
  _group->V_goal[2] = 2000;
}

// void Action_solution(uint8_t mode)  // 底盘解算
// {
//   switch (mode) {
//     case 0:  //+
//     {
//       group1.V[0] = (group1.motor[0].speed_rpm + group1.motor[1].speed_rpm
//                      + group1.motor[2].speed_rpm + group1.motor[3].speed_rpm)
//                     / 1.4147;
//       group1.V[1] = (group1.motor[0].speed_rpm + group1.motor[1].speed_rpm
//                      + group1.motor[2].speed_rpm + group1.motor[3].speed_rpm)
//                     / 1.4147;
//       group1.V[2] = group1.motor[0].speed_rpm + group1.motor[1].speed_rpm
//                     + group1.motor[2].speed_rpm + group1.motor[3].speed_rpm;
//       group1.V[3] = sqrt(group1.V[0] * group1.V[0] + group1.V[1] * group1.V[1]);
//     } break;
//     case 1:  // -
//     {
//       group1.PID[0].set = -(group1.V_goal[0] - group1.V_goal[1]) / sqrt(2.0) + group1.V_goal[2];
//       group1.PID[1].set = (group1.V_goal[0] + group1.V_goal[1]) / sqrt(2.0) + group1.V_goal[2];
//       group1.PID[2].set = (group1.V_goal[0] - group1.V_goal[1]) / sqrt(2.0) + group1.V_goal[2];
//       group1.PID[3].set = -(group1.V_goal[0] + group1.V_goal[1]) / sqrt(2.0) + group1.V_goal[2];
//       for (uint8_t i = 0; i < 4; i++) {
//         PID_calc(&group1.PID[i], group1.motor[i].speed_rpm, group1.PID[i].set);
//       }
//       send_motor_measure(&group1, group1.Txdata);
//       HAL_CAN_AddTxMessage(&hcan1, &CAN1_TxHander, group1.Txdata, 0);
//     } break;
//     default:
//       break;
//   }
// }

void send_motor_measure(CLASSIC *a, uint8_t data[8]);

void Action_solution(CLASSIC *_group, uint8_t mode, fp32 x, fp32 y, fp32 z)  // 底盘解算
{
  _group->mode = mode;
  if (_group->mode == 1) {
    _group->V_goal[0] = x;
    _group->V_goal[1] = y;
    _group->V_goal[2] = z;
  }
  switch (_group->mode) {
    case 0:  // 正解
    {
      _group->V[0] = (_group->motor[0].speed_rpm + _group->motor[1].speed_rpm
                      + _group->motor[2].speed_rpm + _group->motor[3].speed_rpm)
                     / 1.4147;
      _group->V[1] = (_group->motor[0].speed_rpm + _group->motor[1].speed_rpm
                      + _group->motor[2].speed_rpm + _group->motor[3].speed_rpm)
                     / 1.4147;
      _group->V[2] = _group->motor[0].speed_rpm + _group->motor[1].speed_rpm
                     + _group->motor[2].speed_rpm + _group->motor[3].speed_rpm;
      _group->V[3] = sqrt(_group->V[0] * _group->V[0] + _group->V[1] * _group->V[1]);
    } break;
    case 1:  // 逆解
    {
      _group->PID[0].set = (-_group->V_goal[0] - _group->V_goal[1]) / sqrt(2.0) + _group->V_goal[2];
      _group->PID[1].set = (-_group->V_goal[0] + _group->V_goal[1]) / sqrt(2.0) + _group->V_goal[2];
      _group->PID[2].set = (_group->V_goal[0] + _group->V_goal[1]) / sqrt(2.0) + _group->V_goal[2];
      _group->PID[3].set = (_group->V_goal[0] - _group->V_goal[1]) / sqrt(2.0) + _group->V_goal[2];
      for (uint8_t i = 0; i < 4; i++) {
        PID_calc(&_group->PID[i], _group->motor[i].speed_rpm, _group->PID[i].set);
      }
      send_motor_measure(_group, _group->Txdata);
      HAL_CAN_AddTxMessage(&hcan1, &CAN1_TxHander, _group->Txdata, 0);
    } break;
    default:
      break;
  }
}

void send_motor_measure(CLASSIC *a, uint8_t data[8]) {
  int16_t out_temp[4] = {0};
  for (uint8_t i = 0; i < 4; i++) {
    out_temp[i] = (int16_t)(a->PID[i].out);
  }
  data[0] = (uint8_t)(out_temp[0] >> 8);
  data[1] = (uint8_t)(out_temp[0]);
  data[2] = (uint8_t)(out_temp[1] >> 8);
  data[3] = (uint8_t)(out_temp[1]);
  data[4] = (uint8_t)(out_temp[2] >> 8);
  data[5] = (uint8_t)(out_temp[2]);
  data[6] = (uint8_t)(out_temp[3] >> 8);
  data[7] = (uint8_t)(out_temp[3]);
}

/// @brief 330.0为比例参数，可根据实际速度自行调整
/// @param callback
/// @param group
/*void valve_change(Callback *callback, CLASSIC *group) {
  group->V_goal[0] = callback->rc->rc.ch[0] / 330.0;  // 底盘y轴
  group->V_goal[1] = callback->rc->rc.ch[1] / 330.0;  // 底盘x轴
  group->V_goal[2] = callback->rc->rc.ch[2] / 330.0;  // 云台yaw轴
  group->V_goal[3] = callback->rc->rc.ch[3] / 330.0;  // 云台pitch轴
  for (int i = 0; i < 4; i++) {
    group->a[i] = &callback->motor[i];
  }
}
*/
