/**
		   ____                    _____ _______ _____       XTARK@塔克创新
		  / __ \                  / ____|__   __|  __ \
		 | |  | |_ __   ___ _ __ | |       | |  | |__) |
		 | |  | | '_ \ / _ \ '_ \| |       | |  |  _  /
		 | |__| | |_) |  __/ | | | |____   | |  | | \ \
		  \____/| .__/ \___|_| |_|\_____|  |_|  |_|  \_\
				| |
				|_|                OpenCTR   机器人控制器

  ******************************************************************************
  *
  * 版权所有： XTARK@塔克创新  版权所有，盗版必究
  * 公司网站： www.xtark.cn   www.tarkbot.com
  * 淘宝店铺： https://xtark.taobao.com
  * 塔克微信： 塔克创新（关注公众号，获取最新更新资讯）
  *
  ******************************************************************************
  * @作  者  Musk Han@XTARK
  * @版  本  V1.0
  * @日  期  2022-7-26
  * @内  容  PS2无线手柄函数文件
  *
  ******************************************************************************
  * @说  明
  *
  *   PS2数据定义
  *   BYTE   DATA   解释
  *   01     idle
  *   02     0x73   手柄工作模式
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    口
  *   06     data   右边摇杆  0x00 = 左    0xff = 右
  *   07     data   右边摇杆  0x00 = 上    0xff = 下
  *   08     data   左边摇杆  0x00 = 左    0xff = 右
  *   09     data   左边摇杆  0x00 = 上    0xff = 下
  *
  ******************************************************************************
  */

#include "ax_ps2.h"
#include "ax_delay.h"
#include "ax_sys.h"
#include "gpio.h"

const uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 请求获取数据命令
static uint8_t PS2_data[9] = {0};													// 接收的数据

/**
 * @简  述  PS2数据读写函数
 * @参  数  data:要写入的数据
 * @返回值  读出数据
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

	// 返回读出数据
	return res;
}

/**
 * @简  述  PS2获取按键及摇杆数值。
 * @参  数  *JoystickStruct 手柄键值结构体
 * @返回值  无
 */
void AX_PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
	uint8_t i;

	// 使能手柄
	CS_L();
	// 读取PS2数据
	for (i = 0; i < 9; i++)
	{
		PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
		AX_Delayus(16);
	}
	//	AX_Delayus(25);
	// 关闭使能
	CS_H();

	// 数值传递
	JoystickStruct->mode = PS2_data[1];
	JoystickStruct->btn1 = ~PS2_data[3];
	JoystickStruct->btn2 = ~PS2_data[4];
	JoystickStruct->RJoy_LR = PS2_data[5];
	JoystickStruct->RJoy_UD = PS2_data[6];
	JoystickStruct->LJoy_LR = PS2_data[7];
	JoystickStruct->LJoy_UD = PS2_data[8];
}

/******************* (C) 版权 2022 XTARK **************************************/
