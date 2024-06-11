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

	//OUTPUT 1 in mA
	Warning_Current[0] = 1900;
	Over_Current[0] = 2050;
	Under_Current[0] = 00;

	//OUTPUT 2 in mA
	Warning_Current[1] = 1900;
	Over_Current[1] = 2050;
	Under_Current[1] = 00;

	//OUTPUT 3 in mA
	Warning_Current[2] = 1900;
	Over_Current[2] = 2050;
	Under_Current[2] = 00;

	//OUTPUT 4 in mA
	Warning_Current[3] = 1900;
	Over_Current[3] = 2050;
	Under_Current[3] = 00;

	//OUTPUT 5 in mA
	Warning_Current[4] = 1900;
	Over_Current[4] = 2050;
	Under_Current[4] = 00;

	//OUTPUT 6 in mA
	Warning_Current[5] = 1900;
	Over_Current[5] = 2050;
	Under_Current[5] = 00;

	//OUTPUT 7 in mA
	Warning_Current[6] = 1900;
	Over_Current[6] = 2050;
	Under_Current[6] = 00;

	//OUTPUT 8 in mA
	Warning_Current[7] = 1900;
	Over_Current[7] = 2050;
	Under_Current[7] = 00;

	//For analog node
	Warning_Current[8] = 2000;
	Over_Current[8] = 2000;
	Under_Current[8] = 0;

	Default_Switch_State = 0b00001111; //each bit represent one output [8,7,6,5,4,3,2,1]

	output_list[0] = BRAKE_LIGHT;
	output_list[1] = FAN;
	output_list[2] = FAN;
	output_list[3] = PUMP;
	output_list[4] = 0;	//NC
	output_list[5] = 0;	//NC
	output_list[6] = 0;	//NC
	output_list[7] = 0;	//NC

	PWM_out_enable = 0b11;

	//Duty cycle 0-100%
	PWM_width[0] = 10;
	PWM_width[1] = 10;

	output();
}

void Config_2(void){

	CAN_ID = 18;
	CAN_interval = 1000; //in ms

	//OUTPUT 1 in mA
	Warning_Current[0] = 1900;
	Over_Current[0] = 2050;
	Under_Current[0] = 00;

	//OUTPUT 2 in mA
	Warning_Current[1] = 1900;
	Over_Current[1] = 2050;
	Under_Current[1] = 00;

	//OUTPUT 3 in mA
	Warning_Current[2] = 1900;
	Over_Current[2] = 2050;
	Under_Current[2] = 00;

	//OUTPUT 4 in mA
	Warning_Current[3] = 1900;
	Over_Current[3] = 2050;
	Under_Current[3] = 00;

	//OUTPUT 5 in mA
	Warning_Current[4] = 1900;
	Over_Current[4] = 2050;
	Under_Current[4] = 00;

	//OUTPUT 6 in mA
	Warning_Current[5] = 1900;
	Over_Current[5] = 2050;
	Under_Current[5] = 00;

	//OUTPUT 7 in mA
	Warning_Current[6] = 1900;
	Over_Current[6] = 2050;
	Under_Current[6] = 00;

	//OUTPUT 8 in mA
	Warning_Current[7] = 1900;
	Over_Current[7] = 2050;
	Under_Current[7] = 00;

	//For analog node
	Warning_Current[8] = 2000;
	Over_Current[8] = 2000;
	Under_Current[8] = 0;

	Default_Switch_State = 0b01000111; //each bit represent one output [8,7,6,5,4,3,2,1]

	output_list[0] = TSAL;
	output_list[1] = FAN;
	output_list[2] = FAN;
	output_list[3] = BRAKE_LIGHT;
	output_list[4] = BUZZER;	//NC
	output_list[5] = IMU;	//NC
	output_list[6] = PUMP;	//NC
	output_list[7] = 0;	//NC

	PWM_out_enable = 0b11;

	//Duty cycle 0-100%
	PWM_width[0] = 10;
	PWM_width[1] = 10;

	output();
}

void Config_3(void){

	CAN_ID = 19;
	CAN_interval = 1000; //in ms

	//OUTPUT 1 in mA
	Warning_Current[0] = 1900;
	Over_Current[0] = 2050;
	Under_Current[0] = 00;

	//OUTPUT 2 in mA
	Warning_Current[1] = 1900;
	Over_Current[1] = 2050;
	Under_Current[1] = 00;

	//OUTPUT 3 in mA
	Warning_Current[2] = 1900;
	Over_Current[2] = 2050;
	Under_Current[2] = 00;

	//OUTPUT 4 in mA
	Warning_Current[3] = 1900;
	Over_Current[3] = 2050;
	Under_Current[3] = 00;

	//OUTPUT 5 in mA
	Warning_Current[4] = 1900;
	Over_Current[4] = 2050;
	Under_Current[4] = 00;

	//OUTPUT 6 in mA
	Warning_Current[5] = 1900;
	Over_Current[5] = 2050;
	Under_Current[5] = 00;

	//OUTPUT 7 in mA
	Warning_Current[6] = 1900;
	Over_Current[6] = 2050;
	Under_Current[6] = 00;

	//OUTPUT 8 in mA
	Warning_Current[7] = 1900;
	Over_Current[7] = 2050;
	Under_Current[7] = 00;

	//For analog node
	Warning_Current[8] = 2000;
	Over_Current[8] = 2000;
	Under_Current[8] = 0;

	Default_Switch_State = 0b00000000; //each bit represent one output [8,7,6,5,4,3,2,1]

	output_list[0] = BRAKE_LIGHT;
	output_list[1] = FAN;
	output_list[2] = FAN;
	output_list[3] = PUMP;
	output_list[4] = 0;	//NC
	output_list[5] = 0;	//NC
	output_list[6] = 0;	//NC
	output_list[7] = 0;	//NC

	PWM_out_enable = 0b11;

	//Duty cycle 0-100%
	PWM_width[0] = 10;
	PWM_width[1] = 10;

	output();
}

