#include "bsp_tim.h"

void TIM_INIT(void) {
  HAL_TIM_Base_Start_IT(&htim6);
}
