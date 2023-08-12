/*
 * Stm32_F103C6_drivers.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#ifndef INC_STM32_F103C6_RCC_DRIVERS_H_
#define INC_STM32_F103C6_RCC_DRIVERS_H_


//------------------------------------------------------------------
// Includes
//------------------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_drivers.h"


//------------------------------------------------------------------

#define HSI_RC_Clk					(uint32_t)8000000
#define HSE_Clock					(uint32_t)16000000


uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);

#endif /* INC_STM32_F103C6_RCC_DRIVERS_H_ */
