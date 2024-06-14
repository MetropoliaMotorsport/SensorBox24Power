/*
 * config.h
 *
 *  Created on: Nov 19, 2023
 *      Author: csort
 */


#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_


#define ID 1 //1 for front, 2 for back

#define I_AVERAGE 32

#define NC 0
#define BRAKE_LIGHT 1
#define BRAKE_PRESSURE_SENSOR 2
#define FAN 3
#define PUMP 4
#define BUZZER 5
#define TSAL 6
#define IMU 7

void Config_Setup(void);
void Config_1(void);
void Config_2(void);
void Config_3(void);

typedef struct{
	uint16_t device;
	uint16_t Over_Current;
	uint16_t Warning_Current;
	uint16_t Under_Current;
	uint8_t pin;
	uint16_t actual_current;
	uint16_t raw_current;
	uint16_t Current_Sense[I_AVERAGE];
}Outputs;

extern Outputs outputs[8];

enum pins{
	OUT0_1_pin, OUT1_1_pin, OUT2_1_pin, OUT3_1_pin,
	OUT0_2_pin, OUT1_2_pin, OUT2_2_pin, OUT3_2_pin
};


#endif /* INC_CONFIG_H_ */
