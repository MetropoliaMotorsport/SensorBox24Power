#include "main.h"
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

	//OUTPUT 1 in mA
	WC_1_1 = 1900;
	OC_1_1 = 2050;
	UC_1_1 = 1800;

	//OUTPUT 2 in mA
	WC_2_1 = 1900;
	OC_2_1 = 2050;
	UC_2_1 = 1800;

	//OUTPUT 3 in mA
	WC_3_1 = 1900;
	OC_3_1 = 2050;
	UC_3_1 = 1800;

	//OUTPUT 4 in mA
	WC_4_1 = 1900;
	OC_4_1 = 2050;
	UC_4_1 = 1800;

	//OUTPUT 5 in mA
	WC_1_2 = 1900;
	OC_1_2 = 2050;
	UC_1_2 = 1800;

	//OUTPUT 6 in mA
	WC_2_2 = 1900;
	OC_2_2 = 2050;
	UC_2_2 = 1800;

	//OUTPUT 7 in mA
	WC_3_2 = 1900;
	OC_3_2 = 2050;
	UC_3_2 = 1800;

	//OUTPUT 8 in mA
	WC_4_2 = 1900;
	OC_4_2 = 2050;
	UC_4_2 = 1800;

	Default_Switch_State = 0b11111111; //each bit represent one output [1,2,3,4,5,6,7,8]
	PWM_out_enable = 0b00;

	//clock is xy MHz, thus set it such that xy/(prescaler*100) is going to be the frequency
	PWM_Prescalers[0] = 0;
	PWM_Prescalers[1] = 0;

	//Duty cycle 0-100%
	PWM_width[0] = 0;
	PWM_width[1] = 0;

	CAN_id[0] = 0x01; //CAN ID for output 1
	CAN_id[1] = 0x02; //CAN ID for output 2
	CAN_id[2] = 0x03; //CAN ID for output 3
	CAN_id[3] = 0x04; //CAN ID for output 4
	CAN_id[4] = 0x05; //CAN ID for output 5
	CAN_id[5] = 0x06; //CAN ID for output 6
	CAN_id[6] = 0x07; //CAN ID for output 7
	CAN_id[7] = 0x08; //CAN ID for output 8
}

void Config_2(void){

	//OUTPUT 1 in mA
	WC_1_1 = 1900;
	OC_1_1 = 2050;
	UC_1_1 = 1800;

	//OUTPUT 2 in mA
	WC_2_1 = 1900;
	OC_2_1 = 2050;
	UC_2_1 = 1800;

	//OUTPUT 3 in mA
	WC_3_1 = 1900;
	OC_3_1 = 2050;
	UC_3_1 = 1800;

	//OUTPUT 4 in mA
	WC_4_1 = 1900;
	OC_4_1 = 2050;
	UC_4_1 = 1800;

	//OUTPUT 5 in mA
	WC_1_2 = 1900;
	OC_1_2 = 2050;
	UC_1_2 = 1800;

	//OUTPUT 6 in mA
	WC_2_2 = 1900;
	OC_2_2 = 2050;
	UC_2_2 = 1800;

	//OUTPUT 7 in mA
	WC_3_2 = 1900;
	OC_3_2 = 2050;
	UC_3_2 = 1800;

	//OUTPUT 8 in mA
	WC_4_2 = 1900;
	OC_4_2 = 2050;
	UC_4_2 = 1800;

	Default_Switch_State = 0b11111111; //each bit represent one output [1,2,3,4,5,6,7,8]
	PWM_out_enable = 0b00;

	//clock is xy MHz, thus set it such that xy/(prescaler*100) is going to be the frequency
	PWM_Prescalers[0] = 0;
	PWM_Prescalers[1] = 0;

	//Duty cycle 0-100%
	PWM_width[0] = 0;
	PWM_width[1] = 0;

	CAN_id[0] = 0x01; //CAN ID for output 1
	CAN_id[1] = 0x02; //CAN ID for output 2
	CAN_id[2] = 0x03; //CAN ID for output 3
	CAN_id[3] = 0x04; //CAN ID for output 4
	CAN_id[4] = 0x05; //CAN ID for output 5
	CAN_id[5] = 0x06; //CAN ID for output 6
	CAN_id[6] = 0x07; //CAN ID for output 7
	CAN_id[7] = 0x08; //CAN ID for output 8
}

void Config_3(void){

	//OUTPUT 1 in mA
	WC_1_1 = 1900;
	OC_1_1 = 2050;
	UC_1_1 = 1800;

	//OUTPUT 2 in mA
	WC_2_1 = 1900;
	OC_2_1 = 2050;
	UC_2_1 = 1800;

	//OUTPUT 3 in mA
	WC_3_1 = 1900;
	OC_3_1 = 2050;
	UC_3_1 = 1800;

	//OUTPUT 4 in mA
	WC_4_1 = 1900;
	OC_4_1 = 2050;
	UC_4_1 = 1800;

	//OUTPUT 5 in mA
	WC_1_2 = 1900;
	OC_1_2 = 2050;
	UC_1_2 = 1800;

	//OUTPUT 6 in mA
	WC_2_2 = 1900;
	OC_2_2 = 2050;
	UC_2_2 = 1800;

	//OUTPUT 7 in mA
	WC_3_2 = 1900;
	OC_3_2 = 2050;
	UC_3_2 = 1800;

	//OUTPUT 8 in mA
	WC_4_2 = 1900;
	OC_4_2 = 2050;
	UC_4_2 = 1800;

	Default_Switch_State = 0b11111111; //each bit represent one output [1,2,3,4,5,6,7,8]
	PWM_out_enable = 0b00;

	//clock is xy MHz, thus set it such that xy/(prescaler*100) is going to be the frequency
	PWM_Prescalers[0] = 0;
	PWM_Prescalers[1] = 0;

	//Duty cycle 0-100%
	PWM_width[0] = 0;
	PWM_width[1] = 0;

	CAN_id[0] = 0x01; //CAN ID for output 1
	CAN_id[1] = 0x02; //CAN ID for output 2
	CAN_id[2] = 0x03; //CAN ID for output 3
	CAN_id[3] = 0x04; //CAN ID for output 4
	CAN_id[4] = 0x05; //CAN ID for output 5
	CAN_id[5] = 0x06; //CAN ID for output 6
	CAN_id[6] = 0x07; //CAN ID for output 7
	CAN_id[7] = 0x08; //CAN ID for output 8
}


