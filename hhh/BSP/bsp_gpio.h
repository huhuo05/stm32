#ifndef BSP_GPIO_H
#define BSP_GPIO_H


#include "main.h"
#include "gpio.h"

//#define B2_Pin GPIO_PIN_2
//#define B2_GPIO_Port GPIOE
//#define C1_Pin GPIO_PIN_3
//#define C1_GPIO_Port GPIOE
//#define C2_Pin GPIO_PIN_4
//#define C2_GPIO_Port GPIOE
//#define D1_Pin GPIO_PIN_5
//#define D1_GPIO_Port GPIOE
//#define D2_Pin GPIO_PIN_6
//#define D2_GPIO_Port GPIOE
//#define A1_Pin GPIO_PIN_0
//#define A1_GPIO_Port GPIOC
//#define A2_Pin GPIO_PIN_0
//#define A2_GPIO_Port GPIOE
//#define B1_Pin GPIO_PIN_1
//#define B1_GPIO_Port GPIOE

void MG513_Motor_gpio_init(void);
void MOVE_dir(void);
void MOVE_back(void);
void Mini_top(void);
void MOVE_left(void);
void MOVE_right(void);


#endif
