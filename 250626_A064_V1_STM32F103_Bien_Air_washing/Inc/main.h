/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define POT_MID_Pin GPIO_PIN_0
#define POT_MID_GPIO_Port GPIOC
#define Coag_init_Pin GPIO_PIN_0
#define Coag_init_GPIO_Port GPIOA
#define POWER_CTRL_5V_Pin GPIO_PIN_4
#define POWER_CTRL_5V_GPIO_Port GPIOA
#define POWER_CTRL_24V_Pin GPIO_PIN_1
#define POWER_CTRL_24V_GPIO_Port GPIOB
#define CHAIR_DOWN_Pin GPIO_PIN_6
#define CHAIR_DOWN_GPIO_Port GPIOC
#define CHAIR_UP_Pin GPIO_PIN_7
#define CHAIR_UP_GPIO_Port GPIOC
#define BACKREST_UP_Pin GPIO_PIN_8
#define BACKREST_UP_GPIO_Port GPIOC
#define BACKREST_DOWN_Pin GPIO_PIN_9
#define BACKREST_DOWN_GPIO_Port GPIOC
#define SPITTOON_Pin GPIO_PIN_8
#define SPITTOON_GPIO_Port GPIOA
#define A_Pin GPIO_PIN_9
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_10
#define B_GPIO_Port GPIOA
#define COAG_Pin GPIO_PIN_15
#define COAG_GPIO_Port GPIOA
#define LIGHT_ON_Pin GPIO_PIN_10
#define LIGHT_ON_GPIO_Port GPIOC
#define WATER_S_Pin GPIO_PIN_11
#define WATER_S_GPIO_Port GPIOC
#define WATER_F_Pin GPIO_PIN_12
#define WATER_F_GPIO_Port GPIOC
#define Pedal_ON_OFF_Pin GPIO_PIN_2
#define Pedal_ON_OFF_GPIO_Port GPIOD
#define CHIP_Pin GPIO_PIN_3
#define CHIP_GPIO_Port GPIOB
#define SPRAY_Pin GPIO_PIN_4
#define SPRAY_GPIO_Port GPIOB
#define Open_Collector_1_Pin GPIO_PIN_5
#define Open_Collector_1_GPIO_Port GPIOB
#define Open_Collector_2_Pin GPIO_PIN_6
#define Open_Collector_2_GPIO_Port GPIOB
#define Code_LED_Pin GPIO_PIN_7
#define Code_LED_GPIO_Port GPIOB
#define Status_LED_Pin GPIO_PIN_8
#define Status_LED_GPIO_Port GPIOB
#define Error_LED_Pin GPIO_PIN_9
#define Error_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
