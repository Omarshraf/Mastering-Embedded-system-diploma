/*
 * Stm32_F103C6_drivers.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#ifndef INC_STM32_F103C6_UART_DRIVERS_H_
#define INC_STM32_F103C6_UART_DRIVERS_H_


//------------------------------------------------------------------
// Includes
//------------------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_drivers.h"
#include "Stm32_F103C6_RCC_drivers.h"
//------------------------------------------------------------------



//------------------------------------------------------------------
// Configuration structure
//------------------------------------------------------------------
typedef struct
{
	uint8_t 								Mode; //specifies TX/RX Enable/Disable
														//This parameter must be set based on @ref UART_Mode_define

	uint8_t 								BaudRate; //This member configures the UART communication baud_rate
															//This parameter must be set based on @ref UART_BaudRate_define

	uint8_t 								Payload_length; //This member specifies the number of data bits transmitted or received in frame.
																//This parameter must be set based on @ref UART_Payload_length_define

	uint8_t 								Parity; //This member specifies the Parity mode.
														//This parameter must be set based on @ref UART_Parity_define

	uint8_t 								StopBits; //This member specifies the number of stop bits transmitted.
														//This parameter must be set based on @ref UART_StopBits_define

	uint8_t 								HwFlowCtl; //This member specifies the hardware flow control mode is enabled or disabled.
														//This parameter must be set based on @ref UART_HwFlowCtl_define

	uint8_t 								IRQ_Enable; //enabled or disabled UART IRQ TX/RX.
															//@ref UART_IRQ_Enable_define , you can select to or three parameters EX. UART_IRQ_Enable_TXE | UART_IRQ_Enable_TC

	void(*P_IRQ_CallBack)(void);							//Set the C function() which will be called once the IRQ Happen



}UART_Config;



//------------------------------------------------------------------
// Reference Macros
//------------------------------------------------------------------

//@ref UART_Mode_define

#define UART_Mode_RX						(uint32_t)(1<<2) //Bit2 RE: Receiver enable
#define UART_Mode_TX						(uint32_t)(1<<3) //Bit2 TE: Transmitter enable
#define UART_Mode_TX_RX						(uint32_t)(1<<2 | 1<<3)


//@ref UART_BaudRate_define
#define UART_BaudRate_2400					2400
#define UART_BaudRate_9600					9600
#define UART_BaudRate_19200					19200
#define UART_BaudRate_57600					57600
#define UART_BaudRate_115200				115200
#define UART_BaudRate_230400				230400
#define UART_BaudRate_460800				460800
#define UART_BaudRate_921600				921600
#define UART_BaudRate_2250000				2250000
#define UART_BaudRate_4500000				4500000


//@ref UART_Payload_length_define
#define UART_Payload_length_8B				(uint32_t)(0)
#define UART_Payload_length_9B				(uint32_t)(1<<12)


//@ref UART_Parity_define
#define UART_Parity_NONE					(uint32_t)(0)
#define UART_Parity_EVEN					((uint32_t)1<<10)
#define UART_Parity_ODD						((uint32_t)(1<<10 | 1<<9))


//@ref UART_StopBits_define
#define UART_StopBits_half					((uint32_t)1<<12)
#define UART_StopBits_1						(uint32_t)(0)
#define UART_StopBits_1_half				((uint32_t)3<<12)
#define UART_StopBits_2						((uint32_t)2<<12)


//@ref UART_HwFlowCtl_define
#define UART_HwFlowCtl_NONE					(uint32_t)(0)
#define UART_HwFlowCtl_RTS					((uint32_t)1<<8)
#define UART_HwFlowCtl_CTS					((uint32_t)1<<9)
#define UART_HwFlowCtl_RTS_CTS				((uint32_t)(1<<8 | 1<<9))


//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE				(uint32_t)(0)
#define UART_IRQ_Enable_TXE					((uint32_t)1<<7) //Transmit data register empty
#define UART_IRQ_Enable_TC					((uint32_t)1<<6) //Transmission complete
#define UART_IRQ_Enable_RXNEIE				((uint32_t)1<<5) //Transmit data ready to be read & Overrun error detected
#define UART_IRQ_Enable_PE					((uint32_t)1<<8) //Parity Error




enum Pollling_mechanism{
	enable ,
	disable
};


//BaudRate Calculation
#define USARTDIV(_PCLK_ , _BAUD_)			(uint32_t)(_PCLK_ / (16 * _BAUD_ ))
#define USARTDIV_MUL_100(_PCLK_ , _BAUD_)	(uint32_t)(25 * _PCLK_ / (4 * _BAUD_ ))
#define Mantissa(_PCLK_ , _BAUD_)			(uint32_t)(USARTDIV(_PCLK_ , _BAUD_))
#define Mantissa_MUL_100(_PCLK_ , _BAUD_)	(uint32_t)(USARTDIV(_PCLK_ , _BAUD_)*100)
#define DIV_Fraction(_PCLK_ , _BAUD_)		(uint32_t)(((USARTDIV_MUL_100(_PCLK_ , _BAUD_) - Mantissa_MUL_100(_PCLK_ , _BAUD_))*16)/100)
#define USART_BRR_Register(_PCLK_ , _BAUD_) ((Mantissa(_PCLK_ , _BAUD_)) <<4 ) | ((DIV_Fraction(_PCLK_ , _BAUD_)) & 0xf)






//------------------------------------------------------------------
//                 APIs Supported by "MCAL GPIO DRIVER"
//------------------------------------------------------------------

//******Initialization / de-Initialization functions******

void MCAL_UART_Init (USART_TypeDef* USARTx, UART_Config* UART_Config);
void MCAL_UART_DeInit (USART_TypeDef* USARTx);
void MCAL_UART_GPIO_Set_Pins (USART_TypeDef* USARTx);
void MCAL_UART_SendData (USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Pollling_mechanism PollingEn);
void MCAL_UART_ReceiveData (USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Pollling_mechanism PollingEn);
void MCAL_UART_WAIT_TC (USART_TypeDef* USARTx);





#endif /* INC_STM32_F103C6_UART_DRIVERS_H_ */
