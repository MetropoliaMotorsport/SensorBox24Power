/*
 * commands.c
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#include "main.h"
#include "functions.h"
#include "string.h"


void set_pwm_duty_cycle(TIM_HandleTypeDef *htim, uint16_t value){
	  TIM_OC_InitTypeDef sConfigOC;

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = value;
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
}

void set_pwm_freq(TIM_HandleTypeDef *htim, uint16_t value){

}




