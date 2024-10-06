#include "print_to_PC.h"

extern CLASSIC group1;

// void print_to_PC_INIT(UART_HandleTypeDef *_huart, DMA_HandleTypeDef *_hdma) {
//   __HAL_UART_ENABLE_IT(_huart, UART_IT_RXNE);
//   __HAL_DMA_ENABLE(_hdma);
// }

void print_to_PC_Transmit(UART_HandleTypeDef *_huart, CLASSIC *_group) {
  int32_t temp[256] = {0xAB};
  for (uint8_t i = 1; i < 11; i++) {
    temp[i] = _group->V[0];
  }
  HAL_UART_Transmit_DMA(_huart, (uint8_t *)temp, sizeof(temp));
}

// 接收上位机的指令，修改Kp,Ki,Kd
void commond_to_change(UART_HandleTypeDef *_huart) {
  uint8_t Kpid[4] = {9};
  HAL_UART_Receive_IT(_huart, Kpid, 4);
  if (Kpid[0] == 0 || Kpid[0] == 1 || Kpid[0] == 2 || Kpid[0] == 3) {
    group1.PID[Kpid[0]].Kp = Kpid[1];
    group1.PID[Kpid[0]].Ki = Kpid[2];
    group1.PID[Kpid[0]].Kd = Kpid[3];
  }
}
