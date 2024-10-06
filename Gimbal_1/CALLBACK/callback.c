#include "callback.h"

extern CLASSIC group1;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  CAN_RxHeaderTypeDef CAN_RxHeader;

  HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &CAN_RxHeader, group1.Rxdata);
  switch (CAN_RxHeader.StdId) {
    case 0x201:
      get_motor_measure(&group1.motor[0], group1.Rxdata);
      break;
    case 0x202:
      get_motor_measure(&group1.motor[1], group1.Rxdata);
      break;
    case 0x203:
      get_motor_measure(&group1.motor[2], group1.Rxdata);
      break;
    case 0x204:
      get_motor_measure(&group1.motor[3], group1.Rxdata);
      break;
    default:
      break;
  }
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart1)
		{
			print_to_PC_Transmit(&huart1,&group1);
		}
//  if (huart3.Instance->SR & UART_FLAG_RXNE)  // 接收到数据
//  {
//    __HAL_UART_CLEAR_PEFLAG(&huart3);
//  }
//  else if (USART3->SR & UART_FLAG_IDLE) {
//    static uint16_t this_time_rx_len = 0;

//    __HAL_UART_CLEAR_PEFLAG(&huart3);

//    if ((hdma_usart3_rx.Instance->CR & DMA_SxCR_CT) == RESET) {
//      /* Current memory buffer used is Memory 0 */

//      // disable DMA
//      // 失效DMA
//      __HAL_DMA_DISABLE(&hdma_usart3_rx);

//      // get receive data length, length = set_data_length - remain_length
//      // 获取接收数据长度,长度 = 设定长度 - 剩余长度
//      this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;

//      // reset set_data_lenght
//      // 重新设定数据长度
//      hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;

//      // set memory buffer 1
//      // 设定缓冲区1
//      hdma_usart3_rx.Instance->CR |= DMA_SxCR_CT;

//      // enable DMA
//      // 使能DMA
//      __HAL_DMA_ENABLE(&hdma_usart3_rx);

//      if (this_time_rx_len == RC_FRAME_LENGTH) {
//        sbus_to_rc(sbus_rx_buf[0], &rc_ctrl);
//      }
//    }
//    else {
//      /* Current memory buffer used is Memory 1 */
//      // disable DMA
//      // 失效DMA
//      __HAL_DMA_DISABLE(&hdma_usart3_rx);

//      // get receive data length, length = set_data_length - remain_length
//      // 获取接收数据长度,长度 = 设定长度 - 剩余长度
//      this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;

//      // reset set_data_lenght
//      // 重新设定数据长度
//      hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;

//      // set memory buffer 0
//      // 设定缓冲区0
//      DMA1_Stream1->CR &= ~(DMA_SxCR_CT);

//      // enable DMA
//      // 使能DMA
//      __HAL_DMA_ENABLE(&hdma_usart3_rx);

//      if (this_time_rx_len == RC_FRAME_LENGTH) {
//        // 处理遥控器数据
//        sbus_to_rc(sbus_rx_buf[1], &rc_ctrl);
//      }
//    }
//  }
}
