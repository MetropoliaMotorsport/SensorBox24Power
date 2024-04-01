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

	CAN_ID = 3;
	CAN_interval = 1000; //in ms

	//OUTPUT 1 in mA
	WC[0] = 1900;
	OC[0] = 2050;
	UC[0] = 1800;

	//OUTPUT 2 in mA
	WC[1] = 1900;
	OC[1] = 2050;
	UC[1] = 1800;

	//OUTPUT 3 in mA
	WC[2] = 1900;
	OC[2] = 2050;
	UC[2] = 1800;

	//OUTPUT 4 in mA
	WC[3] = 1900;
	OC[3] = 2050;
	UC[3] = 1800;

	//OUTPUT 5 in mA
	WC[4] = 1900;
	OC[4] = 2050;
	UC[4] = 1800;

	//OUTPUT 6 in mA
	WC[5] = 1900;
	OC[5] = 2050;
	UC[5] = 1800;

	//OUTPUT 7 in mA
	WC[6] = 1900;
	OC[6] = 2050;
	UC[6] = 1800;

	//OUTPUT 8 in mA
	WC[7] = 1900;
	OC[7] = 2050;
	UC[7] = 1800;

	Default_Switch_State = 0b00011011; //each bit represent one output [8,7,6,5,4,3,2,1]
	PWM_out_enable = 0b00;

	//clock is xy MHz, thus set it such that xy/(prescaler*100) is going to be the frequency
	PWM_Prescalers[0] = 0;
	PWM_Prescalers[1] = 0;

	if(PWM_out_enable >> 2 != 0){
		PWM_speed[0] = 150000000/(PWM_Prescalers[0]*100);
	}else{
		PWM_speed[0] = 0;
	}
	if(PWM_out_enable >> 1 != 0){
		PWM_speed[1] = 150000000/(PWM_Prescalers[1]*100);
	}else{
		PWM_speed[1] = 0;
	}

	//Duty cycle 0-100%
	PWM_width[0] = 0;
	PWM_width[1] = 0;

	set_pwm_duty_cycle(&htim1,PWM_width[0]);
	set_pwm_duty_cycle(&htim2,PWM_width[1]);

	set_pwm_freq(&htim1,PWM_speed[0]);
	set_pwm_freq(&htim2,PWM_speed[1]);

	output();
}

void Config_2(void){

	CAN_ID = 4;
	CAN_interval = 1000; //in ms

	//OUTPUT 1 in mA
	WC[0] = 1900;
	OC[0] = 2050;
	UC[0] = 1800;

	//OUTPUT 2 in mA
	WC[1] = 1900;
	OC[1] = 2050;
	UC[1] = 1800;

	//OUTPUT 3 in mA
	WC[2] = 1900;
	OC[2] = 2050;
	UC[2] = 1800;

	//OUTPUT 4 in mA
	WC[3] = 1900;
	OC[3] = 2050;
	UC[3] = 1800;

	//OUTPUT 5 in mA
	WC[4] = 1900;
	OC[4] = 2050;
	UC[4] = 1800;

	//OUTPUT 6 in mA
	WC[5] = 1900;
	OC[5] = 2050;
	UC[5] = 1800;

	//OUTPUT 7 in mA
	WC[6] = 1900;
	OC[6] = 2050;
	UC[6] = 1800;

	//OUTPUT 8 in mA
	WC[7] = 1900;
	OC[7] = 2050;
	UC[7] = 1800;

	Default_Switch_State = 0b00000000; //each bit represent one output [1,2,3,4,5,6,7,8]
	PWM_out_enable = 0b00;

	//clock is xy MHz, thus set it such that xy/(prescaler*100) is going to be the frequency
	PWM_Prescalers[0] = 0;
	PWM_Prescalers[1] = 0;

	//Duty cycle 0-100%
	PWM_width[0] = 0;
	PWM_width[1] = 0;

	set_pwm_duty_cycle(&htim1,PWM_width[0]);
	set_pwm_duty_cycle(&htim2,PWM_width[1]);

	set_pwm_freq(&htim1,PWM_speed[0]);
	set_pwm_freq(&htim2,PWM_speed[1]);

	output();
}

void Config_3(void){

	CAN_ID = 5;
	CAN_interval = 1000; //in ms

	//OUTPUT 1 in mA
	WC[0] = 1900;
	OC[0] = 2050;
	UC[0] = 1800;

	//OUTPUT 2 in mA
	WC[1] = 1900;
	OC[1] = 2050;
	UC[1] = 1800;

	//OUTPUT 3 in mA
	WC[2] = 1900;
	OC[2] = 2050;
	UC[2] = 1800;

	//OUTPUT 4 in mA
	WC[3] = 1900;
	OC[3] = 2050;
	UC[3] = 1800;

	//OUTPUT 5 in mA
	WC[4] = 1900;
	OC[4] = 2050;
	UC[4] = 1800;

	//OUTPUT 6 in mA
	WC[5] = 1900;
	OC[5] = 2050;
	UC[5] = 1800;

	//OUTPUT 7 in mA
	WC[6] = 1900;
	OC[6] = 2050;
	UC[6] = 1800;

	//OUTPUT 8 in mA
	WC[7] = 1900;
	OC[7] = 2050;
	UC[7] = 1800;

	Default_Switch_State = 0b11111111; //each bit represent one output [1,2,3,4,5,6,7,8]
	PWM_out_enable = 0b00;

	//clock is xy MHz, thus set it such that xy/(prescaler*100) is going to be the frequency
	PWM_Prescalers[0] = 0;
	PWM_Prescalers[1] = 0;

	//Duty cycle 0-100%
	PWM_width[0] = 0;
	PWM_width[1] = 0;

	set_pwm_duty_cycle(&htim1,PWM_width[0]);
	set_pwm_duty_cycle(&htim2,PWM_width[1]);

	set_pwm_freq(&htim1,PWM_speed[0]);
	set_pwm_freq(&htim2,PWM_speed[1]);

	output();
}


