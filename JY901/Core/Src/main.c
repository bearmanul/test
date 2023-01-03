/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "jy901.h"
#include "encoder.h"
#include "pid.h"



extern struct User_USART JY901_data;
extern struct _Motor motor1;
extern struct _Motor motor2;
extern struct _PID pid1;//w3
extern struct _PID pid2;//w4

//User_USART JY901_data;

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}



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
	PID_Init(&pid1,3);
	PID_Init(&pid2,4);
	motor1.speed = 0;
	motor2.speed = 0;

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  User_USART_Init(&JY901_data);
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);  
	HAL_UART_Receive_DMA(&huart2,JY901_data.RxBuffer,RXBUFFER_LEN);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&GAP_TIM);
	
	
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);//w3_right_0 is forward,1_is_back
	//__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 300);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  
	  
	  //printf("%f\n",motor1.speed);
	  //printf("%f\n",motor2.speed);
	  
	  
//	HAL_Delay(50);
//	JY901_Process();
//	printf("%f\n",JY901_data.angle.angle[0]);
//	printf("%f",JY901_data.angle.angle[1]);
//	printf("%f",JY901_data.angle.angle[2]);
	
	  
//	printf("123\n");
//	HAL_Delay(1000);
	  
	  
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//输入捕获中断
{
	int judge3,judge4;//判断轮子正向或反向转
	static float catch3[3],catch4[3];//存储输入捕获的值 0：上一次上跳沿的定时器的值  1：这一次上跳沿定时器的值   2：两次上跳沿定时器值之差
	if(htim==&htim1&&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)//轮3编码器是否输出上跳沿
	{
//		printf("1");
		judge3=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);//判断轮3 GPIO的高低电平来判断轮子旋转方向
		catch3[1]=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_3);//捕获编码器输入上跳沿时定时器通道3的值
//		printf("%f\t",catch3[1]);
		catch3[2] = catch3[1] - catch3[0];//计算得到两次上跳沿定时器值的差
		catch3[0] = catch3[1];//将这一次上跳沿的值赋给上一次
		if(catch3[2]<0)
		{
			catch3[2]+=0xffff;//消除差值中的负数
		}
		if(judge3==0)
		{
			motor1.speed = 532.236/catch3[2];//532.236计算轮3速度2661.18
		}
		if(judge3==1)
		{
			motor1.speed = -532.236/catch3[2];//计算轮3速度
		}
	}
   if(htim==&htim1&&htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)//轮4编码器是否输出上跳沿
	{
//		printf("1");
		judge4=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);//判断轮4 GPIO的高低电平来判断轮子旋转方向
		catch4[1]=HAL_TIM_ReadCapturedValue(htim,TIM_CHANNEL_4);//捕获编码器输入上跳沿时定时器通道4的值
//		printf("%f\t",catch3[1]);
		catch4[2] = catch4[1] - catch4[0];//计算得到两次上跳沿定时器值的差
		catch4[0] = catch4[1];//将这一次上跳沿的值赋给上一次
		if(catch4[2]<0)
		{
			catch4[2]+=0xffff;//消除差值中的负数
		}
		if(judge4==1)
		{
			motor2.speed = 532.236/catch4[2];//计算轮3速度//532.236
		}
		if(judge4==0)
		{
			motor2.speed = -532.236/catch4[2];//计算轮3速度
		}
	}

//	printf("%f\t",catch3[2]);
//	printf("%f\t",catch4[2]);
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
