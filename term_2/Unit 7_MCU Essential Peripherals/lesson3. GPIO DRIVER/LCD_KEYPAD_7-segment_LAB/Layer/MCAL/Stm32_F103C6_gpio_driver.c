/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#include "Stm32_F103C6_gpio_drivers.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case(GPIO_PIN_0):
			return 0;
			break;
	case(GPIO_PIN_1):
			return 4;
			break;
	case(GPIO_PIN_2):
			return 8;
			break;
	case(GPIO_PIN_3):
			return 12;
			break;
	case(GPIO_PIN_4):
			return 16;
			break;
	case(GPIO_PIN_5):
			return 20;
			break;
	case(GPIO_PIN_6):
			return 24;
			break;
	case(GPIO_PIN_7):
			return 28;
			break;
	case(GPIO_PIN_8):
			return 0;
			break;
	case(GPIO_PIN_9):
			return 4;
			break;
	case(GPIO_PIN_10):
			return 8;
			break;
	case(GPIO_PIN_11):
			return 12;
			break;
	case(GPIO_PIN_12):
			return 16;
			break;
	case(GPIO_PIN_13):
			return 20;
			break;
	case(GPIO_PIN_14):
			return 24;
			break;
	case(GPIO_PIN_15):
			return 28;
			break;

	}
	return 0;
}


/*=======================================================================
 * @Fn				- MCAL_GPIO_Init
 * @brief			- initializes GPIOx PINy according to the specified parameters in PinConfig
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @parameter[in]	- PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 						the configuration information for the specified GPIO PIN
 * @retval			- none
 * Note				- STN32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 						but LQFP48 Package has only GPIO A,B,Part of C/D exported as external PINs from the MCU
 */
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	// Port configuration register low (GPIOxCRL) Config Pins Form 0>>>>7
	// Port configuration register high (GPIOxCRH) Config Pins Form 8>>>>15
	volatile uint32_t* configregister =NULL;
	uint8_t PIN_Config = 0;
	configregister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNFy & MODEy (4 bits)
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));


	//if pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_OUTPT_AF_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPT_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPT_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPT_PP))
	{
		//set CNFy & MODEy (4 bits)
		PIN_Config = ((((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_OUTPUT_SPEED)) & 0x0f);

	}
	//if pin is input
	else //MODE = 00: Input Mode (reset state)
	{
		if ((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) ||(PinConfig->GPIO_MODE == GPIO_MODE_Analog) )
		{
			//set CNFy & MODEy00 (4 bits)
			PIN_Config = ((((PinConfig->GPIO_MODE) << 2) | 0x0) & 0x0f);
		}
		else if (PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT) //consider it as input floating
		{
			//set CNFy & MODEy00 (4 bits)
			PIN_Config = ((((GPIO_MODE_INPUT_FLO) << 2) | 0x0) & 0x0f);

		}
		else //PU or PD input
		{
			PIN_Config = ((((GPIO_MODE_INPUT_PU) << 2) | 0x0) & 0x0f);
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				// Table 20. Port bit configuration table PxODR>> 1 (input Pull-Up)
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				// Table 20. Port bit configuration table PxODR>> 0 (input Pull-Down)
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);

			}

		}
	}
	//write on the CRL or CRH
	(*configregister) |= (PIN_Config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );


}


