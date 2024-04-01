/*
 * commands.h
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

void decode(void);
void PWM(void);
void OUT_READ(uint8_t value);
void set_pwm_duty_cycle(TIM_HandleTypeDef *htim, uint16_t value);
void set_pwm_freq(TIM_HandleTypeDef *htim, uint16_t value);

#endif /* INC_COMMANDS_H_ */
