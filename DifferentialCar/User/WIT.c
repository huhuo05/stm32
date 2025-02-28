#include "WIT.h"

uint8_t WIT_Set_order[] = {0xFF, 0xAA, 0x00, 0x00, 0x00};    // 保存
uint8_t WIT_Unlock_order[] = {0xFF, 0xAA, 0x69, 0x88, 0xB4}; // 解锁

uint8_t WIT_Calibrate_order[] = {0xFF, 0xAA, 0x61, 0x01, 0x00};                // 自动校准
uint8_t WIT_Acceleration_calibration_order[] = {0xFF, 0xAA, 0x01, 0x01, 0x00}; // 加速度校准
uint8_t WIT_Angle_calibration_order[] = {0xFF, 0xAA, 0x01, 0x08, 0x00};        // 角度校准
uint8_t WIT_Z_calibration_order[] = {0xFF, 0xAA, 0x01, 0x02, 0x00};            // Z轴置零

// 初始化WITJY60P
void WIT_Init(UART_HandleTypeDef *huartx)
{
    // 发送解锁指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Unlock_order, sizeof(WIT_Unlock_order), 1000);
    // 延时200ms
    HAL_Delay(200);
    // 发送校准指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Calibrate_order, sizeof(WIT_Calibrate_order), 1000);
    // 延时3000ms
    HAL_Delay(3000);
    // 再次发送解锁指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Set_order, sizeof(WIT_Set_order), 1000);
}

// 函数：WIT_Acceleration_calibration
// 功能：进行WIT加速度计校准
void WIT_Acceleration_calibration(UART_HandleTypeDef *huartx)
{
    // 通过串口2发送解锁指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Unlock_order, sizeof(WIT_Unlock_order), 1000);
    // 延时200ms
    HAL_Delay(200);
    // 通过串口2发送校准指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Calibrate_order, sizeof(WIT_Calibrate_order), 1000);
    // 延时5000ms
    HAL_Delay(5000);
    // 通过串口2发送保存指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Set_order, sizeof(WIT_Set_order), 1000);
}

// 函数：WIT_Angle_calibration
// 功能：角度校准
// 参数：UART_HandleTypeDef *huartx
void WIT_Angle_calibration(UART_HandleTypeDef *huartx)
{
    // 发送解锁指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Unlock_order, sizeof(WIT_Unlock_order), 1000);
    // 延时200ms
    HAL_Delay(200);
    // 发送角度校准指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Angle_calibration_order, sizeof(WIT_Angle_calibration_order), 1000);
    // 延时3000ms
    HAL_Delay(3000);
    // 发送保存指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Set_order, sizeof(WIT_Set_order), 1000);
}

void WIT_Z_calibration(UART_HandleTypeDef *huartx)
{
    // 发送解锁指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Unlock_order, sizeof(WIT_Unlock_order), 1000);
    // 延时200ms
    HAL_Delay(200);
    // 发送Z轴置零指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Z_calibration_order, sizeof(WIT_Z_calibration_order), 1000);
    // 延时3000ms
    HAL_Delay(3000);
    // 发送保存指令
    HAL_UART_Transmit(huartx, (uint8_t *)&WIT_Set_order, sizeof(WIT_Set_order), 1000);
}

void WIT_GET_value(WIT *wit)
{
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)&wit->email, sizeof(wit->email));
    for (uint8_t i = 0; i < sizeof(wit->email); i++)
    {
        if (wit->email[i] == 0x55)
        {
            if (wit->email[i + 1] == 0x51)
            {
                for (uint8_t j = 0; j < 9; j++)
                {
                    wit->Acceleration[j] = wit->email[i + 2 + j];
                }
            }
            else if (wit->email[i + 1] == 0x52)
            {

                for (uint8_t j = 0; j < 9; j++)
                {
                    wit->Angular_velocity[j] = wit->email[i + 2 + j];
                }
            }
            else if (wit->email[i + 1] == 0x53)
            {
                for (uint8_t j = 0; j < 9; j++)
                {
                    wit->Angle[j] = wit->email[i + 2 + j];
                }
            }
            else if (wit->email[i + 1] == 0x59)
            {
                for (uint8_t j = 0; j < 9; j++)
                {
                    wit->Quaternion[j] = wit->email[i + 2 + j];
                }
            }
        }
    }
}

void WIT_resolving(WIT *wit)
{
    // 加速度(m/s2)
    wit->Final_data[1] = ((short)((short)wit->Acceleration[1] << 8 | wit->Acceleration[0])) / 32768.0f * 16 * 9.8f; // X轴
    wit->Final_data[2] = ((short)((short)wit->Acceleration[3] << 8 | wit->Acceleration[2])) / 32768.0f * 16 * 9.8f; // Y轴
    wit->Final_data[3] = ((short)((short)wit->Acceleration[5] << 8 | wit->Acceleration[4])) / 32768.0f * 16 * 9.8f; // Z轴
    HAL_Delay(10);

    // 角速度(°/s)
    wit->Final_data[4] = ((short)((short)wit->Angular_velocity[1] << 8 | wit->Angular_velocity[0])) / 32768.0f * 2000; // 角速度X
    wit->Final_data[5] = ((short)((short)wit->Angular_velocity[3] << 8 | wit->Angular_velocity[2])) / 32768.0f * 2000; // 角速度Y
    wit->Final_data[6] = ((short)((short)wit->Angular_velocity[5] << 8 | wit->Angular_velocity[4])) / 32768.0f * 2000; // 角速度Z
    HAL_Delay(10);

    // 角度(°)
    wit->Final_data[7] = ((short)((short)wit->Angle[1] << 8 | wit->Angle[0])) / 32768.0f * 180; // 翻滚角X
    wit->Final_data[8] = ((short)((short)wit->Angle[3] << 8 | wit->Angle[2])) / 32768.0f * 180; // 俯仰角Y
    wit->Final_data[9] = ((short)((short)wit->Angle[5] << 8 | wit->Angle[4])) / 32768.0f * 180; // 偏航角Z
    HAL_Delay(10);

    // 温度(℃)
    wit->Temperature = ((short)((short)wit->Acceleration[7] << 8 | wit->Acceleration[6]))/100.0f;
    HAL_Delay(10);

    // 四元数
    wit->Final_data[10] = ((short)((short)wit->Quaternion[1] << 8 | wit->Quaternion[0])) / 32768.0f;
    wit->Final_data[11] = ((short)((short)wit->Quaternion[3] << 8 | wit->Quaternion[2])) / 32768.0f;
    wit->Final_data[12] = ((short)((short)wit->Quaternion[5] << 8 | wit->Quaternion[4])) / 32768.0f;
    wit->Final_data[13] = ((short)((short)wit->Quaternion[7] << 8 | wit->Quaternion[6])) / 32768.0f;
    HAL_Delay(10);

    // 完成
    wit->Final_data[0] = 0xee;
    wit->Flag = 0x01;
    HAL_Delay(1);
}
