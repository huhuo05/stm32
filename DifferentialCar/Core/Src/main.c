/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "WIT.h"
#include "APP_classic.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int8_t email[44] = {NULL};
MG513 A_motor;
MG513 B_motor;
Car car;

WIT wit;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_SPI2_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  MG513_Init(&A_motor, PID_POSITION, 100, 1, 0, 0, 399, 20);
  MG513_Init(&B_motor, PID_POSITION, 100, 1, 0, 0, 399, 20);
  // 注册电机
  Classic_init(&car, &A_motor, &B_motor, NULL, NULL);

  MG513_Motor_pwm_init();

  // 定时器中断初始化
  HAL_TIM_Base_Start_IT(&htim6); // 获取编码
  HAL_TIM_Base_Start_IT(&htim7); // pid计算
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    WIT_resolving(&wit);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim6)
  {
    MG513_encodervalue_get(car.motorgroup[0]->cout, &htim2);
    MG513_encodervalue_get(car.motorgroup[1]->cout, &htim3);
  }
  if (htim == &htim7)
  {
    // 计算
    MG513_Calculate(&car.motorgroup[0]->pid1, car.motorgroup[0]->cout);
    MG513_Calculate(&car.motorgroup[1]->pid1, car.motorgroup[1]->cout);
    // 发送
    pids *temp_pid[4] = {NULL};
    for (int i = 0; i < 4; i++)
    {
      temp_pid[i] = &car.motorgroup[i]->pid1;
    }
    MG513_pwm_send(temp_pid);
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart2)
  {
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)&email, sizeof(email));
    for (int i = 0; i < sizeof(email); i++)
    {
      if (email[i] == 0x50)
      {
        if (email[i + 1] == 0x51)
        {
          if (email[i + 10] == email[i] + email[i + 1] + email[i + 2] + email[i + 3] + email[i + 4] +
                                   email[i + 5] + email[i + 6] + email[i + 7] + email[i + 8] + email[i + 9])
          {
            for (uint8_t j = 0; j < 9; j++)
            {
              wit.Acceleration[i] = email[i + 2 + j];
            }
          }
        }
        else if (email[i + 1] == 0x52)
        {
          if (email[i + 10] == email[i] + email[i + 1] + email[i + 2] + email[i + 3] + email[i + 4] +
                                   email[i + 5] + email[i + 6] + email[i + 7] + email[i + 8] + email[i + 9])
          {
            for (uint8_t j = 0; j < 9; j++)
            {
              wit.Angular_velocity[i] = email[i + 2 + j];
            }
          }
          else if (email[i + 1] == 0x53)
          {
            if (email[i + 10] == email[i] + email[i + 1] + email[i + 2] + email[i + 3] + email[i + 4] +
                                     email[i + 5] + email[i + 6] + email[i + 7] + email[i + 8] + email[i + 9])
            {
              for (uint8_t j = 0; j < 9; j++)
              {
                wit.Angle[i] = email[i + 2 + j];
              }
            }
            else if (email[i + 1] == 0x59)
            {
              if (email[i + 10] == email[i] + email[i + 1] + email[i + 2] + email[i + 3] + email[i + 4] +
                                       email[i + 5] + email[i + 6] + email[i + 7] + email[i + 8] + email[i + 9])
              {
                for (uint8_t j = 0; j < 9; j++)
                {
                  wit.Quaternion[i] = email[i + 2 + j];
                }
              }
            }
          }
        }
      }
    }
  }
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
