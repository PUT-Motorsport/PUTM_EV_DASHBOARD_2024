/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

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
#define TSA_BTN_Pin GPIO_PIN_15
#define TSA_BTN_GPIO_Port GPIOA
#define LCD_DISP_RESET_Pin GPIO_PIN_7
#define LCD_DISP_RESET_GPIO_Port GPIOH
#define FUSE_LED_Pin GPIO_PIN_5
#define FUSE_LED_GPIO_Port GPIOH
#define CTP_RST_Pin GPIO_PIN_3
#define CTP_RST_GPIO_Port GPIOE
#define SAFETY_LED_Pin GPIO_PIN_4
#define SAFETY_LED_GPIO_Port GPIOH
#define INTERNAL_BTN_Pin GPIO_PIN_3
#define INTERNAL_BTN_GPIO_Port GPIOJ
#define INTERNAL_LED_Pin GPIO_PIN_5
#define INTERNAL_LED_GPIO_Port GPIOE
#define CTP_INT_Pin GPIO_PIN_6
#define CTP_INT_GPIO_Port GPIOE
#define CTP_INT_EXTI_IRQn EXTI6_IRQn
#define USB_PWR_EN_Pin GPIO_PIN_8
#define USB_PWR_EN_GPIO_Port GPIOG
#define USB_OVERCURRENT_Pin GPIO_PIN_0
#define USB_OVERCURRENT_GPIO_Port GPIOJ
#define RTD_BTN_Pin GPIO_PIN_4
#define RTD_BTN_GPIO_Port GPIOI
#define R_RST_Pin GPIO_PIN_4
#define R_RST_GPIO_Port GPIOF
#define USR_BTN_Pin GPIO_PIN_0
#define USR_BTN_GPIO_Port GPIOB
#define R_CS_Pin GPIO_PIN_1
#define R_CS_GPIO_Port GPIOG
#define R_INT_Pin GPIO_PIN_4
#define R_INT_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
