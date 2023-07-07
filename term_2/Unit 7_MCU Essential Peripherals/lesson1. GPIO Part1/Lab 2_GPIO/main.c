/*
 * Lab_2 GPIO.c
 * this code toggle 3 LEDs in the next sequence
 * LEDd5 on ..wait(0.5sec)... LEDd6 on ..wait(0.5sec)... LEDd7 on ..wait(0.5sec)...
 * LEDd5 off ..wait(0.5sec)... LEDd6 off ..wait(0.5sec)... LEDd7 off ..wait(0.5sec)...
 * Created: 7/7/2023 4:14:14 PM
 * Author : Omar
 */

#include "memory_map.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
    DDRD |= (0b111<<5);
	int i;
	PORTD = 0xFF;
	_delay_ms(500);

	PORTD = 0x00;
	_delay_ms(500);
    while (1) 
    {
		

		for (i=5; i<8; i++)
		{
			PORTD |= (1<<i);
			_delay_ms(500);
		}
		i--;
		for (;i>=0;i--)
		{
			PORTD &= ~(1<<i);
			_delay_ms(500);

		}
		
		
    }
}

