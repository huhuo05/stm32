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
  * @��  ��  �����ʱ����
  ******************************************************************************
  * @˵  ��
  *
  * 1.��ʱ����ʹ�õδ�ʱ��ʵ��
  * 
  ******************************************************************************
  */

#include "ax_delay.h"



void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  if (SysTick_CLKSource == SYSTICK_CLKSOURCE_HCLK)
  {
    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
  }
  else
  {
    SysTick->CTRL &= SYSTICK_CLKSOURCE_HCLK_DIV8;
  }
}


/**
  * @��  ��  ��ʱ������ʼ��
  * @��  ��  ��
  * @����ֵ  ��
  */
void AX_DELAY_Init(void) 
{	 

	/* ��ʱ���� SysTick ���� */
	SysTick_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8); 	//ʱ�ӹ̶�ΪAHBʱ�ӵ�1/8

}

/**
  * @��  ��  ���΢����ʱ
  * @��  ��  us����ʱ���ȣ���λus	  
  * @����ֵ  ��
  */
void AX_Delayus(uint32_t us)
{
	uint32_t temp;
	
	SysTick->LOAD=21*us; 				 		 
	SysTick->VAL=0x00;        				
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;  	 
	
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));	 
	
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; 
	SysTick->VAL =0X00;    
}

/**
  * @��  ��  ��������ʱ������
  * @��  ��  ms����ʱ���ȣ���λms	  	  
  * @����ֵ  ��
  * @˵  ��  ע��ms�ķ�Χ��SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nTime<=0xffffff*8*1000/SYSCLK
  *          ��72M������,ms<=1864ms 
  */
static void Delay_ms(uint16_t ms)
{	 		  	  
	uint32_t temp;	
	
	SysTick->LOAD=(uint32_t)21000*ms;			
	SysTick->VAL =0x00;           		
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 
	
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	
	
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      
	SysTick->VAL =0X00; 
}


/**
  * @��  ��  ���ms��ʱ,ϵͳ���������󣬲�Ҫʹ�øú���
  * @��  ��  ms����ʱ���ȣ���λms	  
  * @����ֵ  ��
  */
void AX_Delayms(uint16_t ms)
{
	uint8_t repeat=ms/500;																
	uint16_t remain=ms%500;
	
	while(repeat)
	{
		Delay_ms(500);
		repeat--;
	}
	
	if(remain)
	{
		Delay_ms(remain);
	}
}


/******************* (C) ��Ȩ 2022 XTARK **************************************/
