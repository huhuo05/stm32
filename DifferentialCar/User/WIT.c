#include "WIT.h"

void WIT_resolving(WIT *wit)
{
    // 加速度(m/s2)
    wit->Final_data[1] = ((short)(wit->Acceleration[1] << 8 | wit->Acceleration[0])) / 32768.0f * 16 * 9.8f; // X轴
    wit->Final_data[2] = ((short)(wit->Acceleration[3] << 8 | wit->Acceleration[2])) / 32768.0f * 16 * 9.8f; // Y轴
    wit->Final_data[3] = ((short)(wit->Acceleration[5] << 8 | wit->Acceleration[4])) / 32768.0f * 16 * 9.8f; // Z轴

    // 角速度(°/s)
    wit->Final_data[4] = ((short)(wit->Angular_velocity[1] << 8 | wit->Angular_velocity[0])) / 32768.0f * 2000; // 角速度X
    wit->Final_data[5] = ((short)(wit->Angular_velocity[3] << 8 | wit->Angular_velocity[2])) / 32768.0f * 2000; // 角速度Y
    wit->Final_data[6] = ((short)(wit->Angular_velocity[5] << 8 | wit->Angular_velocity[4])) / 32768.0f * 2000; // 角速度Z

    // 角度(°)
    wit->Final_data[7] = ((short)(wit->Angle[1] << 8 | wit->Angle[0])) / 32768.0f * 180; // 翻滚角X
    wit->Final_data[8] = ((short)(wit->Angle[3] << 8 | wit->Angle[2])) / 32768.0f * 180; // 俯仰角Y
    wit->Final_data[9] = ((short)(wit->Angle[5] << 8 | wit->Angle[4])) / 32768.0f * 180; // 偏航角Z

    // 温度(℃)
    wit->Temperature = ((short)(wit->Acceleration[7] << 8 | wit->Acceleration[6]));

    // 四元数
    wit->Final_data[10] = ((short)(wit->Quaternion[1] << 8 | wit->Quaternion[0])) / 32768.0f;
    wit->Final_data[11] = ((short)(wit->Quaternion[3] << 8 | wit->Quaternion[2])) / 32768.0f;
    wit->Final_data[12] = ((short)(wit->Quaternion[5] << 8 | wit->Quaternion[4])) / 32768.0f;
    wit->Final_data[13] = ((short)(wit->Quaternion[7] << 8 | wit->Quaternion[6])) / 32768.0f;

    // 完成
    wit->Final_data[0] = 0xee;
    wit->Flag = 0x01;
}
