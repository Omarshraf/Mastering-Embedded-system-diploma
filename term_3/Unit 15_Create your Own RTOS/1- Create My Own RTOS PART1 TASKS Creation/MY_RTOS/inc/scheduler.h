/*
 * scheduler.h
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "Cortex_Mx_OS_Porting.h"


typedef enum {
	NoError,
	Ready_Queue_init_error,
	Task_exceeded_StackSize

}MY_RTOS_ErrorID;


typedef struct{
	unsigned int stack_size;
	unsigned char priority;
	void (*p_TaskEntry) (void); //Pointer to task C Function
	unsigned char AutoStart;
	unsigned int _S_PSP_Task;   //not Entered by the user
	unsigned int _E_PSP_Task;   //not Entered by the user
	unsigned int* Current_PSP;   //not Entered by the user
	char Task_Name[30];
	enum {
		Suspend,
		Running,
		Waitng,
		Ready
	}Task_State;				//not Entered by the user
	struct {
		enum{
			enable,
			disable
		}Blocking;
		unsigned int Ticks_Count;
	}TimngWaiting;
}Task_ref;



//APIs
MY_RTOS_ErrorID MY_RTOS_init();
MY_RTOS_ErrorID MY_RTOS_Creat_Task(Task_ref* Tref);



#endif /* INC_SCHEDULER_H_ */
