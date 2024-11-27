#include "vofa.h"
#include "stdio.h"

int fputc(int ch,FILE *p)
{
	HAL_UART_Transmit_DMA(&huart1,(uint8_t *)&ch,1);
	return ch;
}
