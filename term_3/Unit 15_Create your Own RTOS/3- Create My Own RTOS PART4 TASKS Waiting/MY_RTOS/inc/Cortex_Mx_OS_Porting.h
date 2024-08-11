/*
 * Cortex_Mx_OS_Porting.h
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */

#ifndef INC_CORTEX_MX_OS_PORTING_H_
#define INC_CORTEX_MX_OS_PORTING_H_
#include "core_cm3.h"


extern int _estack;
extern int _eheap;
#define Main_Stack_Size						3072

#define OS_SET_PSP(add)						__asm volatile("mov R0 , %0 \n\t msr PSP, R0" :   :"r" (add))
#define OS_GET_PSP(add)						__asm volatile("mrs R0 , PSP \n\t mov %0, R0"     :"=r" (add))

#define OS_SWITCH_SP_TO_PSP					__asm volatile("MRS R0, CONTROL \n\t MOV R1,#0X02 \n\t ORR R0, R0,R1 \n\t MSR CONTROL, R0")
#define OS_SWITCH_SP_TO_MSP					__asm volatile("MRS R0, CONTROL \n\t MOV R1,#0X05 \n\t AND R0, R0,R1 \n\t MSR CONTROL, R0")



//clear bit 0 in CONTROL Register
#define OS_SWITCH_TO_privileged				__asm("MRS R0 ,CONTROL \n\t"  \
												  "LSR R0, #1 \n\t"       \
												  "LSL R0, #1 \n\t"       \
												  "MSR CONTROL, R0");


//set bit 0 in CONTROL Register
#define OS_SWITCH_TO_unprivileged			 __asm("MRS R0 ,CONTROL \n\t" \
												   "ORR R0,#1\n\t"        \
												   "MSR CONTROL, R0");





void OS_trigger_PendSV();
void Start_Ticker();

#endif /* INC_CORTEX_MX_OS_PORTING_H_ */
