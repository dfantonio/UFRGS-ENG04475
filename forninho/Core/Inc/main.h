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
#define botao_placa_Pin GPIO_PIN_13
#define botao_placa_GPIO_Port GPIOC
#define led_verde_Pin GPIO_PIN_5
#define led_verde_GPIO_Port GPIOA
#define led_forno_Pin GPIO_PIN_6
#define led_forno_GPIO_Port GPIOA
#define led_grill_Pin GPIO_PIN_7
#define led_grill_GPIO_Port GPIOA
#define botao_menu_funcao_Pin GPIO_PIN_12
#define botao_menu_funcao_GPIO_Port GPIOB
#define botao_menu_mais_Pin GPIO_PIN_13
#define botao_menu_mais_GPIO_Port GPIOB
#define botao_menu_menos_Pin GPIO_PIN_14
#define botao_menu_menos_GPIO_Port GPIOB
#define botao_menu_start_Pin GPIO_PIN_15
#define botao_menu_start_GPIO_Port GPIOB
#define display_EN_Pin GPIO_PIN_6
#define display_EN_GPIO_Port GPIOC
#define display_RS_Pin GPIO_PIN_7
#define display_RS_GPIO_Port GPIOC
#define display_D0_Pin GPIO_PIN_8
#define display_D0_GPIO_Port GPIOC
#define display_D1_Pin GPIO_PIN_9
#define display_D1_GPIO_Port GPIOC
#define display_D2_Pin GPIO_PIN_8
#define display_D2_GPIO_Port GPIOA
#define display_D3_Pin GPIO_PIN_9
#define display_D3_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
