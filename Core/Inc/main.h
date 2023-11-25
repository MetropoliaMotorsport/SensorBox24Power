/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define IN1_2_Pin GPIO_PIN_10
#define IN1_2_GPIO_Port GPIOG
#define IN0_2_Pin GPIO_PIN_4
#define IN0_2_GPIO_Port GPIOA
#define SEL1_READ_Pin GPIO_PIN_5
#define SEL1_READ_GPIO_Port GPIOA
#define SEL0_READ_Pin GPIO_PIN_0
#define SEL0_READ_GPIO_Port GPIOB
#define IN3_Pin GPIO_PIN_9
#define IN3_GPIO_Port GPIOA
#define IN2_Pin GPIO_PIN_10
#define IN2_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_15
#define IN1_GPIO_Port GPIOA
#define IN0_Pin GPIO_PIN_3
#define IN0_GPIO_Port GPIOB
#define IN3_2_Pin GPIO_PIN_4
#define IN3_2_GPIO_Port GPIOB
#define SEL1_Pin GPIO_PIN_5
#define SEL1_GPIO_Port GPIOB
#define SEL0_Pin GPIO_PIN_6
#define SEL0_GPIO_Port GPIOB
#define IN2_2_Pin GPIO_PIN_8
#define IN2_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern uint8_t Default_Switch_State;
extern uint8_t PWM_out_enable;
extern uint16_t PWM_Prescalers[8];
extern uint16_t WC_1_1; //current warning 1_1
extern uint16_t OC_1_1; //over current 1_1
extern uint16_t UC_1_1; //under current 1_1
extern uint16_t WC_2_1; //current warning 2_1
extern uint16_t OC_2_1; //over current 2_1
extern uint16_t UC_2_1; //under current 2_1
extern uint16_t WC_3_1; //current warning 3_1
extern uint16_t OC_3_1; //over current 3_1
extern uint16_t UC_3_1; //under current 3_1
extern uint16_t WC_4_1; //current warning 4_1
extern uint16_t OC_4_1; //over current 4_1
extern uint16_t UC_4_1; //under current 4_1
extern uint16_t WC_1_2; //current warning 1_2
extern uint16_t OC_1_2; //over current 1_2
extern uint16_t UC_1_2; //under current 1_2
extern uint16_t WC_2_2; //current warning 2_2
extern uint16_t OC_2_2; //over current 2_2
extern uint16_t UC_2_2; //under current 2_2
extern uint16_t WC_3_2; //current warning 3_2
extern uint16_t OC_3_2; //over current 3_2
extern uint16_t UC_3_2; //under current 3_2
extern uint16_t WC_4_2; //current warning 4_2
extern uint16_t OC_4_2; //over current 4_2
extern uint16_t UC_4_2; //under current 4_2
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
