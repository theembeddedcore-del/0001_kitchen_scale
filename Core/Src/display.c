/*
 * display.c
 *
 *  Created on: Apr 23, 2025
 *      Author: Florian
 */

#include "display.h"

extern UART_HandleTypeDef huart2;

uint8_t Cmd_End[3] = { 0xFF, 0xFF, 0xFF };



void NEXTION_SendString(char* component, char* str)
{
    char buffer[64];
    int len = snprintf(buffer, sizeof(buffer), "%s.txt=\"%s\"", component, str);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, HAL_MAX_DELAY);

    uint8_t endBytes[3] = {0xFF, 0xFF, 0xFF};
    HAL_UART_Transmit(&huart2, endBytes, 3, HAL_MAX_DELAY);




//    static uint8_t uartTxBuffer[64 + 3]; // Buffer für String + 3 Endbytes
//
//	int len = snprintf((char*) uartTxBuffer, sizeof(uartTxBuffer) - 3,
//			"%s.txt=\"%s\"", component, str);
//
//	// 3 Endbytes anhängen
//	uartTxBuffer[len++] = 0xFF;
//	uartTxBuffer[len++] = 0xFF;
//	uartTxBuffer[len++] = 0xFF;
//
//	// Non-blocking Transmit via Interrupt
//	HAL_UART_Transmit_IT(&huart2, uartTxBuffer, len);

}


//void NEXTION_SendIntValue(char *ID, int value)
//{
//    char buffer[50];
//    int len = sprintf(buffer, "%s.val=%d", ID, value);
//    HAL_UART_Transmit(&huart2, (uint8_t*) buffer, len, 1000);
//    HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
//}

//void NEXTION_SendFloat(char *obj, float num, int dp)
//{
//    int32_t number = num * (pow(10, dp));
//
//    char buffer[30];
//    int len = sprintf(buffer, "%s.vvs1=%d", obj, dp);
//    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, 1000);
//    HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
//
//    len = sprintf(buffer, "%s.val=%ld", obj, number);
//    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, 1000);
//    HAL_UART_Transmit(&huart2, Cmd_End, 3, 100);
//}
