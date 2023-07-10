/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


//==============================================
// Example Application on unit7_lesson1 Lab1
//==============================================
#include "stm32f103x6.h"
#include <Stm32_F103C6_gpio_drivers.h>

void clock_init()
{
	//Enable clock GPIOA
	RCC_GPIOA_CLK_EN();
	//Enable clock GPIOB
	RCC_GPIOB_CLK_EN();
}

void GPIO_init()
{
	GPIO_PinConfig_t PinConfig;

	//PA1 input High-Z Floating input
	PinConfig.GPIO_PinNumber =GPIO_PIN_1;
	PinConfig.GPIO_MODE =GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &PinConfig);

	// PB1 (output PUSH-PULL MODE)
	PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPT_PP;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	//=================================================

	//PA13 input Hi-Z
	PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &PinConfig);

	//PB13 open-drain
	PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPT_OD;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

}

void wait_ms(uint32_t time)
{
	uint32_t i,j;
	for(i = 0 ; i < time ; i++)
		for(j=0 ; j < 255 ; j++);
}


int main(void)
{
	clock_init();
	GPIO_init();
	while(1)
	{
		//PA1 >>>> conected external PUR
		if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) //pressed
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			while (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0); //single press
		}
		//PA1 >>>> conected external PUR
		if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1) //pressed
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13); // Multi pressing
		}
		wait_ms(2);
	}
}
