/*
 * US.c
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */
#include "US.h"
extern void (*US_state)();


// variables
unsigned int US_distance=0;
//state pointer to function
int US_Get_distance_random(int l, int r,int count);
void US_init()
{
	//init US Driver
	printf("US_init \n");
}
STATE_define(US_busy){
	//state_name
	US_state_id = US_busy;
	//state_action
	US_distance = US_Get_distance_random(45, 55, 1);
	printf("US_Waiting state: distance =%d \n",US_distance);
	US_Set_distance(US_distance);
	US_state = STATE(US_busy);

}





int US_Get_distance_random(int l, int r, int count){
	//this will generate random number in range l and r
	int i;
	for (i = 0; i < count; ++i) {
		int rand_num=(rand()%(r - l + 1)) + l;
		return rand_num;

	}
}
