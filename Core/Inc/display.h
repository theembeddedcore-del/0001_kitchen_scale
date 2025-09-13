/*
 * display.h
 *
 *  Created on: Apr 23, 2025
 *      Author: Florian
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

void NEXTION_SendString(char *ID, char *string);
//void NEXTION_SendIntValue(char *ID, int value);
//void NEXTION_SendFloat (char *obj, float num, int dp);

#endif /* INC_DISPLAY_H_ */