/*=======================================================================
 * @Fn				- MCAL_GPIO_DeInit
 * @brief			- Reset all the GPIO Register
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @retval			- none
 * Note				- none
 */
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx)
{
	/*METHOD 1
	GPIOx->BRR = 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->CRH = 0x44444444;
	GPIOx->CRL = 0x44444444;
	GPIOx->IDR  (read only);
	GPIOx->LCKR = 0x00000000;
	GPIOx->ODR = 0x00000000;
	*/

	//METHOD 2
	// you can use the reset controller
	// APB2 peripheral reset register (RCC_APB2RSTR)
	//Set and cleared by software.

	if (GPIOx == GPIOA)
	{
		//Bit 2 IOPARST: IO PORT A reset
		//to reset the port >>>> set and reset the bit
		RCC->APB2ENR |= (1<<2);
		RCC->APB2ENR &= ~(1<<2);
	}
	if (GPIOx == GPIOB)
		{
			//Bit 3 IOPARST: IO PORT B reset
			//to reset the port >>>> set and reset the bit
			RCC->APB2ENR |= (1<<3);
			RCC->APB2ENR &= ~(1<<3);
		}
	if (GPIOx == GPIOC)
		{
			//Bit 4 IOPARST: IO PORT C reset
			//to reset the port >>>> set and reset the bit
			RCC->APB2ENR |= (1<<4);
			RCC->APB2ENR &= ~(1<<4);
		}
	if (GPIOx == GPIOD)
		{
			//Bit 5 IOPARST: IO PORT D reset
			//to reset the port >>>> set and reset the bit
			RCC->APB2ENR |= (1<<5);
			RCC->APB2ENR &= ~(1<<5);
		}
	if (GPIOx == GPIOE)
		{
			//Bit 6 IOPARST: IO PORT E reset
			//to reset the port >>>> set and reset the bit
			RCC->APB2ENR |= (1<<6);
			RCC->APB2ENR &= ~(1<<6);
		}




}




/*=======================================================================
 * @Fn				- MCAL_GPIO_ReadPin
 * @brief			- Read Specific PIN
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @parameter[in]	- PinNumber: set Pin Number according to @ref GPIO_PINS_define
 * @retval			- the input pin value (two values based on @ref GPIO_PIN_state)
 * Note				- none
 */

uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	uint8_t bitstatus;
	if((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}



/*=======================================================================
 * @Fn				- MCAL_GPIO_ReadPort
 * @brief			- Read Specific Port
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @retval			- the input Port value
 * Note				- none
 */
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx)
{
	uint16_t PortValue;
	PortValue = (uint16_t)(GPIOx->IDR);
	return PortValue;
}


/*=======================================================================
 * @Fn				- MCAL_GPIO_WritePin
 * @brief			- Writeon Specific Pin
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @parameter[in]	- PinNumber: set Pin Number according to @ref GPIO_PINS_define
 * @parameter[in]	- Value:Pin Value
 * @retval			- none
 * Note				- none
 */
void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	 if (Value != GPIO_PIN_RESET)
	 {
		 GPIOx->ODR |= PinNumber;
	 }
	 else
	 {
		 GPIOx->ODR &= ~ PinNumber;

	 }
}


/*=======================================================================
 * @Fn				- MCAL_GPIO_WritePort
 * @brief			- Write on Specific Port
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @parameter[in]	- Value:Pin Value
 * @retval			- none
 * Note				- none
 */
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t) Value;
}


/*=======================================================================
 * @Fn				- MCAL_GPIO_TogglePin
 * @brief			- Toggle Specific Pin
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @parameter[in]	- PinNumber: set Pin Number according to @ref GPIO_PINS_define
 * @retval			- none
 * Note				- none
 */
void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);

}

/*=======================================================================
 * @Fn				- MCAL_GPIO_LockPin
 * @brief			- the Locking mechanism allows the IO configuration to be frozen
 * @parameter[in]	- GPIOx: where x can be (A>>E depending on device used) to select the GPIO peripheral
 * @parameter[in]	- PinNumber: set Pin Number according to @ref GPIO_PINS_define
 * @retval			- OK if pin config is locked or ERROR if pin not locked (OK & ERROR are defined @ref LOCK_RETURN)
 * Note				- none
 */
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
/*
Bit 16 LCKK[16]: Lock key
This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
0: Port configuration lock key not active
1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
LOCK key writing sequence:
Write 1
Write 0
Write 1
Read 0
Read 1 (this read is optional but confirms that the lock is active)
Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
Any error in the lock sequence will abort the lock.
Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
These bits are read write but can only be written when the LCKK bit is 0.
0: Port configuration not locked
1: Port configuration locked.
*/
	//set LCKK[16]
	volatile uint32_t temp = 1<<16;
	//set the LCKy
	temp |= PinNumber;

	// Write 1
	GPIOx->LCKR = temp;
	// Write 0
	GPIOx->LCKR = PinNumber;
	//Write 1
	GPIOx->LCKR = temp;
	// Read 0
	temp = GPIOx->LCKR;
	// Read 1
	if ((uint32_t)(GPIOx->LCKR & 1<<16))
		return LOCK_RETURN_Enabled;
	else
		return LOCK_RETURN_ERROR;

}




