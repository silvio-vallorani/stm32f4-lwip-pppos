/*
 * usart.h
 *
 *  Created on: 2 июл. 2018 г.
 *      Author: bork
 */

#ifndef _USART_
#define _USART_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

void usart_Open(void);
bool usart_Send(char* bArray, int size_bArray);
uint16_t usart_Recv(char* bArray, uint16_t maxLength);

#endif /* _USART_ */
