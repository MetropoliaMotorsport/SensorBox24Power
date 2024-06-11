/*
 * config.h
 *
 *  Created on: Nov 19, 2023
 *      Author: csort
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_


#define ID 1 //1 for front, 2 for back

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



#endif /* INC_CONFIG_H_ */
