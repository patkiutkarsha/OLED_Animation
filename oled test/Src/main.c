/* USER CODE BEGIN Header */
/** Utkarsha
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "fonts.h"
#include "math.h"
#include "stdio.h"
#include "stdbool.h"
#define FALSE (bool)false
#define TRUE  (bool)true
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
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static bool bFirstTime,bBlinkFlag = FALSE;
bool bPrev = TRUE;
static uint32_t ulCount = 0;
void vBlink(void);
void vAudioWave(void);
uint16_t slMapSine(uint32_t x, uint8_t l);
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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	SSD1306_Init (); 
  /* USER CODE END 2 */
	//vAudioWave();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		
//		if(bFirstTime != bPrev)
//		{
//			bPrev = bFirstTime;
//			SSD1306_GotoXY (10,10); // goto 10, 10 130/64
//			SSD1306_Puts ("HELLO", &Font_11x18, 1); // print Hello 
//			SSD1306_GotoXY (10, 30); 
//			SSD1306_Puts ("WORLD !!", &Font_11x18, 1); 
//			//HAL_Delay(1000);
//			SSD1306_Clear();
//		}
//		else
//		{
//			SSD1306_Clear();
			//SSD1306_DrawLine(0,52,130,52,1);
			//vAudioWave();
			vBlink();
			
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

#define Pi 3.14
static uint32_t x = 0, Mod =7;
static uint32_t ulAmplitude = 8, ulFrequency = 15;

void vAudioWave(void)
{
	//SSD1306_DrawLine(0,52,130,52,1);
	for(int i =0;i<130;i++)
	{
		//x = sin(i*3.14);
		//x = (sin(i*2*Pi/50)+1)*(2096);//(sin(i*2*Pi/100)+1)*(4096/2)
		x = (sin(i*ulFrequency*Pi/100)+Mod)*(ulAmplitude);//sin((i*pi)/4);//(sin(i*Freq*Pi/100)+1)*(Ampl)
		
		SSD1306_DrawPixel(i,x,1);
		SSD1306_UpdateScreen();
	}
//	for(int i =0;i<130;i++)
//	{
//		//x = sin(i*3.14);
//		//x = (sin(i*2*Pi/50)+1)*(2096);//(sin(i*2*Pi/100)+1)*(4096/2)
//		x = (sin(i*ulFrequency*Pi/100)+Mod)*(ulAmplitude);//sin((i*pi)/4);//(sin(i*Freq*Pi/100)+1)*(Ampl)
//		
//		//x = slMapSine(x,mod);
//		SSD1306_DrawPixel(i,x,0);
//		SSD1306_UpdateScreen();
//	}	
	
	
}

//uint16_t slMapSine(uint32_t x, uint8_t l)
//{
//	if(x <= 0)
//		x = 0;
//	else if(x <= l || x >= l)
//		x = x + l;
//	else
//		x = x;
//	
//	return x;
//}

void vBlink(void)
{
	for(int i=0;i<130;i++)
	{
		
		if(i < 32 || i > 96)
		{
			SSD1306_DrawPixel(i,56,1);
		}
		else
		{
			x = (sin(i*ulFrequency*Pi/100)+Mod)*(ulAmplitude);//sin((i*pi)/4);//(sin(i*Freq*Pi/100)+1)*(Ampl)
			SSD1306_DrawPixel(i,x,1);
		}
		
		if(i>= 10 && i <= 20) 
		{
			SSD1306_DrawFilledRectangle(20,10,30,i,1);
			SSD1306_DrawFilledRectangle(80,10,30,i,1);
		}
		SSD1306_UpdateScreen();
	}
	//HAL_Delay(1000);
	for(int i=0;i<130;i++)
	{
		if(i < 32 || i > 96)
		{
			//SSD1306_DrawPixel(i,50,0);
		}
		else
		{
			x = (sin(i*ulFrequency*Pi/100)+Mod)*(ulAmplitude);//sin((i*pi)/4);//(sin(i*Freq*Pi/100)+1)*(Ampl)
			SSD1306_DrawPixel(i,x,0);
		}
		
		if(i>= 10 && i <= 20)
		{
			SSD1306_DrawFilledRectangle(20,10,30,i,0);
			SSD1306_DrawFilledRectangle(80,10,30,i,0);
		}
		SSD1306_UpdateScreen();
	}	
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

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

