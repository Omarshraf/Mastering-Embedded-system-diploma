/*
 * Stm32_F103C12_gpio_driver.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Omar
 */

#include "Stm32_F103C6_USART_drivers.h"

//=======================================================================
//                         Generic Variable
//=======================================================================

UART_Config* Global_UART_Config =NULL;


//=======================================================================
//                                APIs
//=======================================================================

/*=======================================================================
 * @Fn				- MCAL_UART_Init
 * @brief			- initializes UART (Supported feature ASYNCH, ONLY)
 * @parameter[in]	- USARTx: where x can be (1>>>3 depending on device used) to select the USART peripheral
 * @parameter[in]	- UART_Config: pointer to a USART_Config structure, All UART Configuration EXTI_PinConfig_t
 * @retval			- none
 * Note				- Support for Now Asynch mode & Clock 8 MHz
 */

void MCAL_UART_Init (USART_TypeDef* USARTx, UART_Config* UART_Config)
{
	uint32_t pclk ,BRR;
	Global_UART_Config = UART_Config;

	//enable clock for given USART peripheral
	if (USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if(USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if(USARTx == USART3)
		RCC_USART3_CLK_EN();

	//enable USART Module
	//Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	//Enable USART Tx & Rx engines according to the USART_Mode configuration item
	USARTx->CR1 |= UART_Config ->Mode;

	//PayLoad length
	USARTx->CR1 |= UART_Config->Payload_length;

	//Configuration of Parity Control bit field
	USARTx->CR1 |= UART_Config->Parity;

	//Configure the number of stop bits
	USARTx->CR2 |= UART_Config->StopBits;

	//USART Hardware flow control
	USARTx->CR3 |= UART_Config->HwFlowCtl;

	// Configuration of BRR (BAUdrate register)
	// PCLK1 for USART2 ,3
	// PCLK2 for USART1

	if(USARTx == USART1)
		pclk = MCAL_RCC_GetPCLK2Freq();
	else
		pclk = MCAL_RCC_GetPCLK1Freq();


	BRR = USART_BRR_Register(pclk,UART_Config->BaudRate);
	USARTx->BRR = BRR;


	// Enable / Disable Interrupt
	//USART_CR1
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_Config->IRQ_Enable;

		//Enable NVIC For USARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;

		if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;
		if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;

	}

}



/*=======================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief			- DeInitializes UART (Supported feature ASYNCH, ONLY)
 * @parameter[in]	- USARTx: where x can be (1>>>3 depending on device used) to select the USART peripheral
 * @retval			- none
 * Note				- Reset the Model By RCC
 */

void MCAL_UART_DeInit (USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_Disable;
	}


	if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable;
	}

	if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable;
	}


}



/*=======================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief			- Send Buffer on UART
 * @parameter[in]	- USARTx: where x can be (1>>>3 depending on device used) to select the USART peripheral
 * @parameter[in]	- pTxBuffer: Pointer on the tTx Buffer
 * @parameter[in]	- PollingEn: Enable pooling or disable it
 * @retval			- none
 * Note				- Should initialize UART First
 * 					  When transmitting with the Parity enabled (PCE bit set to 1 in the USART_CR1 register),
 * 					  the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 * 					  because it is replaced by the Parity
 * 					  When receiving with the Parity enabled, the value read in the MSB bit is the received parity bit.
 */
void MCAL_UART_SendData (USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Pollling_mechanism PollingEn)
{

	//wait untill TXE flag is set in the SR
	if (PollingEn == enable)
		while (!(USARTx->SR & 1<<7));

	//Check the USART_WORDLENGTH item for 8Bits or 8bits in a frame

//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
//	because it is replaced by the parity.
//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
//	bit.

	if(Global_UART_Config->Payload_length == UART_Payload_length_9B)
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	else
		//8bits data transfer
		USARTx->DR = (*pTxBuffer & (uint16_t)0x0FF);


}


void MCAL_UART_WAIT_TC (USART_TypeDef* USARTx)
{
	// wait till TC flag is set in the SR
	while(! (USARTx->SR && 1<<6));
}






void MCAL_UART_ReceiveData (USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Pollling_mechanism PollingEn)
{
	//wait Until RXNE flag is set in the SR
	if (PollingEn == enable)
		while (!(USARTx->SR & 1<<7));

	//Check the USART_WORDLENGTH item for 8Bits or 8bits in a frame

	if(Global_UART_Config->Payload_length == UART_Payload_length_9B)
	{
		if (Global_UART_Config->Parity == UART_Parity_NONE )
			//no parity so all 9bits are considered as data
			*((uint16_t*)pTxBuffer) = USARTx->DR;
		else
			// the parity is used, so 8bit will be of user data and 1 bit is parity
			*((uint16_t*)pTxBuffer) =( USARTx->DR & (uint8_t)0xFF);

	}else
	{
		//8bit data
		if (Global_UART_Config->Parity == UART_Parity_NONE )
			//no parity so all 9bits are considered as data
			*((uint16_t*)pTxBuffer) =( USARTx->DR & (uint8_t)0xFF);
		else
			// the parity is used, so 7bit will be of user data and 1 bit is parity
			*((uint16_t*)pTxBuffer) =( USARTx->DR & (uint8_t)0x7F);


	}




}


/*=======================================================================
 * @Fn				- MCAL_UART_GPIO_Set_Pins
 * @brief			- Initializes GPIO Pins
 * @parameter[in]	- USARTx: where x can be (1>>>3 depending on device used) to select the USART peripheral
 * @retval			- none
 * Note				- Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins (USART_TypeDef* USARTx)
{
	GPIO_PinConfig_t PinCfg;
	if(USARTx == USART1)
	{
		//PA9  Tx
		//PA10 Rx
		//PA11 CTS
		//PA12 RTS

		//PA9 Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA , &PinCfg);

		//PA10 Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA , &PinCfg);


		if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
		//PA11 CTS
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA , &PinCfg);
		}

		if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &PinCfg);
		}


	}




	else if(USARTx == USART2)
		{
			//PA2 Tx
			//PA3 Rx
			//PA0 CTS
			//PA1 RTS

			//PA2 Tx
			PinCfg.GPIO_PinNumber = GPIO_PIN_2;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA , &PinCfg);

			//PA3 Rx
			PinCfg.GPIO_PinNumber = GPIO_PIN_3;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
			MCAL_GPIO_Init(GPIOA , &PinCfg);


			if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
			{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA , &PinCfg);
			}

			if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
			{
				//PA1 RTS
				PinCfg.GPIO_PinNumber = GPIO_PIN_1;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA , &PinCfg);
			}


		}


	else if(USARTx == USART3)
			{
				//PB10 Tx
				//PB11 Rx
				//PB13 CTS
				//PB14 RTS

				//PB10 Tx
				PinCfg.GPIO_PinNumber = GPIO_PIN_10;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA , &PinCfg);

				//PB11 Rx
				PinCfg.GPIO_PinNumber = GPIO_PIN_11;
				PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
				MCAL_GPIO_Init(GPIOA , &PinCfg);


				if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
				{
				//PB13 CTS
				PinCfg.GPIO_PinNumber = GPIO_PIN_13;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA , &PinCfg);
				}

				if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
				{
					//PA14 RTS
					PinCfg.GPIO_PinNumber = GPIO_PIN_14;
					PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
					PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOA , &PinCfg);
				}


			}

}


void USART1_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CallBack();
}


void USART2_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CallBack();
}


void USART3_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CallBack();
}






