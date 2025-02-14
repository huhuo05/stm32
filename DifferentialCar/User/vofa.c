#include "vofa.h"
/// @brief printf重定向
/// @param ch
/// @param p
/// @return
int fputc(int ch, FILE *p)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
	return ch;
}
