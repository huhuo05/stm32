#include "math.h"

// void DIJ3508_send_motor_measure(float out[4], uint8_t data[8])
// {
//     uint16_t out_temp[4];
//     for (uint8_t i; i < 4; i++)
//     {
//         out_temp[i] = (uint16_t)(out[i] * 10000);
//     }
//     data[0] = (uint8_t)(out_temp[0] >> 8 & 0x0F);
//     data[1] = (uint8_t)(out_temp[0]);
//     data[2] = (uint8_t)(out_temp[1] >> 8 & 0x0F);
//     data[3] = (uint8_t)(out_temp[1]);
//     data[4] = (uint8_t)(out_temp[2] >> 8 & 0x0F);
//     data[5] = (uint8_t)(out_temp[2]);
//     data[6] = (uint8_t)(out_temp[3] >> 8 & 0x0F);
//     data[7] = (uint8_t)(out_temp[3]);
// }

void Mean_filtering(float a[11])
{
    a[9] = a[8];
    a[8] = a[7];
    a[7] = a[6];
    a[6] = a[5];
    a[5] = a[4];
    a[4] = a[3];
    a[3] = a[2];
    a[2] = a[1];
    a[1] = a[0];
    a[10] = (a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6] + a[7] + a[8] + a[9]) / 10.0f;
}
