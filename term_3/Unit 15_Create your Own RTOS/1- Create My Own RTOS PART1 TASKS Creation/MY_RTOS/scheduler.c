/*
 * scheduler.c
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */

#include "scheduler.h"
#include "MY_RTOS_FIFO.h"

void MY_RTOS_idel_Task();


struct {
	Task_ref *OS_Tasks[100]; //scheduler table
	unsigned int _S_MSP_Task;
	unsigned int _E_MSP_Task;
	unsigned int PSP_Task_Locator;
	unsigned int NoOfActiveTasks;  //number of created tasks
	Task_ref* Current_Task;
	Task_ref* Next_Task;
	enum {
		OS_Suspend,
		OS_Running
	}OS_Mode_ID;
}OS_CONROL;


FIFO_Buf_t Ready_Queue;
Task_ref*  Ready_Queue_FIFO[100];
Task_ref MY_RTOS_IDEL_Task;


// to execute specific service
void OS_SVC_Services(int * Stack_Frame_Pointer)
{
	//OS_SVC_Set Stack -> R0 -> argument 0 -> Stack_Frame_Pointer
	//OS_SVC_Set Stack : {R0,R1,R2,R3,R12,LR,PC,XPSR} (return to PC - 2 to reach the SVC number)
	unsigned char SVC_number;
	SVC_number = *((unsigned char *)((unsigned char *)Stack_Frame_Pointer[6])-2);

	switch(SVC_number)
	{
	case 0:	//Activate Task

		break;
	case 1:	//Terminate Task

		break;
	case 2:	//

		break;
	case 3:	//

		break;
	}
}



void PendSV_Handler ()
{

}


int OS_SVC_Set(int SVC_ID)
{
	switch(SVC_ID)
	{
	case 0:	//Activate Task
			__asm("SVC #0x00");
			break;
	case 1:	//Terminate Task
		__asm("SVC #0x01");
		break;
	case 2:	//
		__asm("SVC #0x02");
		break;
	case 3://PendSV
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;

	}

}


void MY_RTOS_Create_MainStack()
{
	OS_CONROL._S_MSP_Task =  &_estack;
	OS_CONROL._E_MSP_Task = OS_CONROL._S_MSP_Task- Main_Stack_Size;
	//Algned 8 Bytes Space between Main Task & PSP Tasks
	OS_CONROL.PSP_Task_Locator = (OS_CONROL._E_MSP_Task - 8);

}
MY_RTOS_ErrorID MY_RTOS_init (void)
{
	MY_RTOS_ErrorID error = NoError;

	//update OS mode (OS_Suspended)
	OS_CONROL.OS_Mode_ID = OS_Suspend;

	//specify the main stack for OS
	MY_RTOS_Create_MainStack();
	//Create OS Ready Queue
	if(FIFO_init(&Ready_Queue,Ready_Queue_FIFO,100) != FIFO_no_error)
	{
		error += Ready_Queue_init_error;
	}

	//configure idle Task
	strcpy(MY_RTOS_IDEL_Task.Task_Name,"IDEL_Task");
	MY_RTOS_IDEL_Task.priority = 255;
	MY_RTOS_IDEL_Task.p_TaskEntry =MY_RTOS_idel_Task;
	MY_RTOS_IDEL_Task.stack_size = 300;

	error += MY_RTOS_Creat_Task(&MY_RTOS_IDEL_Task);






	return error;
}

void MY_RTOS_idel_Task()
{
	while(1)
	{
		__asm("NOP");
	}
}

void MY_RTOS_Create_TaskStack(Task_ref* Tref)
{
	/* Task Frame
	 * ==========
	 * XPSR
	 * PC (Next task instruction which should be Run)
	 * LR (return register which is saved in CPU while Task1 running before Task Switching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 * ===========
	 * r5, r6, r7, r8, r9, r10, r11 (Saved/Restored Manually)
	 */
	Tref->Current_PSP = Tref->_S_PSP_Task;
	Tref->Current_PSP --;
	*(Tref->Current_PSP) = 0x01000000; //Dummy _XPSR should T = 1 to avoid bus fault //0x01000000

	Tref->Current_PSP --;
	*(Tref->Current_PSP) = (unsigned int) Tref -> p_TaskEntry; //PC

	Tref->Current_PSP --; // LR = 0xFFFFFFFD (EXC_RETURN) Returns to thread with PSP
	*(Tref->Current_PSP) = 0xFFFFFFFD;

	for (int j=0 ; j<13 ; j++) // to intialize all the 13 register (r0 -> r12) to be ZERO
	{
		Tref ->Current_PSP--;
		*(Tref->Current_PSP) = 0;
	}
}

MY_RTOS_ErrorID MY_RTOS_Creat_Task(Task_ref* Tref)
{
	MY_RTOS_ErrorID error = NoError;

	// Create it's  own PSP Stack
	Tref -> _S_PSP_Task = OS_CONROL.PSP_Task_Locator;
	Tref -> _E_PSP_Task = Tref -> _S_PSP_Task - Tref -> stack_size;


	// Check task stack size exceeded the PSP stack
	if (Tref -> _E_PSP_Task < (unsigned int) (&(_eheap)))
	{
		return Task_exceeded_StackSize;
	}

	// Aligned 8 bytes between Task PSP and other
	OS_CONROL.PSP_Task_Locator = (Tref->_E_PSP_Task - 8);

	//Initialize PSP Task Stack
	MY_RTOS_Create_TaskStack(Tref);


	// Task State update -> Suspend
	Tref->Task_State = Suspend;


	return error;

}



















