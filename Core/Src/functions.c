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
#include "config.h"





uint8_t RxData[8];
uint8_t TxData[8];
uint8_t toggle = 0;


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		/* Retreive Rx messages from RX FIFO0 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxMessage.Bytes) != HAL_OK)
		{
			/* Reception Error */
			Error_Handler();
		}else{
			if(RxHeader.Identifier == CAN_ID){
				RxMessage.DLC = RxHeader.DataLength;
				decode();
			}
		}

		if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
		{
			/* Notification Error */
			Error_Handler();
		}
	}
}

void CanSend(uint8_t *TxData){
	while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK){
		Error_Handler();
		HAL_GPIO_WritePin(GPIOB,LED1_Pin,0);
	}
}

//function to send state of switches on CAN, for debugging!
void CAN_switch_state(uint8_t values){
	uint8_t TxData1[5];
	uint8_t TxData2[5];

	if(can_select == 0){
		TxData1[0] = 11;
		for(int i = 1; i < 5;i++){
			TxData1[i] = check_bit(Default_Switch_State,i-1);
		}
		CanSend(TxData1);
	}
	if(can_select == 1){
		TxData2[0] = 12;
		for(int i = 1; i < 5;i++){
			TxData2[i] = check_bit(Default_Switch_State,i+3);
		}
		CanSend(TxData2);
	}
}

void switch_on_off(GPIO_TypeDef *port, uint16_t pin, uint8_t state){
	HAL_GPIO_WritePin(port, pin, state);
}

void switch_output(){
	uint8_t i = 0;
	for(i = 0; i < 8;i++){
		outputs[i].state = check_bit(Default_Switch_State, i);
		switch_on_off(outputs[i].port, outputs[i].physical_pin, outputs[i].state);
	}
}

void Over_current(uint8_t output_pin){
	TxData[0] = 15;
	TxData[1] = output_pin;
	CanSend(TxData);
}

void Warning_current(uint8_t output_pin){
	TxData[0] = 14;
	TxData[1] = output_pin;
	CanSend(TxData);
}

void Under_current(uint8_t output_pin){
	TxData[0] = 13;
	TxData[1] = output_pin;
	CanSend(TxData);
}

void decode(){
	switch(RxMessage.Bytes[0]){
	case 1:							//Set PWM RxData[1] -> which PWM, RxData[2] = 1 -> Duty Cycle || RxData[2] = 2 -> Frequency, RxData[3] -> value
		switch(RxMessage.Bytes[1]){
		case 1:										//PUMPS
			PWM_width[0] = RxMessage.Bytes[2];
			set_pwm_duty_cycle(&htim1);
			break;
		case 2:										//FANS
			PWM_width[1] = RxMessage.Bytes[2];
			set_pwm_duty_cycle(&htim2);
			break;
		default:
			Error_Handler();
			break;
		}
		break;
	case 2:							//Switch output on/off
		Default_Switch_State = set_bit(Default_Switch_State,RxMessage.Bytes[1],RxMessage.Bytes[2]); //if RxData[2] is 0 -> OFF, if RxData[2] is 1 -> ON
		switch_output();
		break;
	case 3:							// turning analog node on and off, RxData[1] -> 0 is off 1 is on
		HAL_GPIO_WritePin(GPIOA,LED2_Pin,RxMessage.Bytes[1]);
		break;
	case 4:							//switch BRAKE_LIGHT	RxData[1] --> 0 for off and 1 for on
		for(int i = 0; i < 8; i++){
			if(outputs[i].device == BRAKE_LIGHT){
				Default_Switch_State = set_bit(Default_Switch_State,i,RxMessage.Bytes[1]);
				switch_output();
			}
		}
		break;
	case 5:							//switch BUZZER on off
		for(int i = 0; i < 8; i++){
			if(outputs[i].device == BUZZER){
				Default_Switch_State = set_bit(Default_Switch_State,i,RxMessage.Bytes[1]);
				switch_output();
			}
		}
		break;
	case 6:	//TSAL
		switch(RxMessage.Bytes[0]){
		case 0: 					//on off
			for(int i = 0; i < 8; i++){
				if(outputs[i].device == TSAL){
					Default_Switch_State = set_bit(Default_Switch_State,i,RxMessage.Bytes[1]);
					switch_output();
				}
			}
			break;
		case 1:						//TSAL COLOR
			switch(RxMessage.Bytes[1]){
				case 0:				//RED
					for(int i = 0; i < 8; i++){
						if(outputs[i].device == TSAL_RED){
							Default_Switch_State = set_bit(Default_Switch_State,i,RxMessage.Bytes[2]);
							switch_output();
						}
						if(outputs[i].device == TSAL_GREEN){
							Default_Switch_State = set_bit(Default_Switch_State,i,!RxMessage.Bytes[2]);
							switch_output();
						}
					}
					break;
				case 1:				//GREEN
					for(int i = 0; i < 8; i++){
						if(outputs[i].device == TSAL_GREEN){
							Default_Switch_State = set_bit(Default_Switch_State,i,RxMessage.Bytes[2]);
							switch_output();
						}
						if(outputs[i].device == TSAL_RED){
							Default_Switch_State = set_bit(Default_Switch_State,i,!RxMessage.Bytes[2]);
							switch_output();
						}
					}
					break;
			}
		}
		break;
	default:
		//decode_error(); //TODO: IMPLEMENT
		Error_Handler();
		break;
	}
}



