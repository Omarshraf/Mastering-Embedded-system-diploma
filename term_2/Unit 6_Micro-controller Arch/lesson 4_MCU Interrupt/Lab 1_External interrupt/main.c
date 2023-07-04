


/*
 * This software works on detect an external interrupt on pin 0 Port A
 * and based on it that toggle the output on pin 13 Port A
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
//register address

//RCC
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile unsigned int*)(RCC_BASE + 0x18)
#define RCC_IOPAEN   (1<<2)





//GPIO
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile unsigned int*)(GPIOA_BASE + 0x04)
#define GPIOA_CRL *(volatile unsigned int*)(GPIOA_BASE + 0x00)
#define GPIOA_ODR *(volatile unsigned int*)(GPIOA_BASE + 0x0C)
#define GPIOA13   (1UL<<13)

//EXTI
#define EXTI_BASE 0x40010400
#define EXTI_IMR *(volatile unsigned int*)(EXTI_BASE + 0x00)
#define EXTI_RTSR *(volatile unsigned int*)(EXTI_BASE + 0x08)
#define EXTI_PR *(volatile unsigned int*)(EXTI_BASE + 0x14)


//AFIO
#define AFIO_BASE 0x40010000
#define AFIO_EXTICR1 *(volatile unsigned int*)(AFIO_BASE + 0x08)


#define NVIC_EXTIE0 *(volatile unsigned int*)(0xE000E100)










void clock_int()
{
	//Enable clock GPIOA
	RCC_APB2ENR |= RCC_IOPAEN;
	//BIT 0 AFIOEN: Alternate function I/O clock enable
	RCC_APB2ENR |= (1<<0);

}
void GPIO_init()
{
	//pin 13 port A output
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	//Pin A0 : Floating input (reset state)
	GPIOA_CRL |= (1<<2);


}


int main(void)
{

	clock_int();
	GPIO_init();

	//EXTI0 Configuration to PORTA0
	AFIO_EXTICR1=0;

	//Enable rising Trigger
	EXTI_RTSR |= (1<<0);

	//Enable EXTI Line 0 (MAsk 1)
	EXTI_IMR |=(1<<0);

	//Enable NVIC Irq6 <<>>EXTI0
	NVIC_EXTIE0 |= (1<<6);

	while(1);
}


void EXTI0_IRQHandler(void)
{
	//IRQ is Happened EXTI0 >>>> PORTA Pin 0 _|- rising edge
	//toggle led pin A 133
	GPIOA_ODR ^= (1<<13);

	//Clear pending Request for line 0
	EXTI_PR |= (1<<0);
}



