/*
 * functions.c
 *
 *  Created on: Nov 26, 2023
 *      Author: marcelc
 */
#include "main.h"
#include "stm32g4xx_hal.h"
#include "stdio.h"


void CS_process(){
	//4031 == 3.3V since 12bit, got to pick shunt resistor according to this
	IN1_1_PROC = IN1_1_CS[0];
	IN2_1_PROC = IN2_1_CS[0];
	IN3_1_PROC = IN3_1_CS[0];
	IN4_1_PROC = IN4_1_CS[0];
	IN1_2_PROC = IN1_2_CS[0];
	IN2_2_PROC = IN2_2_CS[0];
	IN3_2_PROC = IN3_2_CS[0];
	IN4_2_PROC = IN4_2_CS[0];
	for(int i = 1; i < I_AVERAGE; i++){
		IN1_1_PROC = (IN1_1_PROC + IN1_1_CS[i])/2;
		IN2_1_PROC = (IN2_1_PROC + IN2_1_CS[i])/2;
		IN3_1_PROC = (IN3_1_PROC + IN3_1_CS[i])/2;
		IN4_1_PROC = (IN4_1_PROC + IN4_1_CS[i])/2;
		IN1_2_PROC = (IN1_2_PROC + IN1_2_CS[i])/2;
		IN2_2_PROC = (IN2_2_PROC + IN2_2_CS[i])/2;
		IN3_2_PROC = (IN3_2_PROC + IN3_2_CS[i])/2;
		IN4_2_PROC = (IN4_2_PROC + IN4_2_CS[i])/2;
	}

}

