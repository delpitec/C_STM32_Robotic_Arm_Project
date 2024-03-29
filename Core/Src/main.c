/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "RobotFunctions.h"
#include "PID.h"

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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	// Registers declarations and/or initializations
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM1->CCR4 = 0;


	// H bridge config initialization
	BTS2960 hBridge1, hBridge2, hBridge3, hBridge4;

	// PA8 (CCR1) = M2
	InitBTS2960(&hBridge2, &TIM1->CCR1, OUT_AXIS_2_L_GPIO_Port, OUT_AXIS_2_L_Pin,
				OUT_AXIS_2_R_GPIO_Port, OUT_AXIS_2_R_Pin);

	// PA9 (CCR2) = M1
	InitBTS2960(&hBridge1, &TIM1->CCR2, OUT_AXIS_1_L_GPIO_Port, OUT_AXIS_1_L_Pin,
				OUT_AXIS_1_R_GPIO_Port, OUT_AXIS_1_R_Pin);

	// PA10 (CCR3) = M3
	InitBTS2960(&hBridge3, &TIM1->CCR3, OUT_AXIS_3_L_GPIO_Port, OUT_AXIS_3_L_Pin,
				OUT_AXIS_3_R_GPIO_Port, OUT_AXIS_3_R_Pin);

	// PA11 (CCR4) = M4
	InitBTS2960(&hBridge4, &TIM1->CCR4, OUT_AXIS_4_L_GPIO_Port, OUT_AXIS_4_L_Pin,
				OUT_AXIS_4_R_GPIO_Port, OUT_AXIS_4_R_Pin);

	Axis Axis1 = {.shield = hBridge1,
				  .HomePort = IN_AXIS_1_HOME_GPIO_Port,
				  .HomePin = IN_AXIS_1_HOME_Pin,
				  .pidPos   =  {.kp = 1.0, // 0.70
				  		       .ki = 0.00,  // 0.65
				  		       .kd = 0.00,  // 0.30
				  	           .minNormilized = 0,
				  		       .maxNormilized = 1000,
				  		       .minProcessVariable = 0,
				  	           .maxProcessVariable = 60000,
				  		       .minControl = -1000,
				  		       .maxControl = 1000,
							   .error = 0,
				  		       .P_error = 0,
				  		       .I_error = 0,
				  		       .D_error = 0,
				  		       .lastSensedOutput = 0,
				  		       .timeStamp = 0},
				  .pidSpeed = {.kp = 0.7,
				    		   .ki = 0.7,
							   .kd = 0.00,
							   .minNormilized = 0,
							   .maxNormilized = 1000,
							   .minProcessVariable = -32000,
							   .maxProcessVariable = 32000,
							   .minControl = -1000,
							   .maxControl = 1000,
							   .error = 0,
							   .P_error = 0,
							   .I_error = 0,
							   .D_error = 0,
							   .lastSensedOutput = 0,
							   .timeStamp = 0},
				  .speed = &enc_1_speed,
				  .position = &enc_1,
				  .firstMove = COUNTERCLOCKWISE,
				  .minSpeed = 60};


	Axis Axis2 = {.shield = hBridge2,
			  	  .HomePort = IN_AXIS_2_HOME_GPIO_Port,
				  .HomePin = IN_AXIS_2_HOME_Pin,
				  .pidPos  =  {.kp = 0.80, // 5 (1) |
				  			   .ki = 0.00,
				  			   .kd = 0.00,
				  			   .minNormilized = 0,
				  			   .maxNormilized = 1000,
				  			   .minProcessVariable = 0,
				  			   .maxProcessVariable = 50000,
				  			   .minControl = -1000,
				  			   .maxControl = 1000,
				  			   .error = 0,
				  			   .P_error = 0,
				  			   .I_error = 0,
				  			   .D_error = 0,
				  			   .lastSensedOutput = 0,
				  			   .timeStamp = 0},
				  .pidSpeed = {.kp = 1.5, //
				  			   .ki = 0.60, // 0.625
				  			   .kd = 0.00,
				  			   .minNormilized = 0,
				  			   .maxNormilized = 1000,
				  			   .minProcessVariable = -32000,
				  			   .maxProcessVariable = 32000,
				  			   .minControl = -1000,
				  			   .maxControl = 1000,
				  			   .error = 0,
				  			   .P_error = 0,
				  			   .I_error = 0,
				  			   .D_error = 0,
				  			   .lastSensedOutput = 0,
				  			   .timeStamp = 0},
				  .speed = &enc_2_speed,
				  .position = &enc_2,
				  .firstMove = CLOCKWISE,
				  .minSpeed = 60};

	Axis Axis3 = {.shield = hBridge3,
			  	  .HomePort = IN_AXIS_3_HOME_GPIO_Port,
				  .HomePin = IN_AXIS_3_HOME_Pin,
				  .pidPos  =  {.kp = 0.25, // 0.70
  				  			   .ki = 0.00,  // 0.65
  				  			   .kd = 0.00,  // 0.30
  				  			   .minNormilized = 0,
  				  			   .maxNormilized = 1000,
  				  			   .minProcessVariable = 0,
  				  			   .maxProcessVariable = 20000,
  				  			   .minControl = -1000,
  				  			   .maxControl = 1000,
  				  			   .error = 0,
  				  			   .P_error = 0,
  				  			   .I_error = 0,
  				  			   .D_error = 0,
  				  			   .lastSensedOutput = 0,
  				  			   .timeStamp = 0},
				  .pidSpeed = {.kp = 2.8,
				  			   .ki = 0.45,
				  			   .kd = 0.0,
				  			   .minNormilized = 0,
				  			   .maxNormilized = 1000,
				  			   .minProcessVariable = -49000,
				  			   .maxProcessVariable = 49000,
				  			   .minControl = -1000,
				  			   .maxControl = 1000,
				  			   .error = 0,
				  			   .P_error = 0,
				  			   .I_error = 0,
				  			   .D_error = 0,
				  			   .lastSensedOutput = 0,
				  			   .timeStamp = 0},
				  .speed = &enc_3_speed,
				  .position = &enc_3,
				  .firstMove = CLOCKWISE,
				  .minSpeed = 70};

	Axis Axis4 = {.shield = hBridge4,
			      .HomePort = IN_AXIS_4_HOME_GPIO_Port,
				  .HomePin = IN_AXIS_4_HOME_Pin,
				  .pidPos  =  {.kp = 1.0,
  				  			   .ki = 0.00,
  				  			   .kd = 0.00,
  				  			   .minNormilized = 0,
  				  			   .maxNormilized = 1000,
  				  			   .minProcessVariable = 0,
  				  			   .maxProcessVariable = 10000,
  				  			   .minControl = -1000,
  				  			   .maxControl = 1000,
  				  			   .error = 0,
  				  			   .P_error = 0,
  				  			   .I_error = 0,
  				  			   .D_error = 0,
  				  			   .lastSensedOutput = 0,
  				  			   .timeStamp = 0},
				  .pidSpeed = {.kp = 0.75,
				  			   .ki = 0.625,
				  			   .kd = 0.00,
				  			   .minNormilized = 0,
				  			   .maxNormilized = 1000,
				  			   .minProcessVariable = -32000,
				  			   .maxProcessVariable = 32000,
				  			   .minControl = -1000,
				  			   .maxControl = 1000,
				  			   .error = 0,
				  			   .P_error = 0,
				  			   .I_error = 0,
				  			   .D_error = 0,
				  			   .lastSensedOutput = 0,
				  			   .timeStamp = 0},
				  .speed = &enc_4_speed,
				  .position = &enc_4,
				  .firstMove = COUNTERCLOCKWISE,
				  .minSpeed = 65};

	FindHomePosition(Axis3);
	FindHomePosition(Axis2);
	FindHomePosition(Axis1);
	FindHomePosition(Axis4);

	HAL_GPIO_TogglePin(OUT_VALVE_GPIO_Port, OUT_VALVE_Pin);

	//Axis1: Max: 60000 | Axis2: Max: 50000 | Axis 3: Max: 20000 | Axis4: 10000
	SetPoint RobotSetPoint = {30000, 50000, 6000, 10000};





	//SetOutputBTS2960(Axis4.shield, 70, COUNTERCLOCKWISE);

