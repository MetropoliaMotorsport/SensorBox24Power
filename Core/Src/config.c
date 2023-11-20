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
	Default_Switch_State = 0b11111111; //each bit represent one output
	PWM_out_enable = 0b00000000;

	PWM_prescalers[0] = 0 ;PWM_prescalers[1] = 0 ;PWM_prescalers[2] = 0 ;PWM_prescalers[3] = 0 ;
	PWM_prescalers[4] = 0 ;PWM_prescalers[5] = 0 ;PWM_prescalers[6] = 0 ;PWM_prescalers[7] = 0 ;
}

