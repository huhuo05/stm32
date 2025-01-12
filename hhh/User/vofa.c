#include "vofa.h"


int fputc(int ch,FILE *p)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,100);
	return ch;
}