int state = 1;


	while (1) {
		//HAL_GPIO_TogglePin(OUT_VALVE_GPIO_Port, OUT_VALVE_Pin);

		PrintPosition();

		if (state == 1){
			MoveToPositionPID(&Axis1, 12896);
			if (ErrorIsZero(&Axis1, 50)){
				state = 2;
			}
		}
		if (state == 2){
			MoveToPositionPID(&Axis2, 9684);
			if (ErrorIsZero(&Axis2, 50)){
				state = 3;
			}
		}
		if (state == 3){
			MoveToPositionPID(&Axis3, 5000);
			if (ErrorIsZero(&Axis3, 1000)){
				state = 4;
			}
		}

		if (state == 4){
			MoveToPositionPID(&Axis4, 1500);
			if (ErrorIsZero(&Axis4, 15)){
				state = 6;
				HAL_GPIO_TogglePin(OUT_VALVE_GPIO_Port, OUT_VALVE_Pin);
				HAL_Delay(1000);
			}
		}
		if (state == 5){
			MoveToPositionPID(&Axis3, 500);
				if (ErrorIsZero(&Axis3, 50)){
					state = 6;
				}
		}
		if (state == 6){
					MoveToPositionPID(&Axis1, 44045);
					if (ErrorIsZero(&Axis1, 50)){
						state = 7;
					}
				}

		if (state == 7){
					MoveToPositionPID(&Axis3, 18000);
					if (ErrorIsZero(&Axis3, 2500)){
						state = 8;
					}
				}
		if (state == 8){
			HAL_GPIO_TogglePin(OUT_VALVE_GPIO_Port, OUT_VALVE_Pin);
			state = 9;
		}



		//MoveToPosition(Axis4, 20000);




	//SetOutputBTS2960(Axis4.shield, 80,COUNTERCLOCKWISE);


		//HAL_GPIO_TogglePin(OUT_LED_GPIO_Port, OUT_LED_Pin);



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

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 100-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 36000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 50-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OUT_LED_GPIO_Port, OUT_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, OUT_VALVE_Pin|OUT_AXIS_1_R_Pin|OUT_AXIS_1_L_Pin|OUT_AXIS_2_L_Pin
                          |OUT_AXIS_2_R_Pin|OUT_AXIS_4_R_Pin|OUT_AXIS_4_L_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, OUT_AXIS_3_R_Pin|OUT_AXIS_3_L_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OUT_LED_Pin */
  GPIO_InitStruct.Pin = OUT_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OUT_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : IN_INT_ENC_4_Pin IN_INT_ENC_3_Pin */
  GPIO_InitStruct.Pin = IN_INT_ENC_4_Pin|IN_INT_ENC_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : IN_DIR_ENC_2_Pin IN_DIR_ENC_1_Pin IN_DIR_ENC_3_Pin IN_DIR_ENC_4_Pin */
  GPIO_InitStruct.Pin = IN_DIR_ENC_2_Pin|IN_DIR_ENC_1_Pin|IN_DIR_ENC_3_Pin|IN_DIR_ENC_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : IN_INT_ENC_2_Pin IN_INT_ENC_1_Pin */
  GPIO_InitStruct.Pin = IN_INT_ENC_2_Pin|IN_INT_ENC_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : IN_AXIS_1_HOME_Pin IN_AXIS_2_HOME_Pin IN_AXIS_4_HOME_Pin IN_AXIS_3_HOME_Pin */
  GPIO_InitStruct.Pin = IN_AXIS_1_HOME_Pin|IN_AXIS_2_HOME_Pin|IN_AXIS_4_HOME_Pin|IN_AXIS_3_HOME_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : OUT_VALVE_Pin */
  GPIO_InitStruct.Pin = OUT_VALVE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OUT_VALVE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OUT_AXIS_1_R_Pin OUT_AXIS_1_L_Pin OUT_AXIS_2_L_Pin OUT_AXIS_2_R_Pin
                           OUT_AXIS_4_R_Pin OUT_AXIS_4_L_Pin */
  GPIO_InitStruct.Pin = OUT_AXIS_1_R_Pin|OUT_AXIS_1_L_Pin|OUT_AXIS_2_L_Pin|OUT_AXIS_2_R_Pin
                          |OUT_AXIS_4_R_Pin|OUT_AXIS_4_L_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : OUT_AXIS_3_R_Pin OUT_AXIS_3_L_Pin */
  GPIO_InitStruct.Pin = OUT_AXIS_3_R_Pin|OUT_AXIS_3_L_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

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
	while (1) {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
