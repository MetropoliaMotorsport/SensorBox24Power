/*
 * functions.h
 *
 *  Created on: Nov 26, 2023
 *      Author: marcelc
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

void CS_read();
void CS_process();
void check_warnings();
void print_out(const char *text, uint8_t out_mode);
void raw_to_mA();
void set_pwm(TIM_HandleTypeDef *htim, uint16_t value);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void decode();
uint8_t check_bit(uint8_t byte, uint8_t bitn);
void set_bit(uint8_t byte, uint8_t pos, uint8_t new_bit);

#endif /* INC_FUNCTIONS_H_ */
