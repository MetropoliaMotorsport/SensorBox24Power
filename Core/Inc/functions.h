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
void output();
uint16_t CS_Raw_to_mA(uint16_t raw);
void decode();
uint8_t check_bit(uint8_t byte, uint8_t bitn);
uint8_t set_bit(uint8_t byte, uint8_t pos, uint8_t new_bit);
void CAN_switch_state(uint8_t values);
void Over_current(uint8_t output_pin);
void Warning_current(uint8_t output_pin);
void Under_current(uint8_t output_pin);
void CAN_Send(uint8_t *TxData, uint32_t id);
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
void analog_read();
void chip_select_read();

#endif /* INC_FUNCTIONS_H_ */
