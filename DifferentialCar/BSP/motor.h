#include "gpio.h"
#include "math.h"
#include "pid.h"
#include "tim.h"

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define R 0.1f // 车中心到轮子的距离 单位：m；
#define p 3.141592f
#define k_rpm p *R / 30.0f

#define D 0.065f          // 单位：m
#define Redu_Ratio 30.0f  // 减速比
#define Line_number 13.0f // 线数
#define Ti 0.001f         // 采样周期



#define A1_Pin GPIO_PIN_8
#define A1_GPIO_Port GPIOE
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOB

#define B1_Pin GPIO_PIN_1
#define B1_GPIO_Port GPIOB
#define B2_Pin GPIO_PIN_7
#define B2_GPIO_Port GPIOE

enum MOTOR_MODE
{
    MOTOR_SPEED = 0,
    MOTOR_POSITION = 1
};

typedef struct motorDate
{
    uint8_t motor_mode; // 电机模式：速度环/位置环
    uint8_t motor_mode_sign[2];
    pids pid1; // 速度环
    pids pid2; // 位置环
    float cout[11];
} MG513;

void motor_pid_init(MG513 *motor, uint8_t motor_mode, fp32 goal,
                    fp32 KP, fp32 KI, fp32 KD, fp32 maxOut, fp32 maxIout); //  // 电机PID初始化
void MG513_Motor_pwm_init(void);
void MG513_encodervalue_get(float a[11], TIM_HandleTypeDef *_tim); // 编码器读取
void MG513_Calculate(pids *MOTOR_PID, float cout[11]);             // pid计算
void MG513_pwm_send(pids *MOTOR_PID[4]);                           // PWM发送
void MG513_Motor_stop(void);                                       // 电机停止
void MG513_SET(pids *MOTOR_PID, float goal);                       // PID目标值设置

#endif
