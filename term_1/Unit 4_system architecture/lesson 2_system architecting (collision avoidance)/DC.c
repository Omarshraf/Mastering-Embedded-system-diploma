/*
 * DC.c
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */

#include "DC.h"
//variables
unsigned int DC_speed;

//state pointer to function
void (*DC_state)();
void DC_init()
{
	//init PWM
	printf("DC_init \n");
}

void DC_motor(int s)
{
	DC_speed = s;
	DC_state = STATE(DC_busy);

 	printf("CA -----speed = %d--------> DC \n",DC_speed);

}


STATE_define(DC_ideal)
{
	//state_name
	DC_state_id = DC_ideal;
	//state action
	DC_speed = 0;
	//DC_motor(DC_speed)
	printf("DC_ideal state:  speed = %d\n",DC_speed);


}

STATE_define(DC_busy)
{
	//state_name
	DC_state_id = DC_busy;
	//state action
	DC_state = STATE(DC_ideal);

	printf("DC_busy state:  speed = %d\n",DC_speed);


}





