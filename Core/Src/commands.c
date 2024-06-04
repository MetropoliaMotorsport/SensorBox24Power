/*
 * commands.c
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#include "main.h"
#include "functions.h"
#include "string.h"


void set_pwm_duty_cycle(TIM_HandleTypeDef *htim){
	if(check_bit(PWM_out_enable,1) != 0){
		PWM_speed[0] = (PWM_width[0] * 40)/100;
	}else{
		PWM_speed[0] = 0;
	}
	if(check_bit(PWM_out_enable,0) != 0){
		PWM_speed[1] = (PWM_width[1] * 40)/100;
	}else{
		PWM_speed[1] = 0;
	}
	 //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,PWM_speed[0]);

	 //__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,PWM_speed[1]);

	/*if(htim->Instance == TIM1){
	  TIM_OC_InitTypeDef sConfigOC;

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = PWM_width[0];
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
	}
	if(htim->Instance == TIM2){
	  TIM_OC_InitTypeDef sConfigOC;

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = PWM_width[1];
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
	}*/
}

void set_pwm_freq(TIM_HandleTypeDef *htim){
	/*if(htim->Instance == TIM1){
		 if (HAL_TIM_Base_DeInit(htim) != HAL_OK)
		  {
		    Error_Handler();
		  }
		 htim1.Init.Prescaler = PWM_Prescalers[0];
		 if (HAL_TIM_Base_Init(htim) != HAL_OK)
		  {
		    Error_Handler();
		  }
	}
	if(htim->Instance == TIM2){
		 if (HAL_TIM_Base_DeInit(htim) != HAL_OK)
		  {
		    Error_Handler();
		  }
		 htim1.Init.Prescaler = PWM_Prescalers[1];
		 if (HAL_TIM_Base_Init(htim) != HAL_OK)
		  {
		    Error_Handler();
		  }
	}*/
}




