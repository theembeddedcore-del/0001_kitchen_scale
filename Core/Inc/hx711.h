/*
 * hx711.h
 *
 *  Created on: Apr 22, 2025
 *      Author: Florian
 */

#ifndef INC_HX711_H_
#define INC_HX711_H_

#include "stm32f4xx_hal.h"

void HX711_Init(GPIO_TypeDef* dt_port, uint16_t dt_pin, GPIO_TypeDef* sck_port, uint16_t sck_pin);
int32_t HX711_Read(void);
float HX711_Read_Average(uint8_t anzahl);
void HX711_Tare(void);
void HX711_Calibrate(float referenzGewicht);

#endif /* INC_HX711_H_ */
