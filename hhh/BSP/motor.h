#include "tim.h"
#include "gpio.h"
#include "math.h"
#include "pid.h"

#ifndef MOTOR_H
#define MOTOR_H

#define A1_Pin GPIO_PIN_4
#define A1_GPIO_Port GPIOE
#define A2_Pin GPIO_PIN_3
#define A2_GPIO_Port GPIOE

#define B1_Pin GPIO_PIN_5
#define B1_GPIO_Port GPIOE
#define B2_Pin GPIO_PIN_6
#define B2_GPIO_Port GPIOE

#define C1_Pin GPIO_PIN_6
#define C1_GPIO_Port GPIOD
#define C2_Pin GPIO_PIN_5
#define C2_GPIO_Port GPIOD

#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOC

enum MOTOR_MODE
{
    MOTOR_SPEED = 0,
    MOTOR_POSITION = 1
};

typedef struct motorDate
{
    uint8_t motor_mode; // 电机模式：速度环/位置环
    uint8_t motor_mode_sign[2];
    pids pid1;     // 速度环
    pids pid2;     // 位置环
    float cout[11];
} MG513;

void motor_pid_init(MG513 *motor, pids *PID, uint8_t motor_mode, fp32 goal,
                    fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout); //  // 电机PID初始化
void MG513_Motor_pwm_init(void);
void MG513_calculate(pids *MOTOR_PID[4], float *cout[4]);//pid计算
void MG513_encodervalue_get(float a[11], TIM_HandleTypeDef *_tim); // 编码器读取
void MG513_Motor_stop(void);

// void MG513_forword_A(void);
// void MG513_back_A(void);
// void MG513_forword_B(void);
// void MG513_back_B(void);
// void MG513_forword_C(void);
// void MG513_back_C(void);
// void MG513_forword_D(void);
// void MG513_back_D(void);

#endif
