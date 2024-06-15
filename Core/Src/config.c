#include "main.h"
#include "functions.h"
#include "commands.h"
#include "config.h"

void Config_Setup(void)
{
#if ID == 1

		Config_1();

#elif ID == 2

		Config_2();
#else //catch everything that is not a proper ID, give it settings that the debug board would get

		Config_3();

#endif
}

void Config_1(void){

	CAN_ID = 17;
	CAN_interval = 1000; //in ms

	//definition of Outputs
	Outputs OUT0_1 = {NC, 2050, 1900, 0, GPIOB, IN0_Pin, OUT0_1_pin};
	Outputs OUT1_1 = {NC, 2050, 1900, 0, GPIOA, IN1_Pin, OUT1_1_pin};
	Outputs OUT2_1 = {NC, 2050, 1900, 0, GPIOA, IN2_Pin, OUT2_1_pin};
	Outputs OUT3_1 = {NC, 2050, 1900, 0, GPIOA, IN3_Pin, OUT3_1_pin};
	Outputs OUT0_2 = {NC, 2050, 1900, 0, GPIOA, IN0_2_Pin, OUT0_2_pin};
	Outputs OUT1_2 = {NC, 2050, 1900, 0, GPIOA, IN1_2_Pin, OUT1_2_pin};
	Outputs OUT2_2 = {NC, 2050, 1900, 0, GPIOB, IN2_2_Pin, OUT2_2_pin};
	Outputs OUT3_2 = {NC, 2050, 1900, 0, GPIOB, IN3_2_Pin, OUT3_2_pin};

	outputs[OUT0_1.pin] = OUT0_1;
	outputs[OUT1_1.pin] = OUT1_1;
	outputs[OUT2_1.pin] = OUT2_1;
	outputs[OUT3_1.pin] = OUT3_1;
	outputs[OUT0_2.pin] = OUT0_2;
	outputs[OUT1_2.pin] = OUT1_2;
	outputs[OUT2_2.pin] = OUT2_2;
	outputs[OUT3_2.pin] = OUT3_2;

	Default_Switch_State = 0b00000000; //each bit represent one output [8,7,6,5,4,3,2,1]

	PWM_out_enable = 0b11;

	//Duty cycle 0-100%
	PWM_width[0] = 10;
	PWM_width[1] = 10;

	switch_output();

}

void Config_2(void){

	CAN_ID = 22;
	CAN_interval = 1000; //in ms

	//definition of Outputs
	Outputs OUT0_1 = {TSAL, 2050, 1900, 0, GPIOB, IN0_Pin, OUT0_1_pin};
	Outputs OUT1_1 = {FAN, 2050, 1900, 0, GPIOA, IN1_Pin, OUT1_1_pin};
	Outputs OUT2_1 = {FAN, 2050, 1900, 0, GPIOA, IN2_Pin, OUT2_1_pin};
	Outputs OUT3_1 = {BRAKE_LIGHT, 2050, 1900, 0, GPIOA, IN3_Pin, OUT3_1_pin};
	Outputs OUT0_2 = {BUZZER, 2050, 1900, 0, GPIOA, IN0_2_Pin, OUT0_2_pin};
	Outputs OUT1_2 = {IMU, 2050, 1900, 0, GPIOA, IN1_2_Pin, OUT1_2_pin};
	Outputs OUT2_2 = {PUMP, 2050, 1900, 0, GPIOB, IN2_2_Pin, OUT2_2_pin};
	Outputs OUT3_2 = {NC, 2050, 1900, 0, GPIOB, IN3_2_Pin, OUT3_2_pin};

	outputs[OUT0_1.pin] = OUT0_1;
	outputs[OUT1_1.pin] = OUT1_1;
	outputs[OUT2_1.pin] = OUT2_1;
	outputs[OUT3_1.pin] = OUT3_1;
	outputs[OUT0_2.pin] = OUT0_2;
	outputs[OUT1_2.pin] = OUT1_2;
	outputs[OUT2_2.pin] = OUT2_2;
	outputs[OUT3_2.pin] = OUT3_2;

	Default_Switch_State = 0b01100111; //each bit represent one output [8,7,6,5,4,3,2,1]

	PWM_out_enable = 0b11;

	//Duty cycle 0-100%
	PWM_width[0] = 10;
	PWM_width[1] = 10;

	switch_output();

}

void Config_3(void){

	CAN_ID = 19;
	CAN_interval = 1000; //in ms

	//definition of Outputs
	Outputs OUT0_1 = {NC, 2050, 1900, 0, GPIOB, IN0_Pin, OUT0_1_pin};
	Outputs OUT1_1 = {NC, 2050, 1900, 0, GPIOA, IN1_Pin, OUT1_1_pin};
	Outputs OUT2_1 = {NC, 2050, 1900, 0, GPIOA, IN2_Pin, OUT2_1_pin};
	Outputs OUT3_1 = {NC, 2050, 1900, 0, GPIOA, IN3_Pin, OUT3_1_pin};
	Outputs OUT0_2 = {NC, 2050, 1900, 0, GPIOA, IN0_2_Pin, OUT0_2_pin};
	Outputs OUT1_2 = {NC, 2050, 1900, 0, GPIOA, IN1_2_Pin, OUT1_2_pin};
	Outputs OUT2_2 = {NC, 2050, 1900, 0, GPIOB, IN2_2_Pin, OUT2_2_pin};
	Outputs OUT3_2 = {NC, 2050, 1900, 0, GPIOB, IN3_2_Pin, OUT3_2_pin};

	outputs[OUT0_1.pin] = OUT0_1;
	outputs[OUT1_1.pin] = OUT1_1;
	outputs[OUT2_1.pin] = OUT2_1;
	outputs[OUT3_1.pin] = OUT3_1;
	outputs[OUT0_2.pin] = OUT0_2;
	outputs[OUT1_2.pin] = OUT1_2;
	outputs[OUT2_2.pin] = OUT2_2;
	outputs[OUT3_2.pin] = OUT3_2;

	Default_Switch_State = 0b00000000; //each bit represent one output [8,7,6,5,4,3,2,1]

	PWM_out_enable = 0b11;

	//Duty cycle 0-100%
	PWM_width[0] = 10;
	PWM_width[1] = 10;

	switch_output();
}


