/*
 * hx711.c
 *
 *  Created on: Apr 22, 2025
 *      Author: Florian
 */

#include "hx711.h"

static GPIO_TypeDef* HX711_DT_Port;
static uint16_t HX711_DT_Pin;
static GPIO_TypeDef* HX711_SCK_Port;
static uint16_t HX711_SCK_Pin;

int32_t offset = 0;
float scale = 1.0f;

void HX711_Init(GPIO_TypeDef* dt_port, uint16_t dt_pin, GPIO_TypeDef* sck_port, uint16_t sck_pin)
{
    HX711_DT_Port = dt_port;
    HX711_DT_Pin = dt_pin;
    HX711_SCK_Port = sck_port;
    HX711_SCK_Pin = sck_pin;
}

int32_t HX711_Read(void) {
    int32_t count = 0;
    uint8_t i;

    while (HAL_GPIO_ReadPin(HX711_DT_Port, HX711_DT_Pin));

    for (i = 0; i < 24; i++)
    {
        HAL_GPIO_WritePin(HX711_SCK_Port, HX711_SCK_Pin, GPIO_PIN_SET);
        count <<= 1;
        HAL_GPIO_WritePin(HX711_SCK_Port, HX711_SCK_Pin, GPIO_PIN_RESET);
        if (HAL_GPIO_ReadPin(HX711_DT_Port, HX711_DT_Pin)) count++;
    }

    HAL_GPIO_WritePin(HX711_SCK_Port, HX711_SCK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HX711_SCK_Port, HX711_SCK_Pin, GPIO_PIN_RESET);

    if (count & 0x800000) count |= 0xFF000000;
    return count;
}

float HX711_Read_Average(uint8_t anzahl)
{
    int64_t summe = 0;
    for (uint8_t i = 0; i < anzahl; i++) {
        summe += HX711_Read();
        osDelay(1);
    }
    return summe / (float)anzahl;
}

void HX711_Tare(void)
{
    offset = (int32_t)HX711_Read_Average(50); // 50 Samples für stabilen Offset
}

void HX711_Calibrate(float referenzGewicht)
{
    int32_t rohwert = (int32_t)HX711_Read_Average(50); // 50 Samples für stabile Mittelung
    if (referenzGewicht > 0.001f) {
        scale = (float)(rohwert - offset) / referenzGewicht;
    } else {
        scale = 1.0f;
    }
}

