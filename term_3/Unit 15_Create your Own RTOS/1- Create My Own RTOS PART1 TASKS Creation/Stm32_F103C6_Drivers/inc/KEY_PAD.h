/*
 * KEY_PAD.h
 *
 *  Created on: Jul 10, 2023
 *      Author: Omar
 */

#ifndef INC_KEY_PAD_H_
#define INC_KEY_PAD_H_


#include "Stm32_F103C6_gpio_drivers.h"
#include "stm32f103x6.h"

#define KEYPAD_PORT					GPIOB
//Rows
#define R0							GPIO_PIN_0
#define R1							GPIO_PIN_1
#define R2							GPIO_PIN_3
#define R3							GPIO_PIN_4
//Columns
#define C0							GPIO_PIN_5
#define C1							GPIO_PIN_6
#define C2							GPIO_PIN_7
#define C3							GPIO_PIN_8


GPIO_PinConfig_t PINCONFIG;

// APIs
void Keypad_init();
char Keypad_getkey();



#endif /* INC_KEY_PAD_H_ */
