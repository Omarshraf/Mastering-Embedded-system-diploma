/*
 * Stm32_F103C6_SPI_driver.c
 *
 *  Created on: Jul 27, 2023
 *      Author: Omar
 */

#include "Stm32_F103C6_SPI_drivers.h"

/*
 * =================================================================================
 *                                        Generic Variable
 * =================================================================================
 */
SPI_Config* Global_SPI_Config[2] = {NULL , NULL};
SPI_Config Global_SPI_Comfig1;
SPI_Config Global_SPI_Comfig2;


/*
 * =================================================================================
 *                                        Generic Macros
 * =================================================================================
 */
#define SPI1_INDEX						0
#define SPI2_INDEX						1


#define SPI_SR_TXE						((uint8_t)0x02)
#define SPI_SR_RXNE						((uint8_t)0x01)
/*
 * =================================================================================
 *                                        APIs
 * =================================================================================
 */

/*=======================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief			- initializes SPI according to specified parameters
 * @parameter[in]	- SPIx: where x can be (1>>>3 depending on device used) to select the USART peripheral
 * @parameter[in]	- SPI_Config: pointer to a SPI_Config structure, All SPI Configuration EXTI_PinConfig_t
 * @retval			- none
 * Note				- Support for SPI FULL Duplex MAster/Slave only & NSS HW/SW
 * 						in case of master you have to configure pin and drive it
 */
void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config* SPI_config)
{
	//Safety for registers
	uint16_t tmpreg_CR1 =0;
	uint16_t tmpreg_CR2 =0;

	if(SPIx == SPI1)
	{
		Global_SPI_Comfig1 = * SPI_config;
		Global_SPI_Config[SPI1_INDEX]= SPI_config;
		RCC_SPI1_CLK_EN();

	}else if(SPIx == SPI2)
	{
		Global_SPI_Comfig2 = * SPI_config;
		Global_SPI_Config[SPI2_INDEX]= SPI_config;
		RCC_SPI2_CLK_EN();
	}
	//Enable SPI CR1: Bit 6 SPE: SPI enable
	tmpreg_CR1 = (0x1U<<6);

	//Master or Slave
	tmpreg_CR1 = SPI_config->Device_Mode;

	//SPI Communication mode
	tmpreg_CR1 = SPI_config->Communication_Mode;

	//SPI Frame Format
	tmpreg_CR1 = SPI_config->Frame_Format;

	//SPI Data Size
	tmpreg_CR1 = SPI_config->Data_Size;

	//SPI Clock Polarity
	tmpreg_CR1 = SPI_config->CLKPolarity;

	//SPI Clock Phase
	tmpreg_CR1 = SPI_config->CLKPhase;

	//==========================NSS========================
	if (SPI_config->NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tmpreg_CR2 |= SPI_config->NSS;
	}else if(SPI_config->NSS == SPI_NSS_Hard_Master_SS_output_disable)
	{
		tmpreg_CR2 &= SPI_config->NSS;
	}else
	{
		tmpreg_CR1 |= SPI_config->NSS;

	}

//============================================================
	//SPI BAUDRATEPRESCALER
	tmpreg_CR1 |= SPI_config->BAUDRATEPRESCALER;
	if(SPI_config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		// SPI IRQ Enable define
		tmpreg_CR2 |= SPI_config->IRQ_Enable;
		if(SPIx == SPI1)
			NVIC_IRQ35_SPI1_Enable;
		else if(SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable;
	}
	SPIx->CR1 = tmpreg_CR1;
	SPIx->CR2 = tmpreg_CR2;

}


void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if (SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_RESET();
	}else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_RESET();
	}
}


void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn)
{
	if (PollingEn == Pollingenable)
		while (!((SPIx)->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer;

}

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum PollingMechism PollingEn)
{
	if (PollingEn == Pollingenable)
		while (!((SPIx)->SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->DR ;
}

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn)
{
	if (PollingEn == Pollingenable)
		while (!((SPIx)->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer;
	if (PollingEn == Pollingenable)
		while (!((SPIx)->SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->DR ;
}

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx)
{
	GPIO_PinConfig_t PinCfg;
	if (SPIx == SPI1)
	{
		//PA4 : SPI1_NSS
		//PA5 : SPI1_SCK
		//PA6 : SPI1_MISO
		//PA7 : SPI1_MOSI
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
		{
			//PA4 : SPI1_NSS
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				// HW Master / slave Input floating
				PinCfg.GPIO_PinNumber =GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			case SPI_NSS_Hard_Master_SS_output_enable:
				// HW Master / NSS output enable Alternate function Push-PULL
				PinCfg.GPIO_PinNumber =GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			}
			//PA5 : SPI1_SCK
			//Master Alternate function push-pull
			PinCfg.GPIO_PinNumber =GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6 : SPI1_MISO (supported by full duplex)
			//Master input floatint
			PinCfg.GPIO_PinNumber =GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7 : SPI1_MOSI
			//Master Alternate function push-pull
			PinCfg.GPIO_PinNumber =GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);



		}else  //Slave
		{
			//PA4 : SPI_NSS
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//HW Master/Salve input floating
				PinCfg.GPIO_PinNumber =GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//PA5 : SPI1_SCK
			//Slave input floating
			PinCfg.GPIO_PinNumber =GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6 : SPI1_MISO (supported by full duplex)
			//slave Alternative function push-pull
			PinCfg.GPIO_PinNumber =GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


			//PA7 : SPI1_MOSI
			//Slave input floating
			PinCfg.GPIO_PinNumber =GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
	}else if(SPIx == SPI2)
	{
		//PA12 : SPI1_NSS
		//PA13 : SPI1_SCK
		//PA14 : SPI1_MISO
		//PA15 : SPI1_MOSI
		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
		{
			//PA12 : SPI2_NSS
			switch(Global_SPI_Config[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				// HW Master / slave Input floating
				PinCfg.GPIO_PinNumber =GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:
				// HW Master / NSS output enable Alternate function Push-PULL
				PinCfg.GPIO_PinNumber =GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			}
			//PA13 : SPI2_SCK
			//Master Alternate function push-pull
			PinCfg.GPIO_PinNumber =GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA14 : SPI2_MISO (supported by full duplex)
			//Master input floatint
			PinCfg.GPIO_PinNumber =GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA15 : SPI2_MOSI
			//Master Alternate function push-pull
			PinCfg.GPIO_PinNumber =GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);



		}else  //Slave
		{
			//PA12 : SPI2_NSS
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Salve input floating
				PinCfg.GPIO_PinNumber =GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//PA13 : SPI2_SCK
			//Slave input floating
			PinCfg.GPIO_PinNumber =GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA14 : SPI2_MISO (supported by full duplex)
			//slave Alternative function push-pull
			PinCfg.GPIO_PinNumber =GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


			//PA15 : SPI2_MOSI
			//Slave input floating
			PinCfg.GPIO_PinNumber =GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


		}
	}
}

/*
 * =================================================================================
 *                                        IRQ
 * =================================================================================
 */

void SPI1_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI1->SR & (1<<1))>>1);
	irq_src.RXNE = ((SPI1->SR & (1<<0))>>0);
	irq_src.ERRI = ((SPI1->SR & (1<<4))>>4);
	Global_SPI_Config [SPI1_INDEX]->P_IRQ_CallBack(irq_src);

}

void SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI2->SR & (1<<1))>>1);
	irq_src.RXNE = ((SPI2->SR & (1<<0))>>0);
	irq_src.ERRI = ((SPI2->SR & (1<<4))>>4);
	Global_SPI_Config [SPI2_INDEX]->P_IRQ_CallBack(irq_src);

}



