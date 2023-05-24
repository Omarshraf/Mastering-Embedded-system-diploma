/*
 * main.c
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */
#include "CA.h"
#include "US.h"
#include "DC.h"


void setup ()
{
	US_init();
	DC_init();

	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_ideal);

}
void main()
{
	volatile int d;
	setup();
	while(1)
	{
		//call state for each block
		US_state();
		CA_state();
		DC_state();

		for (d = 0; d < 1000; ++d);
	}
}
