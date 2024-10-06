#include "bsp_can.h"

CAN_TxHeaderTypeDef CAN1_TxHander;
CAN_TxHeaderTypeDef CAN2_TxHander;

void Classis_can_init(CAN_HandleTypeDef *_canHandler, uint32_t _FIFO, uint32_t _FIFOMask) {
  CAN_FilterTypeDef sFilterConfigStructure;

  if (_canHandler == &hcan1) {
    // CAN发送结构体初始化
    CAN1_TxHander.StdId = 0x200;
    CAN1_TxHander.IDE = CAN_ID_STD;
    CAN1_TxHander.RTR = CAN_RTR_DATA;
    CAN1_TxHander.DLC = 0x08;
    if (_FIFO == CAN_RX_FIFO0) {
      // CAN过滤器初始化
      sFilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
      sFilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
      sFilterConfigStructure.FilterIdHigh = 0x200;  //
      sFilterConfigStructure.FilterIdLow = 0x110;   //
      sFilterConfigStructure.FilterMaskIdHigh = 0x0000;
      sFilterConfigStructure.FilterMaskIdLow = 0x0000;
      sFilterConfigStructure.FilterFIFOAssignment = _FIFO;
      sFilterConfigStructure.FilterActivation = ENABLE;
      sFilterConfigStructure.FilterBank = 0;
      sFilterConfigStructure.SlaveStartFilterBank = 14;

      HAL_CAN_ConfigFilter(_canHandler, &sFilterConfigStructure);
      HAL_CAN_Start(_canHandler);
      HAL_CAN_ActivateNotification(_canHandler, _FIFOMask);
    }
    if (_FIFO == CAN_RX_FIFO1) {
      // CAN过滤器初始化
      sFilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
      sFilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
      sFilterConfigStructure.FilterIdHigh = 0x200;  //
      sFilterConfigStructure.FilterIdLow = 0x110;   //
      sFilterConfigStructure.FilterMaskIdHigh = 0x0000;
      sFilterConfigStructure.FilterMaskIdLow = 0x0000;
      sFilterConfigStructure.FilterFIFOAssignment = _FIFO;
      sFilterConfigStructure.FilterActivation = ENABLE;
      sFilterConfigStructure.FilterBank = 0;
      sFilterConfigStructure.SlaveStartFilterBank = 14;

      HAL_CAN_ConfigFilter(_canHandler, &sFilterConfigStructure);
      HAL_CAN_Start(_canHandler);
      HAL_CAN_ActivateNotification(_canHandler, _FIFOMask);
    }
  }
  if (_canHandler == &hcan2) {
    // CAN发送结构体初始化
    CAN2_TxHander.StdId = 0x200;
    CAN2_TxHander.IDE = CAN_ID_STD;
    CAN2_TxHander.RTR = CAN_RTR_DATA;
    CAN2_TxHander.DLC = 0x08;
    if (_FIFO == CAN_RX_FIFO0) {
      // CAN过滤器初始化
      sFilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
      sFilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
      sFilterConfigStructure.FilterIdHigh = 0x200;  //
      sFilterConfigStructure.FilterIdLow = 0x110;   //
      sFilterConfigStructure.FilterMaskIdHigh = 0x0000;
      sFilterConfigStructure.FilterMaskIdLow = 0x0000;
      sFilterConfigStructure.FilterFIFOAssignment = _FIFO;
      sFilterConfigStructure.FilterActivation = ENABLE;
      sFilterConfigStructure.FilterBank = 14;
      sFilterConfigStructure.SlaveStartFilterBank = 27;

      HAL_CAN_ConfigFilter(_canHandler, &sFilterConfigStructure);
      HAL_CAN_Start(_canHandler);
      HAL_CAN_ActivateNotification(_canHandler, _FIFOMask);
    }
    if (_FIFO == CAN_RX_FIFO1) {
      // CAN过滤器初始化
      sFilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
      sFilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
      sFilterConfigStructure.FilterIdHigh = 0x200;  //
      sFilterConfigStructure.FilterIdLow = 0x110;   //
      sFilterConfigStructure.FilterMaskIdHigh = 0x0000;
      sFilterConfigStructure.FilterMaskIdLow = 0x0000;
      sFilterConfigStructure.FilterFIFOAssignment = _FIFO;
      sFilterConfigStructure.FilterActivation = ENABLE;
      sFilterConfigStructure.FilterBank = 14;
      sFilterConfigStructure.SlaveStartFilterBank = 27;

      HAL_CAN_ConfigFilter(_canHandler, &sFilterConfigStructure);
      HAL_CAN_Start(_canHandler);
      HAL_CAN_ActivateNotification(_canHandler, _FIFOMask);
    }
  }
}

/*void Classis_can_init(void) {
  CAN1_TxHander.StdId = 0x200;
  CAN1_TxHander.IDE = CAN_ID_STD;
  CAN1_TxHander.RTR = CAN_RTR_DATA;
  CAN1_TxHander.DLC = 0x08;

  CAN_FilterTypeDef sFilterConfigStructure;

  // CAN过滤器初始化
  sFilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfigStructure.FilterIdHigh = 0x0000;
  sFilterConfigStructure.FilterIdLow = 0x0000;
  sFilterConfigStructure.FilterMaskIdHigh = 0x0000;
  sFilterConfigStructure.FilterMaskIdLow = 0x0000;
  sFilterConfigStructure.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfigStructure.FilterActivation = ENABLE;
  sFilterConfigStructure.FilterBank = 0;
  sFilterConfigStructure.SlaveStartFilterBank = 14;

  HAL_CAN_ConfigFilter(&hcan1, &sFilterConfigStructure);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}*/

void Connect_can_init(void) {
}
