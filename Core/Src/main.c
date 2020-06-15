/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "notes.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PI 3.1416f
#define SAMPLING_RATE 200
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;
DMA_HandleTypeDef hdma_dac2;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

/* USER CODE BEGIN PV */
volatile int tempo = 115;
volatile char *sequence[8] = {"C4 ", "D4 ", "E4 ", "F4 ", "G4 ", "A4 ", "B4 ", "C5 "};
int sequence_iterator = 0;
volatile int delay = 100;
int chosen_wave = 0;
int octave = 4;
int next_octave;
char active_note[3];
char note[2];
char octave_str[1];
char next_octave_str[1];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	if(htim->Instance == TIM4){
//		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
//		setNote(sequence[sequence_iterator], &htim7);
//		sequence_iterator++;
//		if(sequence_iterator == 8) sequence_iterator = 0;
	}
}

uint32_t sine_val[SAMPLING_RATE];
uint32_t saw_val[SAMPLING_RATE];
uint32_t quad_val[SAMPLING_RATE];

float map(float v, float is, float ie, float os, float oe){
	return os + (oe - os) * ((v - is)/(ie - is));
}

void get_sineval(){
	for(int i = 0; i < SAMPLING_RATE; i++){
		sine_val[i] = ((sin(i*2*PI/SAMPLING_RATE) + 1)*(4096/2));
	}
}

void get_sawval(){
	for(int i = 0; i < SAMPLING_RATE; i++){
		saw_val[i] = map(i, 0, 100, 0, 2)*(4096/2);
	}
}

void get_quadval(){
	for(int i = 0; i < 50; i++){
		quad_val[i] = 4095;
	}
	for(int i = 50; i < 100; i++){
		quad_val[i] = 0;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	next_octave = octave + 1;
	sprintf(octave_str, "%d", octave);
	sprintf(next_octave_str, "%d", next_octave);
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
  MX_DAC_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Base_Start_IT(&htim4);
  get_sineval();
  get_sawval();
  get_quadval();
  HAL_DAC_Start_DMA(&hdac, DAC1_CHANNEL_1, saw_val, SAMPLING_RATE, DAC_ALIGN_12B_R);
  HAL_DAC_Start_DMA(&hdac, DAC1_CHANNEL_2, quad_val, SAMPLING_RATE, DAC_ALIGN_12B_R);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_11))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "C");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_12))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "CS");
			strcat(active_note, octave_str);
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "D");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "DS");
			strcat(active_note, octave_str);
			setNote(active_note, &htim6);
		}
	  }
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "E");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "F");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "FS");
			strcat(active_note, octave_str);
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "G");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "GS");
			strcat(active_note, octave_str);
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "A");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "AS");
			strcat(active_note, octave_str);
		  	setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			strcpy(active_note, "");
			strcat(active_note, "B");
			strcat(active_note, octave_str);
			strcat(active_note, " ");
			setNote(active_note, &htim6);
		}
	  }
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))){
			strcpy(active_note, "");
			strcat(active_note, "C");
			strcat(active_note, next_octave_str);
			strcat(active_note, " ");
		  	setNote(active_note, &htim6);
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
			if(chosen_wave == 0){
				HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sine_val, SAMPLING_RATE, DAC_ALIGN_12B_R);
				chosen_wave += 1;
			}else if(chosen_wave == 1){
				HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, saw_val, SAMPLING_RATE, DAC_ALIGN_12B_R);
				chosen_wave += 1;
			}else if(chosen_wave == 2){
				HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
				HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, quad_val, SAMPLING_RATE, DAC_ALIGN_12B_R);
				chosen_wave = 0;
			}
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
		HAL_Delay(delay);
		if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13))){
			if(octave > 2){
				octave -= 1;
				next_octave = octave + 1;
				sprintf(octave_str, "%d", octave);
				sprintf(next_octave_str, "%d", next_octave);
				if(active_note[1] == 'S'){
					active_note[2] = octave_str;
				}else{
					if(active_note[0] == 'C'){
						if(active_note[1] != next_octave_str){
							active_note[1] = next_octave_str;
						}else{
							active_note[1] = octave_str;
						}
					}else{
						active_note[1] = octave_str;
					}
				}
				setNote(active_note, &htim6);
			}
		}
	  }

	  if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
		HAL_Delay(delay);
	  	if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14))){
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
			if(octave < 6){
				octave += 1;
				next_octave = octave + 1;
				sprintf(octave_str, "%d", octave);
				sprintf(next_octave_str, "%d", next_octave);
				if(active_note[1] == 'S'){
					active_note[2] = octave_str;
				}else{
					if(active_note[0] == 'C'){
						if(active_note[1] != next_octave_str){
							active_note[1] = next_octave_str;
						}else{
							active_note[1] = octave_str;
						}
					}else{
						active_note[1] = octave_str;
					}
				}
				setNote(active_note, &htim6);
			}
	  	}
	  }
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
  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /** DAC Initialization 
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config 
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT2 config 
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T7_TRGO;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 6999;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 11999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 0;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 0;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PE7 PE8 PE9 PE10 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB12 PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
