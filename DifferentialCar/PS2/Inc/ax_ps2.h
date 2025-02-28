/**			                                                    
		   ____                    _____ _______ _____       XTARK@���˴���
		  / __ \                  / ____|__   __|  __ \ 
		 | |  | |_ __   ___ _ __ | |       | |  | |__) |
		 | |  | | '_ \ / _ \ '_ \| |       | |  |  _  / 
		 | |__| | |_) |  __/ | | | |____   | |  | | \ \ 
		  \____/| .__/ \___|_| |_|\_____|  |_|  |_|  \_\
				| |                                     
				|_|                OpenCTR   �����˿�����
									 
  ****************************************************************************** 
  *           
  * ��Ȩ���У� XTARK@���˴���  ��Ȩ���У�����ؾ�
  * ��˾��վ�� www.xtark.cn   www.tarkbot.com
  * �Ա����̣� https://xtark.taobao.com  
  * ����΢�ţ� ���˴��£���ע���ںţ���ȡ���¸�����Ѷ��
  *      
  ******************************************************************************
  * @��  ��  Musk Han@XTARK
  * @��  ��  PS2�����ֱ������ļ�
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_PS2_H
#define __AX_PS2_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f4xx.h"

//PS2�ֱ���ֵ���ݽṹ��	 
typedef struct			 				
{
  uint8_t mode;		    /* �ֱ��Ĺ���ģʽ */

  uint8_t btn1;         /* B0:SLCT B3:STRT B4:UP B5:R B6:DOWN B7:L   */

  uint8_t btn2;         /* B0:L2 B1:R2 B2:L1 B3:R1 B4:/\ B5:O B6:X B7:�� */

  uint8_t RJoy_LR;      /* �ұ�ҡ��  0x00 = ��    0xff = ��   */

  uint8_t RJoy_UD;      /* �ұ�ҡ��  0x00 = ��    0xff = ��   */

  uint8_t LJoy_LR;      /* ���ҡ��  0x00 = ��    0xff = ��   */

  uint8_t LJoy_UD;      /* ���ҡ��  0x00 = ��    0xff = ��   */
	
}JOYSTICK_TypeDef;


// �����Զ���
#define PS2_CS_Pin GPIO_PIN_12
#define PS2_CS_GPIO_Port GPIOB
#define PS2_CLK_Pin GPIO_PIN_13
#define PS2_CLK_GPIO_Port GPIOB
#define PS2_DO_Pin GPIO_PIN_14
#define PS2_DO_GPIO_Port GPIOB
#define PS2_DI_Pin GPIO_PIN_15
#define PS2_DI_GPIO_Port GPIOB

////PS2�ֱ������������
//#define DI()     PAin(4)      //������������

//#define CMD_H()   PAout(5)=1   //����λ��
//#define CMD_L()   PAout(5)=0   //����λ��

//#define CS_H()   PAout(6)=1    //CS����(����ATT)
//#define CS_L()   PAout(6)=0    //CS����(����ATT)

//#define CLK_H()  PAout(7)=1    //ʱ������
//#define CLK_L()  PAout(7)=0    //ʱ������

#define DI()     HAL_GPIO_ReadPin(PS2_DI_GPIO_Port, PS2_DI_Pin)    //������������

#define CMD_H()   HAL_GPIO_WritePin(PS2_DO_GPIO_Port, PS2_DO_Pin, GPIO_PIN_SET)  //����λ��
#define CMD_L()   HAL_GPIO_WritePin(PS2_DO_GPIO_Port, PS2_DO_Pin, GPIO_PIN_RESET)   //����λ��

#define CS_H()   HAL_GPIO_WritePin(PS2_CS_GPIO_Port, PS2_CS_Pin, GPIO_PIN_SET)    //CS����(����ATT)
#define CS_L()   HAL_GPIO_WritePin(PS2_CS_GPIO_Port, PS2_CS_Pin, GPIO_PIN_RESET)    //CS����(����ATT)

#define CLK_H()   HAL_GPIO_WritePin(PS2_CLK_GPIO_Port, PS2_CLK_Pin, GPIO_PIN_SET)   //ʱ������
#define CLK_L()  HAL_GPIO_WritePin(PS2_CLK_GPIO_Port, PS2_CLK_Pin, GPIO_PIN_RESET)   //ʱ������

/*** PS2�����ֱ��������� **********/
void AX_PS2_Init(void);  //PS2��ʼ��
void AX_PS2_ScanKey(JOYSTICK_TypeDef* JoystickStruct);//PS2��ȡ������ҡ����ֵ

#endif 

/******************* (C) ��Ȩ 2023 XTARK **************************************/
