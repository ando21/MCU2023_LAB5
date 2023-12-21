/*
 * uart.h
 *
 *  Created on: Dec 21, 2023
 *      Author: ADMIN
 */

#include "main.h"
#ifndef INC_UART_H_
#define INC_UART_H_

extern uint8_t buffer_flag;
#define MAX_BUFFER_SIZE 30
#define INIT 0

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_UART_H_ */
