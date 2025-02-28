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
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// #include "ax_ps2.h"
// #include "ax_sys.h"   //系统设置
// #include "ax_delay.h" //软件延时
#include "WIT.h"
#include "oled.h"
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
uint8_t key = 0;
int8_t email[44] = {NULL};

float Turning_data[2][2] = {0.8f, 1.4f, 1.4f, 0.8f}; //

MG513 A_motor;
MG513 B_motor;
Car car;

WIT wit;

// JOYSTICK_TypeDef my_joystick; // PS2手柄数据

//void KEY_SCAN(); // 按键扫描
void Grayscale_sensing_scan(Car *mg, GPIO_TypeDef *GPIO1, uint16_t GPIO_Pin1, GPIO_TypeDef *GPIO2, uint16_t GPIO_Pin2, GPIO_TypeDef *GPIO3,
                            uint16_t GPIO_Pin3, GPIO_TypeDef *GPIO4, uint16_t GPIO_Pin4);

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
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  MG513_Init(&A_motor, PID_POSITION, 1.0f, 100.0f, 1.0f, 5.0f, 300.0f, 200.0f);
  MG513_Init(&B_motor, PID_POSITION, -1.0f, 100.0f, 1.0f, 5.0f, 300.0f, 200.0f);

  Classic_init(&car, &A_motor, &B_motor, NULL, NULL);

  MG513_Motor_pwm_init();

  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);

  // OLED_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  printf("%f/n",car.motorgroup[0]->pid1.wheel_speed);
	  printf("%f/n",car.motorgroup[1]->pid1.wheel_speed);
    // //    AX_PS2_ScanKey(&my_joystick); // PS2手柄数据获取
    // ////    AX_Delayms(10);               // PS2的SPI模拟延时
    // KEY_SCAN();
    // HAL_Delay(10);
    // switch (key)
    // {
    // case 0:
    // {
    //   OLED_ShowString(0, 0, "key=");
    //   OLED_ShowNum(40, 0, key, 2, 16);
    //   break;
    // }
    // case 1:
    // {
    //   OLED_ShowString(0, 0, "key=");
    //   OLED_ShowNum(40, 0, key, 2, 16);
    //   break;
    // }
    // case 2:
    // {
    //   OLED_ShowString(0, 0, "key=");
    //   OLED_ShowNum(40, 0, key, 2, 16);
    //   break;
    // }
    // }
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
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
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
void KEY_SCAN()
{
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
  {
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
    {
      HAL_Delay(10);
      key++;
      //      if (key > 6)
      //        key = 0;
    }
  }
}

void Grayscale_sensing_scan(Car *mg, GPIO_TypeDef *GPIO1, uint16_t GPIO_Pin1, GPIO_TypeDef *GPIO2, uint16_t GPIO_Pin2, GPIO_TypeDef *GPIO3,
                            uint16_t GPIO_Pin3, GPIO_TypeDef *GPIO4, uint16_t GPIO_Pin4)
{
  static uint8_t time = 0;
  if (HAL_GPIO_ReadPin(GPIO1, GPIO_Pin1) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIO2, GPIO_Pin2) == GPIO_PIN_SET ||
      HAL_GPIO_ReadPin(GPIO3, GPIO_Pin3) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIO4, GPIO_Pin4) == GPIO_PIN_SET)
  {
    time++;
    if (time % 2 != 0)
    {
      //
      MG513_SET(&mg->motorgroup[0]->pid1, 1);
      MG513_SET(&mg->motorgroup[1]->pid1, 1);
    }
    else
    {
      if (time % 4 == 0)
      {
        MG513_SET(&mg->motorgroup[0]->pid1, 1.4);
        MG513_SET(&mg->motorgroup[1]->pid1, 0.8);
      }
      else if (time % 4 == 2)
      {
        MG513_SET(&mg->motorgroup[0]->pid1, 0);
        MG513_SET(&mg->motorgroup[1]->pid1, 0);
      }
    }
  }
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  if (htim == &htim6)
  {
    MG513_encodervalue_get(car.motorgroup[0]->cout, &htim2);
    MG513_encodervalue_get(car.motorgroup[1]->cout, &htim3);
  }
  if (htim == &htim7)
  {
    // 底盘计算
    MG513_Calculate(&car.motorgroup[0]->pid1, car.motorgroup[0]->cout);
    MG513_Calculate(&car.motorgroup[1]->pid1, car.motorgroup[1]->cout);
    //
    pids *temp_pid[4] = {NULL};
    for (int i = 0; i < 4; i++)
    {
      temp_pid[i] = &car.motorgroup[i]->pid1;
    }
    MG513_pwm_send(temp_pid);
  }
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM14) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

#ifdef  USE_FULL_ASSERT
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
