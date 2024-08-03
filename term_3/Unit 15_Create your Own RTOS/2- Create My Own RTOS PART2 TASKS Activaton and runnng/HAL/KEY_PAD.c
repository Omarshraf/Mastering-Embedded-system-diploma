/*
 * KEY_PAD.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Omar
 */

#include "KEY_PAD.h"

int Row[]={R0,R1,R2,R3};
int Column[]={C0,C1,C2,C3};


void delay_mss(uint32_t time)
{
	uint32_t i,j;
	for (i = 0; i < time; ++i)
		for (j = 0; j < 255; ++j);
}

void Keypad_init()
{
	PINCONFIG.GPIO_PinNumber = R0;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = R1;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = R2;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = R3;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = C0;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = C1;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = C2;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	PINCONFIG.GPIO_PinNumber = C3;
	PINCONFIG.GPIO_MODE = GPIO_MODE_OUTPT_PP ;
	PINCONFIG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PINCONFIG);

	MCAL_GPIO_WritePort(KEYPAD_PORT, 0XFF);
}




char Keypad_getkey()
{
	int i,j;
	for (i = 0; i < 4; ++i) {
		MCAL_GPIO_WritePin(KEYPAD_PORT, Column[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Column[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Column[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Column[3], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Column[i], GPIO_PIN_RESET);
		for (j = 0; j < 4; ++j) {
			if(MCAL_GPIO_ReadPin(KEYPAD_PORT, Row[j]) == 0)
			{
				while(MCAL_GPIO_ReadPin(KEYPAD_PORT, Row[j]) == 0);
				switch(i)
				{
				case (0):
					if(j == 0)
						return '7';
					else if (j == 1)
						return '4';
					else if (j == 2)
						return '1';
					else if (j == 3)
						return '?';
					break;
				case (1):
					if(j == 0)
						return '8';
					else if (j == 1)
						return '5';
					else if (j == 2)
						return '2';
					else if (j == 3)
						return '0';
					break;
				case (2):
					if(j == 0)
						return '9';
					else if (j == 1)
						return '6';
					else if (j == 2)
						return '3';
					else if (j == 3)
						return '=';
					break;
				case (3):
					if(j == 0)
						return '/';
					else if (j == 1)
						return '*';
					else if (j == 2)
						return '-';
					else if (j == 3)
						return '+';
					break;

				}
			}
		}

	}
	return 'E';
}




