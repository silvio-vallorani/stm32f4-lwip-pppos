/*
 * logger.c
 *
 *  Created on: 2 июл. 2018 г.
 *      Author: bork
 */
#include "logger.h"
#include "cmsis_os.h"

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


extern UART_HandleTypeDef huart3;

#define MAX_STRING_SIZE 1024

HAL_StatusTypeDef logger_Send(char* bArray, uint32_t size_bArray)
{
	HAL_StatusTypeDef status;

	for(int i=0;i<5;i++)
	{
		status = HAL_UART_Transmit_DMA(&huart3, (const uint8_t *)bArray, size_bArray);
		if (status == HAL_OK)
			break;
		osDelay(2);
	}


	while (HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY)
	{
		osDelay(1);
	}

	return status;
}

void logger(const char *format, ...)
{
		char buffer[MAX_STRING_SIZE];

		va_list args;
		va_start (args, format);
		vsprintf(buffer, format, args);
		va_end(args);

		buffer[MAX_STRING_SIZE-1]=0;

		logger_Send(buffer, strlen(buffer));
}


