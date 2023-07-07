/*
 * Lab4_GPIO.c
 * this code read the signal from the bottom
 * that connected with pin D0 (if it pressed)
 * it generates a voltage on pin D4
 * that turn on a horn like in cars
 * until the bottom is being released it takes 
 * the horn off   
 * Created: 7/7/2023 7:25:03 PM
 * Author : Omar
 */ 

#include "memory_map.h"

int main(void)
{
	ResetBit(DDRD,0);
	SetBit(DDRD,4);
	

	
    while (1) 
    {
		while(ReadBit(PIND,0)==1)
		{
			SetBit(PORTD,4);
		}
		ResetBit(PORTD,4);
	}

}