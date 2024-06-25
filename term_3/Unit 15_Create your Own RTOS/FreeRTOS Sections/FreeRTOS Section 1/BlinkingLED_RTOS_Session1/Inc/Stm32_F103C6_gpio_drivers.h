/*
 * Stm32_F103C6_drivers.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVERS_H_
#define INC_STM32_F103C6_GPIO_DRIVERS_H_


//------------------------------------------------------------------
// Includes
//------------------------------------------------------------------
#include "stm32f103x6.h"


//------------------------------------------------------------------


//------------------------------------------------------------------
// configure structure
//------------------------------------------------------------------

typedef struct{
	uint16_t GPIO_PinNumber;	    // specifies the GPIO pins to be configured
									// this parameter must be set based on @ref GPIO_PINS_define


	uint8_t GPIO_MODE;			 	// specifies the operating mode for the selected pin
									// this parameter must be set based on @ref GPIO_MODE_define

	uint8_t GPIO_OUTPUT_SPEED;	    // specifies the speed for the selected pin
									// this parameter must be set based on @ref GPIO_SPEED_define



}GPIO_PinConfig_t;


//------------------------------------------------------------------
// Macros Configuration References
//------------------------------------------------------------------


//@ref GPIO_PINS_define
#define GPIO_PIN_0						((uint16_t)0x0001) /* Pin 0 selected   */
#define GPIO_PIN_1						((uint16_t)0x0002) /* Pin 1 selected   */  /*this hex is equivalent to 10 in binary     */
#define GPIO_PIN_2						((uint16_t)0x0004) /* Pin 2 selected   */  /*this hex is equivalent to100 in binary     */
#define GPIO_PIN_3						((uint16_t)0x0008) /* Pin 3 selected   */  /*this hex is equivalent to1000 in binary    */
#define GPIO_PIN_4						((uint16_t)0x0010) /* Pin 4 selected   */  /*this hex is equivalent to10000 in binary   */
#define GPIO_PIN_5						((uint16_t)0x0020) /* Pin 5 selected   */
#define GPIO_PIN_6						((uint16_t)0x0040) /* Pin 6 selected   */
#define GPIO_PIN_7						((uint16_t)0x0080) /* Pin 7 selected   */
#define GPIO_PIN_8						((uint16_t)0x0100) /* Pin 8 selected   */
#define GPIO_PIN_9						((uint16_t)0x0200) /* Pin 9 selected   */
#define GPIO_PIN_10						((uint16_t)0x0400) /* Pin 10 selected  */
#define GPIO_PIN_11						((uint16_t)0x0800) /* Pin 11 selected  */
#define GPIO_PIN_12						((uint16_t)0x1000) /* Pin 12 selected  */  /* this like (1<<12) */
#define GPIO_PIN_13						((uint16_t)0x2000) /* Pin 13 selected  */
#define GPIO_PIN_14						((uint16_t)0x4000) /* Pin 14 selected  */
#define GPIO_PIN_15						((uint16_t)0x8000) /* Pin 15 selected  */
#define GPIO_PIN_All					((uint16_t)0xFFFF) /* All Pins selected*/

#define GPIO_PIN_MASK					0x0000FFFFu		   /* PIN mask for assert test*/



//@ref GPIO_MODE_define
/*0: Analog mode
  1: Floating input (reset state)
  2: Input with pull-up
  3: pull-down
  4: General purpose output push-pull
  5: General purpose output Open-drain
  6: Alternate function output Push-pull
  7: Alternate function output Open-drain
  8: Alternate function input
*/
#define  GPIO_MODE_Analog				0x00000000u  // Analog mode
#define  GPIO_MODE_INPUT_FLO  	0x00000001u  // Floating input mode
#define  GPIO_MODE_INPUT_PU 		0x00000002u  // Input with pull-up mode
#define  GPIO_MODE_INPUT_PD			0x00000003u  // pull-down mode
#define  GPIO_MODE_OUTPT_PP			0x00000004u  // General purpose output push-pull mode
#define  GPIO_MODE_OUTPT_OD			0x00000005u  // General purpose output Open-drain mode
#define  GPIO_MODE_OUTPT_AF_PP	0x00000006u  // Alternate function output Push-pull mode
#define  GPIO_MODE_OUTPT_AF_OD	0x00000007u  // Alternate function output Open-drain mode
#define  GPIO_MODE_AF_INPUT			0x00000008u  // Alternate function input mode



//@ref GPIO_SPEED_define
/* 1: Output mode, max speed 10 MHz
 * 2: Output mode, max speed 2 MHz
 * 3: Output mode, max speed 50 MHz
 */

#define GPIO_SPEED_10M		    	0x00000001u  // Output mode, max speed 10 MHz
#define GPIO_SPEED_2M				   	0x00000002u  // Output mode, max speed 2 MHz
#define GPIO_SPEED_50M				  0x00000003u  // Output mode, max speed 50 MHz

//@ref GPIO_PIN_state
#define GPIO_PIN_SET					  1
#define GPIO_PIN_RESET				  0



//@ref LOCK_RETURN
#define LOCK_RETURN_Enabled	  	1
#define LOCK_RETURN_ERROR	  		0






//------------------------------------------------------------------
//					 APIs Supported by "MCAL GPIO DRIVER"
//------------------------------------------------------------------

void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);










#endif /* INC_STM32_F103C6_GPIO_DRIVERS_H_ */
