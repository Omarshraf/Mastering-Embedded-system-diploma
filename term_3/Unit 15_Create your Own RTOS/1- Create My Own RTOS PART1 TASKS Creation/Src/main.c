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

#include "stm32f103x6.h"
#include "Stm32_F103C6_EXTI_drivers.h"
#include "Stm32_F103C6_gpio_drivers.h"
#include "KEY_PAD.h"
#include "LCD.h"
#include "core_cm3.h"
#include "scheduler.h"

void HW_init();
Task_ref Task1, Task2, Task3;

void task1()
{
	while(1)
	{
		//Task1 Code
	}
}

void task2()
{
	while(1)
	{
		//Task1 Code
	}
}

void task3()
{
	while(1)
	{
		//Task1 Code
	}
}
int main(void)
{
	MY_RTOS_ErrorID error = 0;

	//HW_init (Initialize ClockTree, ResetController )
	HW_init();

	if(MY_RTOS_init() != NoError)
		while (1);

	Task1.stack_size = 1024;
	Task1.priority =3;
	Task1.p_TaskEntry = task1;
	strcpy(Task1.Task_Name , "task1");

	Task2.stack_size = 1024;
	Task2.priority =3;
	Task2.p_TaskEntry = task2;
	strcpy(Task1.Task_Name , "task2");

	Task3.stack_size = 1024;
	Task3.priority =3;
	Task3.p_TaskEntry = task3;
	strcpy(Task1.Task_Name , "task3");

	error += MY_RTOS_Creat_Task(&Task1);
	error += MY_RTOS_Creat_Task(&Task2);
	error += MY_RTOS_Creat_Task(&Task3);


	while (1)
	{

	}
}
