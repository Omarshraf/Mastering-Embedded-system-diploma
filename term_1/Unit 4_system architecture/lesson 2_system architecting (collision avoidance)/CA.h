/*
 * CA.h
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
enum{
	CA_waiting,
	CA_driving,

}CA_state_id;

//prototypes
STATE_define(CA_waiting);
STATE_define(CA_driving);
//global pointer to function
extern void (*CA_state)();


#endif /* CA_H_ */
