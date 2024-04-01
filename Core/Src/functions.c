/*
 * functions.c
 *
 *  Created on: Nov 26, 2023
 *      Author: marcelc
 */
#include "main.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx.h"
#include "stdio.h"





extern uint8_t RxData[8];
uint8_t TxData[8];


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
    /* Reception Error */
    Error_Handler();
    }
  }else{
	decode();
  }

  if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
}

void CanSend(uint8_t *TxData){
	TxHeader.Identifier = CAN_ID;
	while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK){ Error_Handler(); }
}

void CAN_switch_state(){
	TxHeader.Identifier = CAN_ID;
	TxData[0] = 11;
	for(int i = 1; i < 5;i++){
		TxData[i] = check_bit(Default_Switch_State,i-1);
	}
	while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK){ Error_Handler(); }
	TxData[0] = 12;
	for(int i = 1; i < 5;i++){
		TxData[i] = check_bit(Default_Switch_State,i+3);
	}
	while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK){ Error_Handler(); }
}



void output(){
	uint8_t i = 0;
	uint8_t bit = 0;
	for(i = 0; i < 8;i++){
		bit = check_bit(Default_Switch_State, i);
		switch(i){
		case 0:
			HAL_GPIO_WritePin(GPIOA,IN0_Pin,bit);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA,IN1_Pin,bit);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA,IN2_Pin,bit);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA,IN3_Pin,bit);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOA,IN0_2_Pin,bit);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOA,IN1_2_Pin,bit);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOA,IN2_2_Pin,bit);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOA,IN3_2_Pin,bit);
			break;
		default:
			Error_Handler();
			break;
		}
	}
}

void Over_current(uint8_t output_pin){
	TxData[1] = 15;
	TxData[2] = output_pin;
	CanSend(TxData);
}

void Warning_current(uint8_t output_pin){
	TxData[1] = 14;
	TxData[2] = output_pin;
	CanSend(TxData);
}

void Under_current(uint8_t output_pin){
	TxData[1] = 13;
	TxData[2] = output_pin;
	CanSend(TxData);
}

void decode(){
	switch(RxData[0]){
	case 1:							//Set PWM RxData[1] -> which PWM, RxData[2] = 1 -> Duty Cycle || RxData[2] = 2 -> Frequency, RxData[3] -> value
		switch(RxData[1]){
		case 1:										//PUMPS
			switch(RxData[2]){
			case 1:
				set_pwm_duty_cycle(&htim1,RxData[3]);
				break;
			case 2:
				set_pwm_freq(&htim1, RxData[3]);
				break;
			default:
				//decode_error();
				Error_Handler();
				break;
			}
		case 2:										//FANS
			switch(RxData[2]){
			case 1:
				set_pwm_duty_cycle(&htim2,RxData[3]);
				break;
			case 2:
				set_pwm_freq(&htim2, RxData[3]);
				break;
			default:
				//decode_error();
				Error_Handler();
				break;
			}
		default:
			//decode_error(); //TODO: IMPLEMENT
			Error_Handler();
			break;
		}
	case 2:							//Switch output on/off
		Default_Switch_State = set_bit(Default_Switch_State,RxData[1],RxData[2]); //if RxData[2] is 0 -> OFF, if RxData[2] is 1 -> ON
		break;
	default:
		Error_Handler();
		break;
	}
}



void CS_process(){
	//4031 == 3.3V since 12bit, have to pick shunt resistor according to this
	PROC[0] = IN1_1_CS[0];
	PROC[1] = IN2_1_CS[0];
	PROC[2] = IN3_1_CS[0];
	PROC[3] = IN4_1_CS[0];
	PROC[4] = IN1_2_CS[0];
	PROC[5] = IN2_2_CS[0];
	PROC[6] = IN3_2_CS[0];
	PROC[7] = IN4_2_CS[0];
	for(int i = 1; i < I_AVERAGE; i++){
		PROC[0] = (PROC[0] + IN1_1_CS[i])/2;
		PROC[1] = (PROC[1] + IN2_1_CS[i])/2;
		PROC[2] = (PROC[2] + IN3_1_CS[i])/2;
		PROC[3] = (PROC[3] + IN4_1_CS[i])/2;
		PROC[4] = (PROC[4] + IN1_2_CS[i])/2;
		PROC[5] = (PROC[5] + IN2_2_CS[i])/2;
		PROC[6] = (PROC[6] + IN3_2_CS[i])/2;
		PROC[7] = (PROC[7] + IN4_2_CS[i])/2;
	}

}

void check_warnings(){
	for(uint8_t x = 0; x < 8; x++){
		if(PROC[x] >= WC[x]){
			if(PROC[x] >= OC[x]){
				Default_Switch_State = set_bit(Default_Switch_State, x, 0);
				Over_current(x);
			}else{
				Warning_current(x);
			}
		}
		if(PROC[x] <= UC[x]){
			Under_current(x);
		}
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


uint8_t check_bit(uint8_t byte, uint8_t bitn){
	uint8_t buffer = 1<<bitn;
	if (byte & buffer){
		return 1;
	}else{
		return 0;
	}
}

uint8_t set_bit(uint8_t byte, uint8_t pos, uint8_t new_bit){
	uint8_t mask = 1 << pos;
	if(new_bit == 1){
		byte |= mask;
	}else{
		byte &= ~mask;
	}
	return byte;
}


