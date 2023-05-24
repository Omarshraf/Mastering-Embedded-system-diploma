/*
 * US.h
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */

#ifndef US_H_
#define US_H_
#include "state.h"
//define states
enum{
	US_busy
}US_state_id;

//declare states function US
STATE_define(US_busy);

void US_int();
//state pointer to function
void (*US_state)();


#endif /* US_H_ */
