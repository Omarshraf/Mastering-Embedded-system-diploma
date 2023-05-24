/*
 ============================================================================
 Name        : collision_avoidance.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "CA.h"
//variables
int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 50 ;
//state pointer to function
void (*CA_state)();


void US_Set_distance(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	printf("US -------distance = %d-------->CA\n",CA_distance);

}

STATE_define(CA_waiting)
{
	//state nane
	CA_state_id = CA_waiting;
	printf("CA wating state : distance = %d speed=%d \n",CA_distance,CA_speed);
	//state action
	CA_speed=0;
	DC_motor(CA_speed);

}


STATE_define(CA_driving)
{
	//state nane
	CA_state_id = CA_driving;
	printf("CA driving state : distance = %d speed=%d \n",CA_distance,CA_speed);

	CA_speed=30;
	//state action

	DC_motor(CA_speed);

}


