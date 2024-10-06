#include "APP_classic.h"

APP_classic classic;

void Action_solution(uint8_t a, pids *pid1, pids *pid2, pids *pid3, pids *pid4)
{
    fp32 v, v_w, degree; // ´ýÓÅ»¯
    for (uint8_t i = 0; i < 4; i++)
    {
        classic.V[i] = 0;
    }
    switch (a)
    {
    case 1: // positive
    {
        classic.V[0] = (pid1->out + pid2->out + pid3->out + pid4->out) / sqrt(2.0f);
        classic.V[1] = (pid1->out + pid2->out + pid3->out + pid4->out) / sqrt(2.0f);
        classic.V[2] = pid1->out + pid2->out + pid3->out + pid4->out;
        classic.V[3] = sqrt(classic.V[0] * classic.V[0] + classic.V[1] * classic.V[1]);
    }
    break;
    case 0: ;//
	}
}	
