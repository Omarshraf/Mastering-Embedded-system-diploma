#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* this software example make sure that the system clock set in 60MHz
 * and the APB1 BUS set in 15MHz
 * and the APB2 BUS set in 60MHz
 * By using an external crystal/ceramic resonator in 15MHz
 * in Case to control the power consumption
 * for STM32F103C6
 */
#define RCC_base 0x40021000
#define RCC_CFGR *(volatile unsigned int*)(RCC_base+0x04)
#define RCC_CR *(volatile unsigned int*) (RCC_base+0x00)

int main(void)
{
	//Bit 24 PLLON: PLL enable
	//Set and cleared by software to enable PLL.
	//Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
	//PLL clock is used as system clock or is selected to become the system clock.
	//0: PLL OFF
	//1: PLL ON
	RCC_CR |= (0<< 24);


	//Bit 16 PLLSRC: PLL entry clock source
	//Set and cleared by software to select PLL clock source. This bit can be written only when
	//PLL is disabled.
	//0: HSI oscillator clock / 2 selected as PLL input clock
	//1: HSE oscillator clock selected as PLL input clock
	RCC_CFGR |= (1 << 16);

	//Bits 21:18 PLLMUL: PLL multiplication factor
	//These bits are written by software to define the PLL multiplication factor. These bits can be
	//written only when PLL is disabled.
	//Caution: The PLL output frequency must not exceed 72 MHz.
	//0000: PLL input clock x 2
	//0001: PLL input clock x 3
	//0010: PLL input clock x 4
	RCC_CFGR |= (0b0010 << 18);

	//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	//Set and cleared by software to control the division factor of the APB low-speed clock
	//(PCLK1).
	//Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
	//0xx: HCLK not divided
	//100: HCLK divided by 2
	//101: HCLK divided by 4
	RCC_CFGR |= (0b101 << 8);

	//Bit 16 HSEON: HSE clock enable
	//Set and cleared by software.
	//Cleared by hardware to stop the HSE oscillator when entering Stop or Standby mode. This
	//bit cannot be reset if the HSE oscillator is used directly or indirectly as the system clock.
	//0: HSE oscillator OFF
	//1: HSE oscillator ON
	RCC_CR |= (0b1<< 16);

	//Bit 24 PLLON: PLL enable
	//Set and cleared by software to enable PLL.
	//Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
	//PLL clock is used as system clock or is selected to become the system clock.
	//0: PLL OFF
	//1: PLL ON
	RCC_CR |= (1<< 24);



	//Bits 1:0 SW: System clock switch
	//Set and cleared by software to select SYSCLK source.
	//Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of
	//failure of the HSE oscillator used directly or indirectly as system clock (if the Clock Security
	//System is enabled).
	//00: HSI selected as system clock
	//01: HSE selected as system clock
	//10: PLL selected as system clock
	//11: not allowed
	RCC_CFGR |= (0b10<< 0);




	while(1)
		{

		for(int i=0;i<2000;i++);
		}

}

