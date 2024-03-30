/*
 * commands.c
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#include "main.h"
#include "functions.h"
#include "string.h"



/*void decode_uart(){
	uint8_t str1[7];
	uint8_t str2[5];
	uint8_t str3[3];
	str1[6] = 0;
	str2[4] = 0;
	str3[2] = 0;
	uint8_t number;
	uint8_t string_counter = 0;
	uint8_t string_determine = 1;
	for(int i = 0; i <30; i++){
		if(string_determine == 1){
			if(uart_rx_buffer[i] != 32){
				if(uart_rx_buffer[i] != 0){
					str1[string_counter] = uart_rx_buffer[i];
					string_counter++;
				}
			}else{
				string_determine++;
				string_counter = 0;
			}
		}else if(string_determine == 2){
			if(uart_rx_buffer[i] != 32){
				if(uart_rx_buffer[i] != 0){
					str2[string_counter] = uart_rx_buffer[i];
					string_counter++;
				}
			}else{
				string_determine++;
				string_counter = 0;
			}
		}else{
			if(uart_rx_buffer[i] != 32){
				if(uart_rx_buffer[i] != 0){
					str3[string_counter] = uart_rx_buffer[i];
					string_counter++;
				}
			}else{
				string_determine = 1;
				string_counter = 0;
			}
		}
		uart_rx_buffer[i] = 0;
	}

	number = atoi(str3);

	if(strcmp(str1,"PWM") == 0){
		if(strcmp(str2,"READ") == 0){
			PWM();
		}else if(strcmp(str2,"SET") == 0){
			PWM_set(number);
		}else{
			print_out("\r\nERR", data_output_switch);
		}
	}else if(strcmp(str1, "OUTPUT") == 0){
		if(strcmp(str2,"READ") == 0){
			OUT_READ(number);
		}else if(strcmp(str2,"SET/0") == 0){
			//TODO bit set
		}else{
			print_out("\r\nERR", data_output_switch);
		}
	}else{
		print_out("ERR", data_output_switch);
	}

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
}*/


void PWM(){
	char msg1[20];
	char msg2[20];
	char msg3[20];
	char msg4[20];
	sprintf(msg1,"PWM_1 PULSE WIDTH %d",PWM_width[0]);
	sprintf(msg2,"PWM_1 frequency %d",PWM_width[0]);
	sprintf(msg3,"PWM_2 PULSE WIDTH %d",PWM_width[0]);
	sprintf(msg4,"PWM_2 frequency %d",PWM_width[0]);
	print_out(msg1,data_output_switch);
	print_out(msg2,data_output_switch);
	print_out(msg3,data_output_switch);
	print_out(msg4,data_output_switch);
}

void OUT_READ(uint8_t value){
	uint8_t status_bit;
	char msg[8];
		status_bit = check_bit(Default_Switch_State, value+1);
		sprintf(msg,"OUTPUT %d %d", value+1, status_bit);
		print_out(msg, data_output_switch);
}

//TODO implement separating numbers from command
void PWM_set(uint8_t value){
	//set_pwm(htim1, value);
}




