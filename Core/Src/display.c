/*
 * display.c
 *
 *  Created on: Apr 23, 2025
 *      Author: Florian
 */

#include "display.h"

extern UART_HandleTypeDef huart2;

uint8_t Cmd_End[3] = { 0xFF, 0xFF, 0xFF };

uint8_t RxData = 0;
int32_t num = 1;
float value = 1.1;

void NEXTION_SendString(char *ID, char *string) {
	char buffer[50];
	int len = sprintf(buffer, "%s.txt=\"%s\"", ID, string);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, len, 1000);
	HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
}

void NEXTION_SendIntValue(char *ID, int *value) {
	int buffer[50];
	int len = sprintf(buffer, "%s.val=%d", ID, value);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, len, 1000);
	HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
}


void NEXTION_SendFloat (char *obj, float num, int dp)
{
	// convert to the integer
	int32_t number = num*(pow(10,dp));

	uint8_t *buffer = malloc(30*sizeof (char));
	int len = sprintf ((char *)buffer, "%s.vvs1=%d", obj, dp);
	HAL_UART_Transmit(&huart2, buffer, len, 1000);
	HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);


	len = sprintf ((char *)buffer, "%s.val=%ld", obj, number);
	HAL_UART_Transmit(&huart2, buffer, len, 1000);
	HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
	free(buffer);
}
