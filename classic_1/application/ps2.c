#include "ps2.h"
/*********************************************************
**********************************************************/
#define DELAY_TIME HAL_Delay(5);
uint16_t Handkey;                // ����ֵ��ȡ����ʱ�洢��
uint8_t Comd[2] = {0x01, 0x42};  // ��ʼ�����������
uint8_t Data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // ���ݴ洢����
uint16_t MASK[] = {PSB_SELECT,   PSB_L3,       PSB_R3,   PSB_START, PSB_PAD_UP, PSB_PAD_RIGHT,
                   PSB_PAD_DOWN, PSB_PAD_LEFT, PSB_L2,   PSB_R2,    PSB_L1,     PSB_R1,
                   PSB_GREEN,    PSB_RED,      PSB_BLUE, PSB_PINK};  // ����ֵ�밴����

typedef struct ps2_date {
  int PS2_LX, PS2_LY, PS2_RX, PS2_RY, PS2_KEY;  //
} PS2;

PS2 ps2;

// ���ֱ���������
void PS2_Cmd(uint8_t CMD) {
  volatile uint16_t ref = 0x01;
  Data[1] = 0;
  for (ref = 0x01; ref < 0x0100; ref <<= 1) {
    if (ref & CMD) {
      DO_H;  // ���һλ����λ
    }
    else
      DO_L;

    CLK_H;  // ʱ������
    DELAY_TIME;
    CLK_L;
    DELAY_TIME;
    CLK_H;
    if (DI)
      Data[1] = ref | Data[1];
  }
  HAL_Delay(16);
}

// �ж��Ƿ�Ϊ���ģʽ,0x41=ģ���̵ƣ�0x73=ģ����
// ����ֵ��0�����ģʽ
//		  ����������ģʽ
uint8_t PS2_RedLight(void) {
  CS_L;
  PS2_Cmd(Comd[0]);  // ��ʼ����
  PS2_Cmd(Comd[1]);  // ��������
  CS_H;
  if (Data[1] == 0X73)
    return 0;
  else
    return 1;
}

// ��ȡ�ֱ�����
void PS2_ReadData(void) {
  volatile uint8_t byte = 0;
  volatile uint16_t ref = 0x01;
  CS_L;
  PS2_Cmd(Comd[0]);                 // ��ʼ����
  PS2_Cmd(Comd[1]);                 // ��������
  for (byte = 2; byte < 9; byte++)  // ��ʼ��������
  {
    for (ref = 0x01; ref < 0x100; ref <<= 1) {
      CLK_H;
      DELAY_TIME;
      CLK_L;
      DELAY_TIME;
      CLK_H;
      if (DI)
        Data[byte] = ref | Data[byte];
    }
    HAL_Delay(16);
  }
  CS_H;
}

// �Զ�������PS2�����ݽ��д���,ֻ������������
// ֻ��һ����������ʱ����Ϊ0�� δ����Ϊ1
uint8_t PS2_DataKey() {
  uint8_t index;

  PS2_ClearData();
  PS2_ReadData();

  Handkey = (Data[4] << 8) | Data[3];  // ����16������  ����Ϊ0�� δ����Ϊ1
  for (index = 0; index < 16; index++) {
    if ((Handkey & (1 << (MASK[index] - 1))) == 0)
      return index + 1;
  }
  return 0;  // û���κΰ�������
}

// �õ�һ��ҡ�˵�ģ����	 ��Χ0~256
uint8_t PS2_AnologData(uint8_t button) {
  return Data[button];
}

// ������ݻ�����
void PS2_ClearData(void) {
  uint8_t a;
  for (a = 0; a < 9; a++)
    Data[a] = 0x00;
}

/******************************************************
Function:    void PS2_Vibration(uint8_t motor1, uint8_t motor2)
Description: �ֱ��𶯺�����
Calls:		 void PS2_Cmd(uint8_t CMD);
Input: motor1:�Ҳ�С�𶯵�� 0x00�أ�������
       motor2:�����𶯵�� 0x40~0xFF �������ֵԽ�� ��Խ��
******************************************************/
void PS2_Vibration(uint8_t motor1, uint8_t motor2) {
  CS_L;
  HAL_Delay(16);
  PS2_Cmd(0x01);  // ��ʼ����
  PS2_Cmd(0x42);  // ��������
  PS2_Cmd(0X00);
  PS2_Cmd(motor1);
  PS2_Cmd(motor2);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  CS_H;
  HAL_Delay(16);
}

// short poll
void PS2_ShortPoll(void) {
  CS_L;
  HAL_Delay(16);
  PS2_Cmd(0x01);
  PS2_Cmd(0x42);
  PS2_Cmd(0X00);
  PS2_Cmd(0x00);
  PS2_Cmd(0x00);
  CS_H;
  HAL_Delay(16);
}

// ��������
void PS2_EnterConfing(void) {
  CS_L;
  HAL_Delay(16);
  PS2_Cmd(0x01);
  PS2_Cmd(0x43);
  PS2_Cmd(0X00);
  PS2_Cmd(0x01);
  PS2_Cmd(0x00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  CS_H;
  HAL_Delay(16);
}

// ����ģʽ����
void PS2_TurnOnAnalogMode(void) {
  CS_L;
  PS2_Cmd(0x01);
  PS2_Cmd(0x44);
  PS2_Cmd(0X00);
  PS2_Cmd(0x01);  // analog=0x01;digital=0x00  �������÷���ģʽ
  PS2_Cmd(0x03);  // Ox03�������ã�������ͨ��������MODE������ģʽ��
                  // 0xEE�������������ã���ͨ��������MODE������ģʽ��
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  PS2_Cmd(0X00);
  CS_H;
  HAL_Delay(16);
}

// ������
void PS2_VibrationMode(void) {
  CS_L;
  HAL_Delay(16);
  PS2_Cmd(0x01);
  PS2_Cmd(0x4D);
  PS2_Cmd(0X00);
  PS2_Cmd(0x00);
  PS2_Cmd(0X01);
  CS_H;
  HAL_Delay(16);
}

// ��ɲ���������
void PS2_ExitConfing(void) {
  CS_L;
  HAL_Delay(16);
  PS2_Cmd(0x01);
  PS2_Cmd(0x43);
  PS2_Cmd(0X00);
  PS2_Cmd(0x00);
  PS2_Cmd(0x5A);
  PS2_Cmd(0x5A);
  PS2_Cmd(0x5A);
  PS2_Cmd(0x5A);
  PS2_Cmd(0x5A);
  CS_H;
  HAL_Delay(16);
}

// �ֱ����ó�ʼ��
void PS2_SetInit(void) {
  PS2_ShortPoll();
  PS2_ShortPoll();
  PS2_ShortPoll();
  PS2_EnterConfing();      // ��������ģʽ
  PS2_TurnOnAnalogMode();  // �����̵ơ�����ģʽ����ѡ���Ƿ񱣴�
  // PS2_VibrationMode();	//������ģʽ
  PS2_ExitConfing();  // ��ɲ���������
}

// ��ȡ�ֱ���Ϣ
void PS2_Receive(void) {
  ps2.PS2_LX = PS2_AnologData(PSS_LX);
  ps2.PS2_LY = PS2_AnologData(PSS_LY);
  ps2.PS2_RX = PS2_AnologData(PSS_RX);
  ps2.PS2_RY = PS2_AnologData(PSS_RY);
  ps2.PS2_KEY = PS2_DataKey();
}