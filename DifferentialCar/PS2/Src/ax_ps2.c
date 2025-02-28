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
  * @��  ��  V1.0
  * @��  ��  2022-7-26
  * @��  ��  PS2�����ֱ������ļ�
  *
  ******************************************************************************
  * @˵  ��
  *
  *   PS2���ݶ���
  *   BYTE   DATA   ����
  *   01     idle
  *   02     0x73   �ֱ�����ģʽ
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    ��
  *   06     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   07     data   �ұ�ҡ��  0x00 = ��    0xff = ��
  *   08     data   ���ҡ��  0x00 = ��    0xff = ��
  *   09     data   ���ҡ��  0x00 = ��    0xff = ��
  *
  ******************************************************************************
  */

#include "ax_ps2.h"
#include "ax_delay.h"
#include "ax_sys.h"
#include "gpio.h"

const uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // �����ȡ��������
static uint8_t PS2_data[9] = {0};													// ���յ�����

/**
 * @��  ��  PS2���ݶ�д����
 * @��  ��  data:Ҫд�������
 * @����ֵ  ��������
 */
static uint8_t PS2_ReadWriteData(uint8_t data)
{
	uint8_t ref, res;

	for (ref = 0x01; ref > 0x00; ref <<= 1)
	{
		CLK_L();
		if (ref & data)
		{
			CMD_H();
		}
		else
		{
			CMD_L();
		}

		AX_Delayus(16);

		CLK_H();
		if (DI())
		{
			res |= ref;
		}

		AX_Delayus(16);
	}

	CMD_H();

	// ���ض�������
	return res;
}

/**
 * @��  ��  PS2��ȡ������ҡ����ֵ��
 * @��  ��  *JoystickStruct �ֱ���ֵ�ṹ��
 * @����ֵ  ��
 */
void AX_PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
	uint8_t i;

	// ʹ���ֱ�
	CS_L();
	// ��ȡPS2����
	for (i = 0; i < 9; i++)
	{
		PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
		AX_Delayus(16);
	}
	//	AX_Delayus(25);
	// �ر�ʹ��
	CS_H();

	// ��ֵ����
	JoystickStruct->mode = PS2_data[1];
	JoystickStruct->btn1 = ~PS2_data[3];
	JoystickStruct->btn2 = ~PS2_data[4];
	JoystickStruct->RJoy_LR = PS2_data[5];
	JoystickStruct->RJoy_UD = PS2_data[6];
	JoystickStruct->LJoy_LR = PS2_data[7];
	JoystickStruct->LJoy_UD = PS2_data[8];
}

/******************* (C) ��Ȩ 2022 XTARK **************************************/
