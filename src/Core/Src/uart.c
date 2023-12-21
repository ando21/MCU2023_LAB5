#include "uart.h"
#include "sofware_timer.h"
#include <stdlib.h>
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t command_flag = 0;
uint8_t first_read_flag = 0;
uint8_t command_data;
uint8_t communicationStage = 0;
uint32_t ADC_value;
uint8_t status = 0;
uint32_t old_ADC = 0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		buffer[index_buffer++] = temp;
		if(index_buffer == 30) index_buffer = 0;

		buffer_flag = 1;
		HAL_UART_Transmit(&huart2, &temp, 1, 1000);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

void command_parser_fsm(){
	if(communicationStage == 0){
		switch(status){
		case INIT:
			if(temp == '!'){
				status = '!';
			}else{
				status = INIT;
			}
			break;
		case '!':
			if(temp == 'R'){
				status = 'R';
			}else{
				status = INIT;
			}
			break;
		case 'R':
			if(temp == 'S'){
				status = 'S';
			}else{
				status = INIT;
			}
			break;
		case 'S':
			if(temp == 'T'){
				status = 'T';
			}else{
				status = INIT;
			}
			break;
		case 'T':
			if(temp == '#'){
				timer2_flag = 1;
				command_flag = 1;
				first_read_flag = 1;
				communicationStage = 1;
				status = INIT;
			}else{
				status = INIT;
			}
			break;
		default:
			break;
		}
	}else{
		switch(status){
		case INIT:
			if(temp == '!'){
				status = '!';
			}else{
				status = INIT;
			}
			break;
		case '!':
			if(temp == 'O'){
				status = 'O';
			}else{
				status = INIT;
			}
			break;
		case 'O':
			if(temp == 'K'){
				status = 'K';
			}else{
				status = INIT;
			}
			break;
		case 'K':
			if(temp == '#'){
				timer2_flag = 0;
				command_flag = 0;
				communicationStage = 0;
				status = INIT;
			}else{
				status = INIT;
			}
			break;
		default:
			break;
		}
	}
}

void uart_communication_fsm(){
	if(command_flag == 1){
		if(timer2_flag == 1){
			uint8_t str[]="!ADC=";
			uint8_t endline[] = "#\r";
			char* buffer2;
			if(first_read_flag == 1){
				ADC_value = HAL_ADC_GetValue(&hadc1);
				old_ADC = ADC_value;
				first_read_flag = 0;
			}
			HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
			itoa(old_ADC, buffer2, 10);
			HAL_UART_Transmit(&huart2, buffer2, sizeof(buffer2), 1000);
			HAL_UART_Transmit(&huart2, endline, sizeof(endline), 1000);
			setTimer2(3000);
		}
	}
}
