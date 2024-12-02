#ifndef MOTOR_H
#define MOTOR_H


#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "math.h"
#include "pid.h"


enum MOTOR_MODE
{
    MOTOR_SPEED = 0,
    MOTOR_POSITION
};

typedef struct motorDate
{
	uint8_t motor_mode;//电机模式：速度环/位置环
	pids *pid1;//速度环
    pids *pid2;//位置环
    uint32_t V[4];//电机速度
    float cout[11];
}MG513;

#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOC
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOC

#define B1_Pin GPIO_PIN_1
#define B1_GPIO_Port GPIOE
#define B2_Pin GPIO_PIN_2
#define B2_GPIO_Port GPIOE

#define C1_Pin GPIO_PIN_6
#define C1_GPIO_Port GPIOD
#define C2_Pin GPIO_PIN_5
#define C2_GPIO_Port GPIOD

#define D1_Pin GPIO_PIN_5
#define D1_GPIO_Port GPIOE
#define D2_Pin GPIO_PIN_6
#define D2_GPIO_Port GPIOE

void MG513_Motor_pwm_init(void);
void MG513_encodervalue_get(float a[11],TIM_HandleTypeDef *_tim);
	
void MG513_Motor_stop(void);

void MG513_forword_A(void);
void MG513_back_A(void);
void MG513_forword_B(void);
void MG513_back_B(void);
void MG513_forword_C(void);
void MG513_back_C(void);
void MG513_forword_D(void);
void MG513_back_D(void);



#endif
