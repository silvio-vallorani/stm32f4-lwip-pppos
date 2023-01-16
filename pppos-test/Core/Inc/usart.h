/*
 * usart.h
 *
 *  Created on: Jan 16, 2023
 *      Author: svallorani
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f4xx_hal.h"

void usart_Open(void);
bool usart_Send(char* bArray, int size_bArray);
uint16_t usart_Recv(char* bArray, uint16_t maxLength);

#endif /* INC_USART_H_ */
