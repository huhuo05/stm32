#include "bsp_gpio.h"
   
void classic_init(void)
{
    // ³õÊ¼»¯Òý½Å
    HAL_GPIO_WritePin(GPIOC, A1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(GPIOE, B1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(GPIOE, C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
}
//
void MOVE_dir(void)
{
    // A
    HAL_GPIO_WritePin(GPIOC, A1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(GPIOE, B1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(GPIOE, C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
}

//
void MOVE_back(void)
{
    // A
    HAL_GPIO_WritePin(GPIOC, A1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(GPIOE, B1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(GPIOE, C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
}

//
void Mini_top(void)
{
    // A
    HAL_GPIO_WritePin(GPIOC, A1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(GPIOE, B1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(GPIOE, C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
}

//
void MOVE_left(void)
{
    // A
    HAL_GPIO_WritePin(GPIOC, A1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(GPIOE, B1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(GPIOE, C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
}

//
void MOVE_right(void)
{
    // A
    HAL_GPIO_WritePin(GPIOC, A1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, A2_Pin, GPIO_PIN_RESET);
    // B
    HAL_GPIO_WritePin(GPIOE, B1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, B2_Pin, GPIO_PIN_RESET);
    // C
    HAL_GPIO_WritePin(GPIOE, C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, C2_Pin, GPIO_PIN_RESET);
    // D
    HAL_GPIO_WritePin(GPIOE, D1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, D2_Pin, GPIO_PIN_RESET);
}