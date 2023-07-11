/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#include "Stm32_F103C6_EXTI_drivers.h"

//=======================================================================
//                               Generic Variable
//=======================================================================

void(* GP_IRQ_CallBack[15])(void);


//=======================================================================
//                               Generic Macros
//=======================================================================
#define AFIO_GPIO_EXTIMapping(x)		 (	 (x==GPIOA) ? 0 : \
											 (x==GPIOB) ? 1 : \
											 (x==GPIOC) ? 2 : \
											 (x==GPIOD) ? 3 : 0	)



//=======================================================================
//                               Generic Function
//=======================================================================
void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;



	}

}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;



	}

}




void Update_EXTI(EXTI_GPIO_PinConfig_t* EXTI_CONFIG)
{
	//1- Configure GPIO TO be AF Input ->>> Floating INPUT

	GPIO_PinConfig_t PINCONFiG;
	//Update the GPIO Pin To be Floating Input
	PINCONFiG.GPIO_PinNumber =EXTI_CONFIG ->EXTI_PIN.GPIO_PIN;
	PINCONFiG.GPIO_MODE=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_CONFIG->EXTI_PIN.GPIO_PORT, &PINCONFiG);
	//============================================================

	//2- Update AFIO to Route between EXTI Line with PORT A,B,C,D

	uint8_t AFIO_EXTICR_index = EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER /4;
	uint8_t AFIO_EXTICR_Position = (EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER % 4) * 4;

	//Clear the four bit
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_Position);
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTIMapping(EXTI_CONFIG->EXTI_PIN.GPIO_PORT) &0xF) << AFIO_EXTICR_Position);


	//3- Update Rising or Falling Register
	//Clear both registers
	EXTI->RTSR &= ~(1 << EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);
	EXTI->FTSR &= ~(1 << EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);

	if(EXTI_CONFIG->Trigger_Case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1 << EXTI_CONFIG ->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);

	}else if(EXTI_CONFIG->Trigger_Case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1 << EXTI_CONFIG ->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);

	}else if(EXTI_CONFIG->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1 << EXTI_CONFIG ->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);
		EXTI->FTSR |= (1 << EXTI_CONFIG ->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);

	}

	//====================================================================
	//4- Update IRQ Handling CallBack
	GP_IRQ_CallBack[EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER] = EXTI_CONFIG->P_IRQ_CallBack;

	//5- Enable/Disable IRQ EXTI & NVIC
	if(EXTI_CONFIG->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI ->IMR |= (1<< EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);
		Enable_NVIC(EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);
	}else
	{
		EXTI ->IMR &= ~(1<< EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);
		Disable_NVIC(EXTI_CONFIG->EXTI_PIN.EXTI_INPUT_LINE_NUMBER);
	}

}



/*=======================================================================
 * @Fn				- MCAL_EXTI_GPIO_Init
 * @brief			- reset EXTI Register and NVIC Corresponding IRQ MASK
 * @retval			- none
 * Note				- none
 */

void MCAL_EXTI_GPIO_DeInit(void){

	EXTI->EMR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->IMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;

	//CLEARD BY writing a '1' into the PR
	EXTI->PR = 0xFFFFFFFF;

	//Disable EXTI IQR From NVIC
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;
}


/*=======================================================================
 * @Fn				- MCAL_EXTI_GPIO_DeInit
 * @brief			- this is used to initialize EXTI From Specific GPIO PIN and specify the MAsk /
 * @parameter[in]	- EXTI_CONFIG set by @ref EXTI_def, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval			- none
 * Note				- STN32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 						but LQFP48 Package has only GPIO A,B,Part of C/D exported as external PINs from the MCU
 * 					- Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
 */
void MCAL_EXTI_GPIO_Init(EXTI_GPIO_PinConfig_t* EXTI_CONFIG)
{
	Update_EXTI(EXTI_CONFIG);
}

/*=======================================================================
 * @Fn				- MCAL_EXTI_GPIO_Update
 * @brief			- this is used to Update EXTI From Specific GPIO PIN and specify the MAsk /
 * @parameter[in]	- EXTI_CONFIG set by @ref EXTI_def, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval			- none
 * Note				- STN32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 						but LQFP48 Package has only GPIO A,B,Part of C/D exported as external PINs from the MCU
 * 					- Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
 */

void MCAL_EXTI_GPIO_Update(EXTI_GPIO_PinConfig_t* EXTI_CONFIG)
{
	Update_EXTI(EXTI_CONFIG);
}


//=======================================================================
// 							 ISR Functions
//=======================================================================

void EXTI0_IRQHandler (void)
{
	EXTI->PR |= (1<<0);
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler (void)
{
	EXTI->PR |= (1<<1);
	GP_IRQ_CallBack[1]();

}

void EXTI2_IRQHandler (void)
{
	EXTI->PR |= (1<<2);
	GP_IRQ_CallBack[2]();

}

void EXTI3_IRQHandler (void)
{
	EXTI->PR |= (1<<3);
	GP_IRQ_CallBack[3]();

}

void EXTI4_IRQHandler (void)
{
	EXTI->PR |= (1<<4);
	GP_IRQ_CallBack[4]();

}

void EXTI9_5_IRQHandler (void)
{
	if (EXTI->PR & 1<<5)	{EXTI->PR |= (1<<5);	GP_IRQ_CallBack[5]();}
	if (EXTI->PR & 1<<6)	{EXTI->PR |= (1<<6);	GP_IRQ_CallBack[6]();}
	if (EXTI->PR & 1<<7)	{EXTI->PR |= (1<<7);	GP_IRQ_CallBack[7]();}
	if (EXTI->PR & 1<<8)	{EXTI->PR |= (1<<8);	GP_IRQ_CallBack[8]();}
	if (EXTI->PR & 1<<9)	{EXTI->PR |= (1<<9);	GP_IRQ_CallBack[9]();}

}

void EXTI15_10_IRQHandler (void)
{
	if (EXTI->PR & 1<<10)	{EXTI->PR |= (1<<10);	GP_IRQ_CallBack[10]();}
	if (EXTI->PR & 1<<11)	{EXTI->PR |= (1<<11);	GP_IRQ_CallBack[11]();}
	if (EXTI->PR & 1<<12)	{EXTI->PR |= (1<<12);	GP_IRQ_CallBack[12]();}
	if (EXTI->PR & 1<<13)	{EXTI->PR |= (1<<13);	GP_IRQ_CallBack[13]();}
	if (EXTI->PR & 1<<14)	{EXTI->PR |= (1<<14);	GP_IRQ_CallBack[14]();}
	if (EXTI->PR & 1<<15)	{EXTI->PR |= (1<<15);	GP_IRQ_CallBack[15]();}

}






