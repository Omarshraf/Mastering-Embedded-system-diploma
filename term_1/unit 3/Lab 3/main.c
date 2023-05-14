#define SYSCTL_RCGC2_R (*((volatile unsigned long*) 0x400FE108))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long*) 0X40025400))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long*) 0X4002551C))
#define GPIO_PORTF_DATA_R (*((volatile unsigned long*) 0X400253FC))
int main(int argc, char const *argv[])
{
	volatile unsigned long i; //to save the delay from optimization
	SYSCTL_RCGC2_R=0x20;
	// DELAY TO MAKE SURE GPIOF IS RUNNING
	for (i = 0; i < 200; ++i);
	GPIO_PORTF_DIR_R|=1<<3; //MAKE THE DIRECTION IS OUTPUT
	GPIO_PORTF_DEN_R|=1<<3; //ENABLE PIN 3
	//TOGGLE
	while(1){
		GPIO_PORTF_DATA_R|=1<<3;
		for (i = 0; i < 200000; ++i);
		GPIO_PORTF_DATA_R&=~(1<<3);
		for (i = 0; i < 200000; ++i);
	}
	

	return 0;
}
