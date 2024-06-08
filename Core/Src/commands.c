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
}






