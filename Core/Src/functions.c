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





uint8_t RxData[8];
uint8_t TxData[8];
uint8_t toggle = 0;


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		/* Retreive Rx messages from RX FIFO0 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
		{
			/* Reception Error */
			Error_Handler();
		}else{
			if(RxHeader.Identifier == CAN_ID){
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



void output(){
	uint8_t i = 0;
	uint8_t bit = 0;
	for(i = 0; i < 8;i++){
		bit = check_bit(Default_Switch_State, i);
		switch(i){
		case 0:
			HAL_GPIO_WritePin(GPIOB,IN0_Pin,bit);
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
			HAL_GPIO_WritePin(GPIOB,IN2_2_Pin,bit);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOB,IN3_2_Pin,bit);
			break;
		default:
			Error_Handler();
			break;
		}
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
	switch(RxData[0]){
	case 1:							//Set PWM RxData[1] -> which PWM, RxData[2] = 1 -> Duty Cycle || RxData[2] = 2 -> Frequency, RxData[3] -> value
		switch(RxData[1]){
		case 1:										//PUMPS
			PWM_width[0] = RxData[2];
			set_pwm_duty_cycle(&htim1);
			break;
		case 2:										//FANS
			PWM_width[1] = RxData[2];
			set_pwm_duty_cycle(&htim2);
			break;
		default:
			Error_Handler();
			break;
		}
		break;
	case 2:							//Switch output on/off
		Default_Switch_State = set_bit(Default_Switch_State,RxData[1],RxData[2]); //if RxData[2] is 0 -> OFF, if RxData[2] is 1 -> ON
		output();
		break;
	case 3:							// turning analog node on and off, RxData[1] -> 0 is off 1 is on
		HAL_GPIO_WritePin(GPIOA,LED2_Pin,RxData[1]);
		break;
	case 4:							//switch BRAKE_LIGHT	RxData[1] --> 0 for off and 1 for on
		for(int i = 0; i < 8; i++){
			if(output_list[i] == BRAKE_LIGHT){
				Default_Switch_State = set_bit(Default_Switch_State,i,RxData[1]);
				output();
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
	PROC[0] = IN1_1_Current_Sense[0];
	PROC[1] = IN2_1_Current_Sense[0];
	PROC[2] = IN3_1_Current_Sense[0];
	PROC[3] = IN4_1_Current_Sense[0];
	PROC[4] = IN1_2_Current_Sense[0];
	PROC[5] = IN2_2_Current_Sense[0];
	PROC[6] = IN3_2_Current_Sense[0];
	PROC[7] = IN4_2_Current_Sense[0];
	PROC[8] = Analog_Current_Sense[0];
	for(int i = 1; i < I_AVERAGE; i++){
		PROC[0] = (PROC[0] + IN1_1_Current_Sense[i])/2;
		PROC[1] = (PROC[1] + IN2_1_Current_Sense[i])/2;
		PROC[2] = (PROC[2] + IN3_1_Current_Sense[i])/2;
		PROC[3] = (PROC[3] + IN4_1_Current_Sense[i])/2;
		PROC[4] = (PROC[4] + IN1_2_Current_Sense[i])/2;
		PROC[5] = (PROC[5] + IN2_2_Current_Sense[i])/2;
		PROC[6] = (PROC[6] + IN3_2_Current_Sense[i])/2;
		PROC[7] = (PROC[7] + IN4_2_Current_Sense[i])/2;
		if(i % 2 == 0){
			PROC[8] = (PROC[8] + Analog_Current_Sense[i/2])/2;
		}
	}
	PROC[0] = Current_Sense_Raw_to_mA(PROC[0]);
	PROC[1] = Current_Sense_Raw_to_mA(PROC[1]);
	PROC[2] = Current_Sense_Raw_to_mA(PROC[2]);
	PROC[3] = Current_Sense_Raw_to_mA(PROC[3]);
	PROC[4] = Current_Sense_Raw_to_mA(PROC[4]);
	PROC[5] = Current_Sense_Raw_to_mA(PROC[5]);
	PROC[6] = Current_Sense_Raw_to_mA(PROC[6]);
	PROC[7] = Current_Sense_Raw_to_mA(PROC[7]);
	PROC[8] = Current_Sense_Raw_to_mA(PROC[8]);
	check_warnings();
}

void check_warnings(){
	for(uint8_t x = 0; x < 7; x++){
		if(PROC[x] >= Warning_Current[x]){
			if(PROC[x] >= Over_Current[x]){
				Default_Switch_State = set_bit(Default_Switch_State, x, 0);
				Over_current(x);
			}else{
				Warning_current(x);
			}
		}
	/*	if(PROC[x] < Under_Current[x]){
			Under_current(x);
		}*/
	}
	if(PROC[8] >= Warning_Current[8]){
		if(PROC[8] >= Over_Current[8]){
			Over_current(8);
			//HAL_GPIO_WritePin(GPIOB,AnalogPower_EN_Pin,0);
		}else{
			Warning_current(8);
		}
	}
	/*if(PROC[8] < Under_Current[8]){
		Under_current(8);
	}*/
	output();

}

void Current_Sense_read(){
	for(int x = 0; x < 5; x++){
		switch(x){
		case 0:
			//chip_select_read();
			Current_Sense_SEL[0] = 0;
			Current_Sense_SEL[1] = 0;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,Current_Sense_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,Current_Sense_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,100)!=HAL_OK){Error_Handler();}
				IN1_1_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN1_2_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 1:
			//chip_select_read();
			Current_Sense_SEL[0] = 0;
			Current_Sense_SEL[1] = 1;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,Current_Sense_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,Current_Sense_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,100)!=HAL_OK){Error_Handler();}
				IN2_1_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN2_2_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 2:
			//chip_select_read();
			Current_Sense_SEL[0] = 1;
			Current_Sense_SEL[1] = 0;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,Current_Sense_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,Current_Sense_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start_IT(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,100)!=HAL_OK){Error_Handler();}
				IN3_1_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN3_2_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop_IT(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 3:
			//chip_select_read();
			Current_Sense_SEL[0] = 1;
			Current_Sense_SEL[1] = 1;
			HAL_GPIO_WritePin(GPIOB,SEL0_Pin,Current_Sense_SEL[0]);
			HAL_GPIO_WritePin(GPIOB,SEL1_Pin,Current_Sense_SEL[1]);
			for(int i = 0; i < I_AVERAGE; i++){
				if(HAL_ADC_Start_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Start_IT(&hadc2)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc2,100)!=HAL_OK){Error_Handler();}
				IN4_1_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
				IN4_2_Current_Sense[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
				if(HAL_ADC_Stop_IT(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_Stop_IT(&hadc2)!=HAL_OK){Error_Handler();}
			}
			break;
		case 4:
			//analog_read();
			for(int i = 0; i < I_AVERAGE/2; i++){
				if(HAL_ADC_Start(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();} //have to repeat this in all loops, so that the rank 2 ADC gets emptied as well
				Analog_Current_Sense_1[i] = (uint16_t)HAL_ADC_GetValue(&hadc1); //have to repeat this in all loops, so that the rank 2 ADC gets emptied as well
				if(HAL_ADC_Stop(&hadc1)!=HAL_OK){Error_Handler();}
			}
			//analog_read();
			for(int i = 0; i < I_AVERAGE/2; i++){
				if(HAL_ADC_Start(&hadc1)!=HAL_OK){Error_Handler();}
				if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();} //have to repeat this in all loops, so that the rank 2 ADC gets emptied as well
				Analog_Current_Sense_2[i] = (uint16_t)HAL_ADC_GetValue(&hadc1); //have to repeat this in all loops, so that the rank 2 ADC gets emptied as well
				if(HAL_ADC_Stop(&hadc1)!=HAL_OK){Error_Handler();}
				if(Analog_Current_Sense_1[i]>Analog_Current_Sense_2[i]){
					Analog_Current_Sense[i] = Analog_Current_Sense_1[i] - Analog_Current_Sense_2[i];
				}else{
					Analog_Current_Sense[i] = 0;
				}
			}
			break;

		}
//		This function is for checking how Current_Sense_SEL pins behave
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

	//current = raw*max_mA / 4095;
	current = raw*3300 / 4095;

	return current;
}
