/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define STEP_Pin GPIO_PIN_2
#define STEP_GPIO_Port GPIOA
#define DIR_Pin GPIO_PIN_1
#define DIR_GPIO_Port GPIOB
#define KEY_R4_Pin GPIO_PIN_12
#define KEY_R4_GPIO_Port GPIOB
#define KEY_R3_Pin GPIO_PIN_13
#define KEY_R3_GPIO_Port GPIOB
#define KEY_R2_Pin GPIO_PIN_14
#define KEY_R2_GPIO_Port GPIOB
#define KEY_R1_Pin GPIO_PIN_15
#define KEY_R1_GPIO_Port GPIOB
#define MS1_Pin GPIO_PIN_4
#define MS1_GPIO_Port GPIOB
#define MS2_Pin GPIO_PIN_5
#define MS2_GPIO_Port GPIOB
#define MS3_Pin GPIO_PIN_6
#define MS3_GPIO_Port GPIOB
#define KEY_C2_Pin GPIO_PIN_8
#define KEY_C2_GPIO_Port GPIOB
#define KEY_C1_Pin GPIO_PIN_9
#define KEY_C1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
