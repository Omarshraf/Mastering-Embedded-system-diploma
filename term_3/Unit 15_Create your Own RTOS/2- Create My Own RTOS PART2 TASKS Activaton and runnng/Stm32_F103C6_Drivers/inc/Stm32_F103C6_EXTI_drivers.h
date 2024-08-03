/*
 * Stm32_F103C6_drivers.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#ifndef INC_STM32_F103C6_EXTI_DRIVERS_H_
#define INC_STM32_F103C6_EXTI_DRIVERS_H_


//------------------------------------------------------------------
// Includes
//------------------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_drivers.h"


//------------------------------------------------------------------


//------------------------------------------------------------------
// configure structure
//------------------------------------------------------------------

typedef struct
{
	uint16_t				EXTI_INPUT_LINE_NUMBER;
	GPIO_TypeDef*		GPIO_PORT;
	uint16_t				GPIO_PIN;
	uint8_t					IVT_IRQ_Number;
}EXTI_GPIO_MAPING_t;

typedef struct
{
	EXTI_GPIO_MAPING_t		EXTI_PIN;			//Specifies the External interrupt GPIO mapping
												//this parameter must be set based on @ref EXTI_def

	uint8_t					Trigger_Case;		//Specifies Rising or Falling or Both trigger
												//this parameter must be set based on @ref EXTI_Trigger_def

	uint8_t					IRQ_EN;				//Enable or Disable the EXTI IRQ (that will enable the IRQ MASK in EXTI and Also on the NVIC Interrupt Controller)
												//this parameter must be set based on @ref EXTI_IRQ_def

	void(*P_IRQ_CallBack)(void);				//Set the C function() which will be called once the IRQ Happen

}EXTI_GPIO_PinConfig_t;




//------------------------------------------------------------------
// Macros Configuration References
//------------------------------------------------------------------


//EXTI Line Number
#define EXTI0									0
#define EXTI1									1
#define EXTI2									2
#define EXTI3									3
#define EXTI4									4
#define EXTI5									5
#define EXTI6									6
#define EXTI7									7
#define EXTI8									8
#define EXTI9									9
#define EXTI10									10
#define EXTI11									11
#define EXTI12									12
#define EXTI13									13
#define EXTI14									14
#define EXTI15									15
//-------------------------------------------------------------------


//@ref EXTI_define

//EXTI0
#define EXTIPA0									(EXTI_GPIO_MAPING_t){EXTI0 , GPIOA , GPIO_PIN_0 , EXTI0_IRQ}
#define EXTIPB0									(EXTI_GPIO_MAPING_t){EXTI0 , GPIOB , GPIO_PIN_0 , EXTI0_IRQ}
#define EXTIPC0									(EXTI_GPIO_MAPING_t){EXTI0 , GPIOC , GPIO_PIN_0 , EXTI0_IRQ}
#define EXTIPD0									(EXTI_GPIO_MAPING_t){EXTI0 , GPIOD , GPIO_PIN_0 , EXTI0_IRQ}

//EXTI1
#define EXTIPA1									(EXTI_GPIO_MAPING_t){EXTI1 , GPIOA , GPIO_PIN_1 , EXTI1_IRQ}
#define EXTIPB1									(EXTI_GPIO_MAPING_t){EXTI1 , GPIOB , GPIO_PIN_1 , EXTI1_IRQ}
#define EXTIPC1									(EXTI_GPIO_MAPING_t){EXTI1 , GPIOC , GPIO_PIN_1 , EXTI1_IRQ}
#define EXTIPD1									(EXTI_GPIO_MAPING_t){EXTI1 , GPIOD , GPIO_PIN_1 , EXTI1_IRQ}

//EXTI2
#define EXTIPA2									(EXTI_GPIO_MAPING_t){EXTI2 , GPIOA , GPIO_PIN_2 , EXTI2_IRQ}
#define EXTIPB2									(EXTI_GPIO_MAPING_t){EXTI2 , GPIOB , GPIO_PIN_2 , EXTI2_IRQ}
#define EXTIPC2									(EXTI_GPIO_MAPING_t){EXTI2 , GPIOC , GPIO_PIN_2 , EXTI2_IRQ}
#define EXTIPD2									(EXTI_GPIO_MAPING_t){EXTI2 , GPIOD , GPIO_PIN_2 , EXTI2_IRQ}

//EXTI3
#define EXTIPA3									(EXTI_GPIO_MAPING_t){EXTI3 , GPIOA , GPIO_PIN_3 , EXTI3_IRQ}
#define EXTIPB3									(EXTI_GPIO_MAPING_t){EXTI3 , GPIOB , GPIO_PIN_3 , EXTI3_IRQ}
#define EXTIPC3									(EXTI_GPIO_MAPING_t){EXTI3 , GPIOC , GPIO_PIN_3 , EXTI3_IRQ}
#define EXTIPD3									(EXTI_GPIO_MAPING_t){EXTI3 , GPIOD , GPIO_PIN_3 , EXTI3_IRQ}

//EXTI4
#define EXTIPA4									(EXTI_GPIO_MAPING_t){EXTI4 , GPIOA , GPIO_PIN_4 , EXTI4_IRQ}
#define EXTIPB4									(EXTI_GPIO_MAPING_t){EXTI4 , GPIOB , GPIO_PIN_4 , EXTI4_IRQ}
#define EXTIPC4									(EXTI_GPIO_MAPING_t){EXTI4 , GPIOC , GPIO_PIN_4 , EXTI4_IRQ}
#define EXTIPD4									(EXTI_GPIO_MAPING_t){EXTI4 , GPIOD , GPIO_PIN_4 , EXTI4_IRQ}

//EXTI5
#define EXTIPA5									(EXTI_GPIO_MAPING_t){EXTI5 , GPIOA , GPIO_PIN_5 , EXTI5_IRQ}
#define EXTIPB5									(EXTI_GPIO_MAPING_t){EXTI5 , GPIOB , GPIO_PIN_5 , EXTI5_IRQ}
#define EXTIPC5									(EXTI_GPIO_MAPING_t){EXTI5 , GPIOC , GPIO_PIN_5 , EXTI5_IRQ}
#define EXTIPD5									(EXTI_GPIO_MAPING_t){EXTI5 , GPIOD , GPIO_PIN_5 , EXTI5_IRQ}

//EXTI6
#define EXTIPA6									(EXTI_GPIO_MAPING_t){EXTI6 , GPIOA , GPIO_PIN_6 , EXTI6_IRQ}
#define EXTIPB6									(EXTI_GPIO_MAPING_t){EXTI6 , GPIOB , GPIO_PIN_6 , EXTI6_IRQ}
#define EXTIPC6									(EXTI_GPIO_MAPING_t){EXTI6 , GPIOC , GPIO_PIN_6 , EXTI6_IRQ}
#define EXTIPD6									(EXTI_GPIO_MAPING_t){EXTI6 , GPIOD , GPIO_PIN_6 , EXTI6_IRQ}

//EXTI7
#define EXTIPA7									(EXTI_GPIO_MAPING_t){EXTI7 , GPIOA , GPIO_PIN_7 , EXTI7_IRQ}
#define EXTIPB7									(EXTI_GPIO_MAPING_t){EXTI7 , GPIOB , GPIO_PIN_7 , EXTI7_IRQ}
#define EXTIPC7									(EXTI_GPIO_MAPING_t){EXTI7 , GPIOC , GPIO_PIN_7 , EXTI7_IRQ}
#define EXTIPD7									(EXTI_GPIO_MAPING_t){EXTI7 , GPIOD , GPIO_PIN_7 , EXTI7_IRQ}

//EXTI8
#define EXTIPA8									(EXTI_GPIO_MAPING_t){EXTI8 , GPIOA , GPIO_PIN_8 , EXTI8_IRQ}
#define EXTIPB8									(EXTI_GPIO_MAPING_t){EXTI8 , GPIOB , GPIO_PIN_8 , EXTI8_IRQ}
#define EXTIPC8									(EXTI_GPIO_MAPING_t){EXTI8 , GPIOC , GPIO_PIN_8 , EXTI8_IRQ}
#define EXTIPD8									(EXTI_GPIO_MAPING_t){EXTI8 , GPIOD , GPIO_PIN_8 , EXTI8_IRQ}

//EXTI9
#define EXTIPA9									(EXTI_GPIO_MAPING_t){EXTI9 , GPIOA , GPIO_PIN_9 , EXTI9_IRQ}
#define EXTIPB9									(EXTI_GPIO_MAPING_t){EXTI9 , GPIOB , GPIO_PIN_9 , EXTI9_IRQ}
#define EXTIPC9									(EXTI_GPIO_MAPING_t){EXTI9 , GPIOC , GPIO_PIN_9 , EXTI9_IRQ}
#define EXTIPD9									(EXTI_GPIO_MAPING_t){EXTI9 , GPIOD , GPIO_PIN_9 , EXTI9_IRQ}

//EXTI10
#define EXTIPA10								(EXTI_GPIO_MAPING_t){EXTI10 , GPIOA , GPIO_PIN_10 , EXTI10_IRQ}
#define EXTIPB10								(EXTI_GPIO_MAPING_t){EXTI10 , GPIOB , GPIO_PIN_10 , EXTI10_IRQ}
#define EXTIPC10								(EXTI_GPIO_MAPING_t){EXTI10 , GPIOC , GPIO_PIN_10 , EXTI10_IRQ}
#define EXTIPD10								(EXTI_GPIO_MAPING_t){EXTI10 , GPIOD , GPIO_PIN_10 , EXTI10_IRQ}

//EXTI11
#define EXTIPA11								(EXTI_GPIO_MAPING_t){EXTI11 , GPIOA , GPIO_PIN_11 , EXTI11_IRQ}
#define EXTIPB11								(EXTI_GPIO_MAPING_t){EXTI11 , GPIOB , GPIO_PIN_11 , EXTI11_IRQ}
#define EXTIPC11								(EXTI_GPIO_MAPING_t){EXTI11 , GPIOC , GPIO_PIN_11 , EXTI11_IRQ}
#define EXTIPD11								(EXTI_GPIO_MAPING_t){EXTI11 , GPIOD , GPIO_PIN_11 , EXTI11_IRQ}

//EXTI12
#define EXTIPA12								(EXTI_GPIO_MAPING_t){EXTI12 , GPIOA , GPIO_PIN_12 , EXTI12_IRQ}
#define EXTIPB12								(EXTI_GPIO_MAPING_t){EXTI12 , GPIOB , GPIO_PIN_12 , EXTI12_IRQ}
#define EXTIPC12								(EXTI_GPIO_MAPING_t){EXTI12 , GPIOC , GPIO_PIN_12 , EXTI12_IRQ}
#define EXTIPD12								(EXTI_GPIO_MAPING_t){EXTI12 , GPIOD , GPIO_PIN_12 , EXTI12_IRQ}

//EXTI13
#define EXTIPA13								(EXTI_GPIO_MAPING_t){EXTI13 , GPIOA , GPIO_PIN_13 , EXTI13_IRQ}
#define EXTIPB13								(EXTI_GPIO_MAPING_t){EXTI13 , GPIOB , GPIO_PIN_13 , EXTI13_IRQ}
#define EXTIPC13								(EXTI_GPIO_MAPING_t){EXTI13 , GPIOC , GPIO_PIN_13 , EXTI13_IRQ}
#define EXTIPD13								(EXTI_GPIO_MAPING_t){EXTI13 , GPIOD , GPIO_PIN_13 , EXTI13_IRQ}

//EXTI14
#define EXTIPA14								(EXTI_GPIO_MAPING_t){EXTI14 , GPIOA , GPIO_PIN_14 , EXTI14_IRQ}
#define EXTIPB14								(EXTI_GPIO_MAPING_t){EXTI14 , GPIOB , GPIO_PIN_14 , EXTI14_IRQ}
#define EXTIPC14								(EXTI_GPIO_MAPING_t){EXTI14 , GPIOC , GPIO_PIN_14 , EXTI14_IRQ}
#define EXTIPD14								(EXTI_GPIO_MAPING_t){EXTI14 , GPIOD , GPIO_PIN_14 , EXTI14_IRQ}

//EXTI15
#define EXTIPA15								(EXTI_GPIO_MAPING_t){EXTI15 , GPIOA , GPIO_PIN_15 , EXTI15_IRQ}
#define EXTIPB15								(EXTI_GPIO_MAPING_t){EXTI15 , GPIOB , GPIO_PIN_15 , EXTI15_IRQ}
#define EXTIPC15								(EXTI_GPIO_MAPING_t){EXTI15 , GPIOC , GPIO_PIN_15 , EXTI15_IRQ}
#define EXTIPD15								(EXTI_GPIO_MAPING_t){EXTI15 , GPIOD , GPIO_PIN_15 , EXTI15_IRQ}



// @ref EXTI_Trigger_def

#define EXTI_Trigger_Rising						0
#define EXTI_Trigger_Falling					1
#define EXTI_Trigger_RisingAndFalling			2

//@ref EXTI_IRQ_def

#define EXTI_IRQ_Enable							1
#define EXTI_IRQ_Disable						0






//------------------------------------------------------------------
//					 APIs Supported by "MCAL GPIO DRIVER"
//------------------------------------------------------------------

void MCAL_EXTI_GPIO_Init(EXTI_GPIO_PinConfig_t* EXTI_CONFIG);
void MCAL_EXTI_GPIO_DeInit(void);
void MCAL_EXTI_GPIO_Update(EXTI_GPIO_PinConfig_t* EXTI_CONFIG);



#endif /* INC_STM32_F103C6_EXTI_DRIVERS_H_ */
