#include  "math1.h"

void send_motor_measure(Callback *stru, uint8_t data[8])
{
    uint16_t out_temp[4];
    for (uint8_t i; i < 4; i++)
    {
        out_temp[i] = (uint16_t)(stru->PID[i].out * 10000);
    }
    data[0] = (uint8_t)(out_temp[0] >> 8 & 0x0F);
    data[1] = (uint8_t)(out_temp[0]);
    data[2] = (uint8_t)(out_temp[1] >> 8 & 0x0F);
    data[3] = (uint8_t)(out_temp[1]);
    data[4] = (uint8_t)(out_temp[2] >> 8 & 0x0F);
    data[5] = (uint8_t)(out_temp[2]);
    data[6] = (uint8_t)(out_temp[3] >> 8 & 0x0F);
    data[7] = (uint8_t)(out_temp[3]);
}
