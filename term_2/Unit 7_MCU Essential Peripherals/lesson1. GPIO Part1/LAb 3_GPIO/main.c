/*
 * Lap3_GPIO.c
 * this software make sure that every time you press
 * the bottom connected with pin (D0) >>> turn on 
 * an led sequentially until the all leds are on
 * it reverse the order
 * Created: 7/7/2023 6:25:01 PM
 * Author : Omar
 */ 

#include <util/delay.h>
#include "memory_map.h"
#define F_CPU 8000000


int main(void)
{
	DDRD |= (0b111<<5);
	ResetBit(DDRD,0);
	int flag = 0;
	
    while (1) 
    {
		if (ReadBit(PIND,0)==1) //the bottom is pressed
		{
			if(flag<3)
			{
			SetBit(PORTD,(flag+5));
			flag++;
			while(ReadBit(PIND,0)==1); //single press
			}
			else
			{
				while(flag>0)
				{
					
					if (ReadBit(PIND,0)==1) //the bottom is pressed
					{
						ResetBit(PORTD,((flag-1)+5));
						flag--;
						while(ReadBit(PIND,0)==1); //single press
					}

				}
				
				
			}
	
		}
	
		
    }
}

