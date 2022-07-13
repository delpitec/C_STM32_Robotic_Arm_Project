/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bts7960.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern UART_HandleTypeDef huart1;
extern unsigned int count_1;
extern unsigned int count_2;
extern unsigned int count_3;
extern unsigned int count_4;

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OUT_LED_Pin GPIO_PIN_13
#define OUT_LED_GPIO_Port GPIOC
#define IN_INT_ENC_4_Pin GPIO_PIN_0
#define IN_INT_ENC_4_GPIO_Port GPIOA
#define IN_INT_ENC_4_EXTI_IRQn EXTI0_IRQn
#define IN_INT_ENC_3_Pin GPIO_PIN_1
#define IN_INT_ENC_3_GPIO_Port GPIOA
#define IN_INT_ENC_3_EXTI_IRQn EXTI1_IRQn
#define IN_DIR_ENC_2_Pin GPIO_PIN_2
#define IN_DIR_ENC_2_GPIO_Port GPIOA
#define IN_INT_ENC_2_Pin GPIO_PIN_3
#define IN_INT_ENC_2_GPIO_Port GPIOA
#define IN_INT_ENC_2_EXTI_IRQn EXTI3_IRQn
#define IN_INT_ENC_1_Pin GPIO_PIN_4
#define IN_INT_ENC_1_GPIO_Port GPIOA
#define IN_INT_ENC_1_EXTI_IRQn EXTI4_IRQn
#define IN_DIR_ENC_1_Pin GPIO_PIN_5
#define IN_DIR_ENC_1_GPIO_Port GPIOA
#define IN_DIR_ENC_3_Pin GPIO_PIN_6
#define IN_DIR_ENC_3_GPIO_Port GPIOA
#define IN_DIR_ENC_4_Pin GPIO_PIN_7
#define IN_DIR_ENC_4_GPIO_Port GPIOA
#define IN_AXIS_1_HOME_Pin GPIO_PIN_0
#define IN_AXIS_1_HOME_GPIO_Port GPIOB
#define IN_AXIS_2_HOME_Pin GPIO_PIN_1
#define IN_AXIS_2_HOME_GPIO_Port GPIOB
#define IN_AXIS_4_HOME_Pin GPIO_PIN_10
#define IN_AXIS_4_HOME_GPIO_Port GPIOB
#define OUT_AXIS_1_R_Pin GPIO_PIN_12
#define OUT_AXIS_1_R_GPIO_Port GPIOB
#define OUT_AXIS_1_L_Pin GPIO_PIN_13
#define OUT_AXIS_1_L_GPIO_Port GPIOB
#define OUT_AXIS_2_L_Pin GPIO_PIN_14
#define OUT_AXIS_2_L_GPIO_Port GPIOB
#define OUT_AXIS_2_R_Pin GPIO_PIN_15
#define OUT_AXIS_2_R_GPIO_Port GPIOB
#define OUT_AXIS_2_PWM_Pin GPIO_PIN_8
#define OUT_AXIS_2_PWM_GPIO_Port GPIOA
#define OUT_AXIS_3_R_Pin GPIO_PIN_12
#define OUT_AXIS_3_R_GPIO_Port GPIOA
#define OUT_AXIS_3_L_Pin GPIO_PIN_15
#define OUT_AXIS_3_L_GPIO_Port GPIOA
#define OUT_AXIS_4_R_Pin GPIO_PIN_3
#define OUT_AXIS_4_R_GPIO_Port GPIOB
#define OUT_AXIS_4_L_Pin GPIO_PIN_4
#define OUT_AXIS_4_L_GPIO_Port GPIOB
#define IN_AXIS_3_HOME_Pin GPIO_PIN_5
#define IN_AXIS_3_HOME_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