void Current_Sense_process(){
	//4031 == 3.3V since 12bit, have to pick shunt resistor according to this
	for(int i = 0; i < 8; i++){
		outputs[i].raw_current = outputs[i].Current_Sense[0];
		for(int z = 1; z < I_AVERAGE; z++){
			outputs[i].raw_current = (outputs[i].raw_current + outputs[i].Current_Sense[0])/2;

		}
		outputs[i].actual_current = Current_Sense_Raw_to_mA(outputs[i].raw_current);
	}
	check_warnings();
}

void check_warnings(){
	for(uint8_t x = 0; x < 7; x++){
		if(outputs[x].device != NC){
			if(outputs[x].actual_current >= outputs[x].Warning_Current){
				if(outputs[x].actual_current >= outputs[x].Over_Current){
					Default_Switch_State = set_bit(Default_Switch_State, outputs[x].pin, 0);
					Over_current(x);
				}else{
					Warning_current(x);
				}
			}
		}
		if(outputs[x].actual_current < outputs[x].Under_Current){
			Under_current(x);
		}
	}
	switch_output();
}


void ConfigureCurrentSense(uint8_t SEL0, uint8_t SEL1){
	HAL_GPIO_WritePin(GPIOB,SEL0_Pin,SEL0);
	HAL_GPIO_WritePin(GPIOB,SEL1_Pin,SEL1);
}

void ReadADCValues(uint16_t *adc1_values, uint16_t *adc2_values){
	for(int i = 0; i < I_AVERAGE; i++){
		if(HAL_ADC_Start(&hadc1)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_Start(&hadc2)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_PollForConversion(&hadc2,100)!=HAL_OK){Error_Handler();}
        adc1_values[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
        adc2_values[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
		if(HAL_ADC_Stop(&hadc1)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_Stop(&hadc2)!=HAL_OK){Error_Handler();}
	}
}

void Current_Sense_read(){
	for(int x = 0;x < 5; x++){
		switch(x){
		case 0:
			ConfigureCurrentSense(0, 0);
			ReadADCValues(outputs[0].Current_Sense, outputs[4].Current_Sense);
			break;
		case 1:
			ConfigureCurrentSense(0, 1);
			ReadADCValues(outputs[1].Current_Sense, outputs[5].Current_Sense);
			break;
		case 2:
			ConfigureCurrentSense(1, 0);
			ReadADCValues(outputs[2].Current_Sense, outputs[6].Current_Sense);
			break;
		case 3:
			ConfigureCurrentSense(1, 1);
			ReadADCValues(outputs[3].Current_Sense, outputs[7].Current_Sense);
			break;
		}
	}
	Current_Sense_process();
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

uint16_t Current_Sense_Raw_to_mA(uint16_t raw){
	//4095 is the max, depending on resistors we will find the current values		3.3 V == 4,95 A
	uint32_t max_mA = 4950;
	uint16_t current = 0;

	current = raw*max_mA / 4095;
	//current = raw*3300 / 4095;

	return current;
}

