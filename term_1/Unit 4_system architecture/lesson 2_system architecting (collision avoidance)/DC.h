/*
 * DC.h
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */

#ifndef DC_H_
#define DC_H_
#include "state.h"
//Define States
enum{
	DC_ideal,
	DC_busy
}DC_state_id;

//declare states functions DC
void DC_init();
STATE_define(DC_ideal);
STATE_define(DC_busy);



//State pointer to function
extern void (*DC_state)();


#endif /* DC_H_ */
