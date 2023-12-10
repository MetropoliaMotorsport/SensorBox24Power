/*
 * commands.c
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#include "main.h"
#include "functions.h"



void decode_uart(){
	if(strcmp(uart_rx_buffer,"PWM READ") == 0){
		PWM();
	}else if(strcmp(uart_rx_buffer,"OUT READ") == 0){
		OUT_READ();
	}else if(uart_rx_buffer,"PWM SET"){
		PWM_set();
	}else{
		print_out(-1, "!!WRONG COMMAND!!", data_output_switch);
	}

	command_received_flag = 0;
}

void PWM(){
	print_out(PWM_width[0], "PWM_1 PULSE WIDTH",data_output_switch);
	print_out(PWM_speed[0], "PWM_1 frequency",data_output_switch);
	print_out(PWM_width[1], "PWM_2 PULSE WIDTH",data_output_switch);
	print_out(PWM_speed[1], "PWM_2 frequency",data_output_switch);
}

void OUT_READ(){
	uint8_t status_bit;
	char msg[8];
	for(int i = 0; i < 8; i++){
		status_bit = check_bit(Default_Switch_State, i);
		sprintf(msg,"OUTPUT %d", i+1);
		print_out(status_bit,msg, data_output_switch);
	}
}

//TODO implement separating numbers from command
void PWM_set(uint8_t value){
	set_pwm(&htim3, value);
}



