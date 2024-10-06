#include "APP_remote_control.h"

void PS2_control()
{
    uint8_t mid = 128;

    PS2_SetInit();
    HAL_Delay(500);
    PS2_Receive();
}
