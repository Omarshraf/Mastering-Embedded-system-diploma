/*
 * Stm32_F103C6_SPI_drivers.h
 *
 *  Created on: Jul 27, 2023
 *      Author: Omar
 */

#ifndef STM32_F103C6_SPI_DRIVERS_H_
#define STM32_F103C6_SPI_DRIVERS_H_
//------------------------------------------------------------------
// Includes
//------------------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_drivers.h"
//--------------------------------------------------------------------

struct S_IRQ_SRC
{
	uint8_t TXE:1;                                  //TX buffer empty interrupt
	uint8_t RXNE:1;                                 //RX buffer not empty interrupt
	uint8_t ERRI:1;                                 //Error interrupt
	uint8_t Reserved:5;

};
//------------------------------------------------------------------
// Configuration Structure
//------------------------------------------------------------------
typedef struct
{
	uint16_t Device_Mode;							//Specifies the SPI Operating mode @ref SPI_Device_Mode
	uint16_t Communication_Mode;					//Specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16_t Frame_Format;							//Specifies the LSB or MSB @ref SPI_Frame_Format
	uint16_t Data_Size;								//@ref SPI_Data_Size
	uint16_t CLKPolarity;							//@ref SPI_CLKPolarity
	uint16_t CLKPhase;								//@ref SPI_CLKPhase
	uint16_t NSS;									//Specifies whether the NSS signal is managed by
													//hardware (NSS pin) or by softare using the SSI bitenable
													//@ref SSPI_NSS

	uint16_t BAUDRATEPRESCALER;						//Specifies The baud rate prescaler value which will be
													//used to configure the transmit and receive SCK clock.
													//this parameter can be a value of @ref SPI_BAUDRATEPRESCALER
													//note: the communication clock is derived from the master clock.
													//the slave clock dosen't need to be set
													//Take care you have to Configure RCC to enter the control clock to APB2 >>> to SPI1

	uint16_t IRQ_Enable;							//@ref SPI_IRQ_Enable

	void (* P_IRQ_CallBack)(struct S_IRQ_SRC);		//Set the C Function() which ill be called ones the IRQ happen
}SPI_Config;




//------------------------------------------------------------------
// Reference Macros
//------------------------------------------------------------------

// @ref SPI_Device_Mode
#define SPI_Device_Mode_SLAVE						(0x00000000U)
#define SPI_Device_Mode_MASTER						(0x1U<<2)  //CR1.MSTR :1: Master configuration

//@ref SPI_Communication_Mode

#define SPI_DIRECTION_2LINES						(0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY					(0x1U<<10) //CR1. Bit 10 RXONLY: Receive only
#define SPI_DIRECTION_1LINES_Receive_only			(0x1U<<15) //CR1. Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_DIRECTION_1LINES_transmit_only			((0x1U<<15) | 0x1U<<14) //CR1. Bit 15 BIDIMODE: Bidirectional data mode enable & Bit 14 BIDIOE: Output enable in bidirectional mode

//@ref SPI_Data_Size
#define  SPI_DataSize_8BIT							(0x00000000U)
#define  SPI_DataSize_16BIT							(0x1U<<11) //Bit 11 DFF: Data size

//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB						(0x00000000U)
#define SPI_Frame_Format_LSB						(0x1U<<7) // CR1. Bit 7 LSBFIRST: Frame format

//@ref SPI_CLKPolarity
#define SPI_SPI_CLKPolarity_LOW_when_idle			(0x00000000U)
#define SPI_SPI_CLKPolarity_HIGH_when_idle			(0x1U<<1) //Bit 1 CPOL: Clock polarity

//@ref SPI_CLKPhase
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge (0x00000000U)
#define SPI_Clock_Phase_2EDGE_second_data_capture_edge (0x1U<<0) //Bit 1 CPHA: Clock phase

//@ref SSPI_NSS
//================NSS================
//Hardware
#define SPI_NSS_Hard_Slave							(0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_enable		(0x1U<<2) //SPI_CR2 bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_output_disable		~(0x1U<<2) //SPI_CR2 bit 2 SSOE: SS output disable
 //SW
#define SPI_NSS_Soft_NSSInternalSoft_Reset			(0x1U<<9)
#define SPI_NSS_Soft_NSSInternalSoft_Set			((0x1U<<9) | (0x1U<<8))
//==================================

//@ref SPI_BAUDRATEPRESCALER
#define SPI_BAUDRATEPRESCALER_2						(0x00000000U)
#define SPI_BAUDRATEPRESCALER_4						(0b001U<<3)
#define SPI_BAUDRATEPRESCALER_8						(0b010U<<3)
#define SPI_BAUDRATEPRESCALER_16					(0b011U<<3)
#define SPI_BAUDRATEPRESCALER_32					(0b100U<<3)
#define SPI_BAUDRATEPRESCALER_64					(0b101U<<3)
#define SPI_BAUDRATEPRESCALER_128					(0b110U<<3)
#define SPI_BAUDRATEPRESCALER_256					(0b111U<<3)

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE							(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE						(uint32_t)(1<<7)
#define SPI_IRQ_Enable_RXEIE						(uint32_t)(1<<6)
#define SPI_IRQ_Enable_ERRIE						(uint32_t)(1<<5)
//------------------------------------------------------------------------------

enum PollingMechism
{
	Pollingenable,
	Pollingdisable
};


/*
 * ==============================================================================
 *                       APIs Supported by "MCAL SPI DRIVER"
 * ==============================================================================
 */

void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config* SPI_config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn);
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn);

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn);





















#endif /* STM32_F103C6_SPI_DRIVERS_H_ */
