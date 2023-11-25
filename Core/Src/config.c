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
	PWM_out_enable = 0b00000000;

	PWM_Prescalers[0] = 0 ;PWM_Prescalers[1] = 0 ;PWM_Prescalers[2] = 0 ;PWM_Prescalers[3] = 0 ;
	PWM_Prescalers[4] = 0 ;PWM_Prescalers[5] = 0 ;PWM_Prescalers[6] = 0 ;PWM_Prescalers[7] = 0 ;
}

