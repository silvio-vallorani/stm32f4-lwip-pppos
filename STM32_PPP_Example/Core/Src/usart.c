/*
 * usart.c
 *
 *  Created on: 2 июл. 2018 г.
 *      Author: bork
 */
#include "usart.h"
#include "logger.h"

#include "cmsis_os.h"


#define Q_USART2_SIZE 2048

xQueueHandle g_qUsart;
osThreadId g_usart_rxTaskHandle;

extern UART_HandleTypeDef huart2;

void usart_rxTask(void const * argument);

uint8_t bGet[Q_USART2_SIZE] = {0};
uint16_t g_tail = 0;

void usart_Open(void)
{
	g_qUsart = xQueueCreate( Q_USART2_SIZE, sizeof( unsigned char ) );

	osThreadDef(usart_rxTask_NAME, usart_rxTask, osPriorityNormal, 0, (Q_USART2_SIZE/4+128));
	g_usart_rxTaskHandle = osThreadCreate(osThread(usart_rxTask_NAME), NULL);

	HAL_UART_Receive_DMA(&huart2, bGet, Q_USART2_SIZE);

}

void usart_rxTask(void const * argument)
{
	for(;;)
	{
		uint16_t length = Q_USART2_SIZE - huart2.hdmarx->Instance->NDTR;

		while(length - g_tail)
		{
			uint8_t tmp = bGet[g_tail];
			xQueueSendToBack( g_qUsart, &tmp, 100 );
			g_tail++;
			if (g_tail == Q_USART2_SIZE)
				g_tail = 0;
		}
	}
}

bool usart_Send(char* bArray, int size_bArray)
{
	HAL_StatusTypeDef status;

	status = HAL_UART_Transmit_DMA(&huart2, (const uint8_t *)bArray, size_bArray);

	while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY)
	{
		if (HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_RX)
			break;

		osDelay(1);
	}

	if (status == HAL_OK)
		return true;

	return false;
}

uint16_t usart_Recv(char* bArray, uint16_t maxLength)
{
	uint8_t tmp = 0;
	uint16_t length = 0;
	while(uxQueueMessagesWaiting(g_qUsart))
	{
		xQueueReceive( g_qUsart, &tmp, 100 );
		bArray[length] = tmp;
		length++;
		if (length >= maxLength)
			break;
	}

	return length;
}

