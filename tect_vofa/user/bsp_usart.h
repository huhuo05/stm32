#ifndef BSP_USART_H
#define BSP_USART_H

#include "usart.h"
#include "dma.h"


void print_to_PC_INIT(UART_HandleTypeDef *_huart, DMA_HandleTypeDef *_hdma);
void RC_init(UART_HandleTypeDef *_huart,uint8_t *rx1_buf,uint8_t *rx2_buf,uint16_t dma_buf_num);

#endif
