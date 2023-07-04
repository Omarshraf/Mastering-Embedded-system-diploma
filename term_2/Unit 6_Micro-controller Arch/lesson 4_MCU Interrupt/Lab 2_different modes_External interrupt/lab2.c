
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define IO_BASE         0x20
#define IO_PORTD        *(volatile unsigned int*)(IO_BASE + 0x12)
#define IO_DDRD         *(volatile unsigned int*)(IO_BASE + 0x11)
#define MCUCR           *(volatile unsigned int*)(IO_BASE + 0x35)
#define MCUCSR          *(volatile unsigned int*)(IO_BASE + 0x34)
#define GICR            *(volatile unsigned int*)(IO_BASE + 0x3B)  


int main(int argc, char const *argv[])
{
	//allow pin(5,6,7) as output in portD (pin = 0)
	IO_DDRD |= (1<<5);
	IO_DDRD |= (1<<6);
	IO_DDRD |= (1<<7);
	
	//set int0 logical
	MCUCR |= (1<<0);
	MCUCR &= ~(1<<1);

	//set int0 logical
	MCUCR |= (1<<2);
	MCUCR |= (1<<3);

	//set int0 logical
	MCUCSR &= ~(1<<6);

	//enable all int 0,1,2
	GICR |= (1<<5);
	GICR |= (1<<6);
	GICR |= (1<<7);

	//enable Global interrupt
	sei();


	while(1)
	{
		IO_PORTD &= ~(1<<5);
		IO_PORTD &= ~(1<<6);
		IO_PORTD &= ~(1<<7);
	}
	

	return 0;
}

ISR (INT0_vect){
	IO_PORTD |= (1<<5);
	_delay_ms(1000);
}


ISR (INT1_vect){
	IO_PORTD |= (1<<6);
	_delay_ms(1000);
}

ISR (INT2_vect){
	IO_PORTD |= (1<<7);
	_delay_ms(1000);
}
