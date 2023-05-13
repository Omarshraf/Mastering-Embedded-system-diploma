#include<stdint.h>

extern int main(void);
extern uint32_t stack_top;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;
extern uint32_t _E_text;


void reset_handler(){
	//copy data fom flash to sram
	uint32_t data_size=(uint8_t*) &_E_data-(uint8_t*) &_S_data;
	uint8_t* P_source=(uint8_t*) &_E_text;
	uint8_t* P_distination=(uint8_t*) &_S_data;
	for (int i = 0; i < data_size; ++i)
	{
		*((uint8_t*) P_distination++)=	*((uint8_t*) P_source++);
	}

	//init the .bss section and set it with zeros
	uint32_t bss_size= _E_bss- _S_bss;
	for (int i = 0; i < bss_size; ++i)
	{
		*((uint8_t*) P_distination++)=	(uint8_t)0;
	}


	main();
}

void default_handler(){
	reset_handler();
}

void NMI_handler(void) __attribute__((weak,alias("default_handler")));;
void HardFault_handler(void) __attribute__((weak,alias("default_handler")));;
void MemManage_handler(void) __attribute__((weak,alias("default_handler")));;
void BusFault_handler(void) __attribute__((weak,alias("default_handler")));;
void UsageFault_handler(void) __attribute__((weak,alias("default_handler")));;





uint32_t vector[] __attribute__((section(".vectors")))={
	(uint32_t) &stack_top,
	(uint32_t) &reset_handler,
	(uint32_t) &NMI_handler,
	(uint32_t) &HardFault_handler,
	(uint32_t) &MemManage_handler,
	(uint32_t) &BusFault_handler,
	(uint32_t) &UsageFault_handler
};
