#include "math.h"

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
