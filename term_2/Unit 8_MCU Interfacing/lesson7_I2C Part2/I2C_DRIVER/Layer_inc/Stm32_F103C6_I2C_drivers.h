/*
 * Stm32_F103C6_I2C_drivers.h
 *
 *  Created on: Jul 27, 2023
 *      Author: Omar
 */

#ifndef STM32_F103C6_I2C_DRIVERS_H_
#define STM32_F103C6_I2C_DRIVERS_H_
//------------------------------------------------------------------
// Includes
//------------------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_drivers.h"
#include "Stm32_F103C6_RCC_drivers.h"

//--------------------------------------------------------------------

//------------------------------------------------------------------
// Configuration Structure
//------------------------------------------------------------------
struct S_I2C_Slave_Device_Address
{
	uint16_t Enable_Dual_ADD; // 1-Enable  0-Disable
	uint16_t Primary_slave_address;
	uint16_t Secondary_slave_address;
	uint16_t I2C_Addressing_Slave_mode;		 //@ref I2C_Addressing_slave					//@ref I2C_Addressing_Slave_mode

};
typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,		//the APP Layer should send the data (I2C_SlaveSendData)in this state
	I2C_EV_DATA_RCV			//the APP Layer should read the data (I2C_SlaveReceiveData)in this state

}Slave_State;
typedef struct
{
	uint32_t ClockSpeed;										/*specifies the clock frequency.
																  This parameter must be set to @ref I2C_SCLK_ */

	uint32_t StretchMode;										//@ref I2C_StretchMode_


	uint32_t I2C_Mode;											/*Specifies the I2C mode
																@ref I2C_Mode*/

	struct S_I2C_Slave_Device_Address I2C_Slave_Adress;


	uint32_t I2C_ACK_Control;									/*Enable or disables the acknowledgement
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref I2C_ACK*/


	uint32_t General_Call_Address_Detection;					//@ref I2C_ENGC


	void (*P_Slave_Event_CallBack)(Slave_State state);
}I2C_Config;
//------------------------------------------------------------------
// Reference Macros
//------------------------------------------------------------------

//@ref I2C_SCLK_
//- Standard Speed (Up to 100 KHz)
// to configure Clock before enable the peripheral
//---I2C_CR2.FREQ[5:0]: peripheral Clock frequency
// configure the Clock control registers
//				Thigh = CCR * TPCLK1
//				SM or FM
// configure the rise time register I2C_TRISE
//----
#define I2C_SCLK_SM_50K										(0x50000U)
#define I2C_SCLK_SM_100K									(0x100000U)


//@ref I2C_StretchMode_

//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
//it is reset by software.
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_StretchMode_Enable								(0x00000000U)
#define I2C_StretchMode_Enable								I2C_CR1_NOSTRETCH

//@ref I2C_Mode
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_mode_I2C										0
#define I2C_mode_SMBus										I2C_CR1_SMBUS


//@ref I2C_Addressing_Slave_mode
#define I2C_Addressing_Slave_mode_7Bit						0x00000000U
#define I2C_Addressing_Slave_mode_10Bit						(uint16_t)(1<<15)


//@ref I2C_ACK
#define I2C_ACK_Enable										(I2C_CR1_ACK)
#define I2C_ACK_Disable										((uint16_t)0x0000)


//@ref I2C_ENGC
#define I2C_ENGC_Enable										(I2C_CR1_ENGC)
#define I2C_ENGC_Disable									0x00000000U



//------------------------------------------------------------------------------


typedef enum
{
	with_Stop,
	without_Stop
}Stop_Condition;

typedef enum
{
	Start,
	repeated_start
}Repeated_Start;


typedef enum {DISABLE = 0 , ENABLE = 1}FunctionalState;
typedef enum {RESET = 0 , SET = 1}FlagStatus;
typedef enum {I2C_Direction_Transmitter = 0 , I2C_Direction_Reciever = 1}I2C_Direction;

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING				((uint32_t)0x00070080) /*TRA, BUSY, MSL, TXE flags*/

typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5,  	//	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6,	// EV6: ADDR = 1, cleared by reading SR1 register followed by reading SR2.
	EV8, // EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
	EV8_1,
	EV7,
	MASTER_BYTE_TRANSMITTING =  ((uint32_t)0x00070080)   /*TRA, BUSY, MSL, TXE flags*/


}Status;

/*
 * ==============================================================================
 *                       APIs Supported by "MCAL SPI DRIVER"
 * ==============================================================================
 */

void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config* I2C_CFG);
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

// MAster Polling Mechanism
void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx , uint16_t devAddr, uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx , uint16_t devAddr, uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);


// Slave interrupt mechanism
void MCAL_I2C_SlaveSendData (I2C_TypeDef* I2Cx, uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData (I2C_TypeDef* I2Cx);




// Generic APIs
void I2C_GenerateSTART(I2C_TypeDef* I2Cx , FunctionalState NewState , Repeated_Start start);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx , Status flag);
void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16_t Address, I2C_Direction Direction);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx , FunctionalState NewState);
void I2C_AcknoledgeConfig(I2C_TypeDef* I2Cx , FunctionalState NewState);
















#endif /* STM32_F103C6_I2C_DRIVERS_H_ */
