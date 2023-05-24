/*
 * state.h
 *
 *  Created on: May 24, 2023
 *      Author: Omar
 */

#ifndef STATE_H_
#define STATE_H_
#include "stdio.h"
#include "stdlib.h"
//Automatic State function generated
#define STATE_define(_statfun_) void ST_##_statfun_()
#define STATE(_statfun_)  ST_##_statfun_

//states connection
void US_Set_distance (int d);
void DC_motor (int s);




#endif /* STATE_H_ */