void check_warnings(){
	if(IN1_1_PROC >= WC_1_1){
		if(IN1_1_PROC >= OC_1_1){
			HAL_GPIO_WritePin(GPIOA,IN0_Pin,0);
			print_out("1_OC",data_output_switch);
		}else{
			print_out("1_WC",data_output_switch);
		}
	}
	if(IN1_1_PROC <= UC_1_1){
		print_out("1_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN2_1_PROC >= WC_2_1){
		if(IN2_1_PROC >= OC_2_1){
			HAL_GPIO_WritePin(GPIOA,IN1_Pin,0);
			print_out("2_OC",data_output_switch);
		}else{
			print_out("2_WC",data_output_switch);
		}
	}
	if(IN2_1_PROC <= UC_2_1){
		print_out("2_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN3_1_PROC >= WC_3_1){
		if(IN3_1_PROC >= OC_3_1){
			HAL_GPIO_WritePin(GPIOA,IN2_Pin,0);
			print_out("3_OC",data_output_switch);
		}else{
			print_out("3_WC",data_output_switch);
		}
	}
	if(IN3_1_PROC <= UC_3_1){
		print_out("3_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN4_1_PROC >= WC_4_1){
		if(IN4_1_PROC >= OC_4_1){
			HAL_GPIO_WritePin(GPIOA,IN3_Pin,0);
			print_out("4_OC",data_output_switch);
		}else{
			print_out("4_WC",data_output_switch);
		}
	}
	if(IN4_1_PROC <= UC_4_1){
		print_out("4_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN1_2_PROC >= WC_1_2){
		if(IN1_2_PROC >= OC_1_2){
			HAL_GPIO_WritePin(GPIOA,IN0_2_Pin,0);
			print_out("5_OC",data_output_switch);
		}else{
			print_out("5_WC",data_output_switch);
		}
	}
	if(IN1_2_PROC <= UC_1_2){
		print_out("5_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN2_2_PROC >= WC_2_2){
		if(IN2_2_PROC >= OC_2_2){
			HAL_GPIO_WritePin(GPIOA,IN1_2_Pin,0);
			print_out("6_OC",data_output_switch);
		}else{
			print_out("6_WC",data_output_switch);
		}
	}
	if(IN2_2_PROC <= UC_2_2){
		print_out("6_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN3_2_PROC >= WC_3_2){
		if(IN3_2_PROC >= OC_3_2){
			HAL_GPIO_WritePin(GPIOA,IN2_2_Pin,0);
			print_out("7_OC",data_output_switch);
		}else{
			print_out("7_WC",data_output_switch);
		}
	}
	if(IN3_2_PROC <= UC_3_2){
		print_out("7_UC",data_output_switch);
	}
//------------------------------------------------------
	if(IN4_2_PROC >= WC_4_2){
		if(IN4_2_PROC >= OC_4_2){
			HAL_GPIO_WritePin(GPIOA,IN3_2_Pin,0);
			print_out("8_OC",data_output_switch);
		}else{
			print_out("8_WC",data_output_switch);
		}
	}
	if(IN4_2_PROC <= UC_4_2){
		print_out("8_UC",data_output_switch);
	}
}

void CS_read(){
	for(int x = 0; x < 4; x++){
		switch(x){
		case 0:
			CS_SEL[0] = 0;
			CS_SEL[1] = 0;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,CS_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,CS_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start_IT(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,10)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,10)!=HAL_OK){Error_Handler();}
				IN1_1_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN1_2_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop_IT(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 1:
			CS_SEL[0] = 0;
			CS_SEL[1] = 1;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,CS_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,CS_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start_IT(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,10)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,10)!=HAL_OK){Error_Handler();}
				IN2_1_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN2_2_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop_IT(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 2:
			CS_SEL[0] = 1;
			CS_SEL[1] = 0;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,CS_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,CS_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start_IT(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,10)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,10)!=HAL_OK){Error_Handler();}
				IN3_1_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN3_2_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop_IT(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 3:
			CS_SEL[0] = 1;
			CS_SEL[1] = 1;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,CS_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,CS_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start_IT(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,10)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,10)!=HAL_OK){Error_Handler();}
				IN4_1_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN4_2_CS[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop_IT(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		}
//		This function is for checking how CS_SEL pins behave
//		During writing the code it behaved as expected
//------------------------------------------------------
/*		if(HAL_GPIO_ReadPin(SEL0_READ_GPIO_Port, SEL0_READ_Pin) == GPIO_PIN_RESET){
			print_out(0,"S0: ",data_output_switch);
		}else{
			print_out(1,"S0: ",data_output_switch);
		}
		if(HAL_GPIO_ReadPin(SEL1_READ_GPIO_Port, SEL1_READ_Pin) == GPIO_PIN_RESET){
			print_out(0,"S1: ",data_output_switch);
		}else{
			print_out(1,"S1: ",data_output_switch);
		}*/
//------------------------------------------------------
	}
	CS_process();
}

void print_out(const char *text, uint8_t out_mode){

	// uint16_t length = strlen(string);
	 //uint8_t CRLFbuff[] = "\r\n";
	char buffer[strlen(text)+1];
	strcpy(buffer, text);
	switch(out_mode){
		  case 1: //Ouput only through DEBUG
			  HAL_UART_Transmit_DMA(&huart2, buffer, sizeof(text));
			  text = "";
			  break;
		  case 2: //output only through CAN
			  //TODO implement CAN
			  break;
		  case 3://output through BOTH CAN and DEBUG
			  HAL_UART_Transmit_DMA(&huart2, buffer, sizeof(text));
			  text = "";
			  //TODO implement CAN
			  break;
		  }
}

void set_pwm(TIM_HandleTypeDef *htim, uint16_t value){
	  TIM_OC_InitTypeDef sConfigOC;

	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = value;
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(uart_receive == 13){
		const char *newline = "\r\n";
		HAL_UART_Transmit_DMA(huart, (uint8_t*)newline,2);
		uart_rx_buffer[29] = 0;
		command_received_flag = 1;
	}else{
		for(int i = 0; i < 28; i++){
			uart_rx_buffer[i] = uart_rx_buffer[i+1];
		}
		HAL_UART_Transmit_DMA(huart, &uart_receive,1);
		uart_rx_buffer[28] = uart_receive;
	}
	HAL_UART_Receive_DMA(huart, &uart_receive,1);
}

uint8_t check_bit(uint8_t byte, uint8_t bitn){
	uint8_t buffer = 1<<bitn;
	if (byte & buffer){
		return 1;
	}else{
		return 0;
	}
}


