
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
#define GPIOA_IDR *(volatile unsigned int*)(GPIOA_BASE + 0x08)

#define GPIOA13   (1UL<<13)

#define GPIOB_BASE 0x40010C00
#define GPIOB_CRH *(volatile unsigned int*)(GPIOB_BASE + 0x04)
#define GPIOB_CRL *(volatile unsigned int*)(GPIOB_BASE + 0x00)
#define GPIOB_ODR *(volatile unsigned int*)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR *(volatile unsigned int*)(GPIOB_BASE + 0x08)


void clock_int()
{
	//Enable clock GPIOA
	RCC_APB2ENR |= RCC_IOPAEN;
	//Enable clock GPIOB
	RCC_APB2ENR |= (1<<3);

}
void GPIO_init()
{
	GPIOA_CRL =0x0;
	GPIOB_CRL =0x0;

	//PA1 input Hi-Z
	GPIOA_CRL |= (1<<6);

	//PB1 output push pull mode
	//CNF  00
	GPIOB_CRL &= ~(0b11<<6);
	//01: OUTPUT MODE , MAX SPEED 10 MHz
	GPIOB_CRL |= (0b01<<4);

	//PA13 input Hi-Z
	GPIOA_CRH &= ~(0b11<<20);
	GPIOA_CRH |= (0b01<<22);

	//PB13 output push pull mode
	GPIOB_CRH |= (0b01<<20);
	GPIOB_CRH &= ~(0b11<<22);
}

void my_wait(int x)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<255;j++);
}
int main(void)
{

	clock_int();
	GPIO_init();



	while(1)
	{
		//PA1 >>>>> connected external  PUR
		if(((GPIOA_IDR & (1<<1))>>1) == 0 ) //press
		{
			GPIOB_ODR ^= 1<<1;
			while ((((GPIOA_IDR & (1<<1))>>1) == 0 ) ); //Single press
		}

		//PA1 >>>>> connected external  PUR
		if(((GPIOA_IDR & (1<<13))>>13) == 1 ) //Multi press
		{
			GPIOB_ODR ^= 1<<13;
		}
		my_wait(1);
	}

}


