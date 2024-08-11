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

typedef enum{
	SVC_Activate_Task,
	SVC_Terminate_Task,
	SVC_Task_Waiting_Time
}SVC_ID;


FIFO_Buf_t Ready_Queue;
Task_ref*  Ready_Queue_FIFO[100];
Task_ref MY_RTOS_IDEL_Task;






__attribute ((naked)) void PendSV_Handler ()
{
	//=====================================
	// Save the Context of the Current Task
	//=====================================
	// Get the current Task "Current PSP from CPU register" as CPU Push XPSR,....,R0
	OS_GET_PSP(OS_CONROL.Current_Task->Current_PSP);

	//using this Current_PSP (Pointer) to store (R4 to R11)
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r4" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r5" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r6" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r7" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r8" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r9" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r10" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP-- ;
	__asm volatile("mov %0 ,r11" : "=r" (*(OS_CONROL.Current_Task->Current_PSP)) );

	//save the Current Value of PSP
	//already saved in Cureent_PSP

	//=====================================
	// Restore the Context of the Next Task
	//=====================================
	OS_CONROL.Current_Task = OS_CONROL.Next_Task;
	OS_CONROL.Next_Task = NULL;
	__asm volatile("mov r11, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r10, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r9, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r8, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r7, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r6, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r5, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;
	__asm volatile("mov r4, %0" : : "r" (*(OS_CONROL.Current_Task->Current_PSP)) );
	OS_CONROL.Current_Task->Current_PSP++ ;


	// Update PSP and exit
	OS_SET_PSP(OS_CONROL.Current_Task->Current_PSP);
	__asm volatile ("BX LR");



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

unsigned char idel_TaskLED;
void MY_RTOS_idel_Task()
{
	while(1)
	{
		idel_TaskLED ^= 1;
		__asm("wfe");
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
	Tref->Current_PSP = (unsigned int*)Tref->_S_PSP_Task;
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

	// Update Scheduler Table
	OS_CONROL.OS_Tasks[OS_CONROL.NoOfActiveTasks] = Tref;
	OS_CONROL.NoOfActiveTasks++;


	// Task State update -> Suspend
	Tref->Task_State = Suspend;


	return error;

}


//handler Mode
void bubbleSort()
{
	unsigned int i,j,n;
	Task_ref* Temp;
	n = OS_CONROL.NoOfActiveTasks;
	for(i=0 ; i < n ; i++)
	{
		for(j=0 ;j< n-i-1;j++)
		{
			if(OS_CONROL.OS_Tasks[j]->priority > OS_CONROL.OS_Tasks[j+1]->priority)
			{
				Temp = OS_CONROL.OS_Tasks[j];
				OS_CONROL.OS_Tasks[j] = OS_CONROL.OS_Tasks[j+1];
				OS_CONROL.OS_Tasks[j +1] = Temp;
			}
		}
	}
}

//handler mode
void MY_RTOS_Update_Scheduler_Table()
{
	Task_ref* Temp = NULL;
	Task_ref* Ptask;
	Task_ref* PnextTask;
	int i =0;

	// 1- bubble sort scheduler table OS_CONTROL-> OS_Tasks[100] (priority high then low)
	bubbleSort();
	// 2- free Ready Queue
	while(FIFO_dequeue(&Ready_Queue, &Temp) != FIFO_empty);

	// 3- Update Ready Queue
	while(i<OS_CONROL.NoOfActiveTasks)
	{
		Ptask = OS_CONROL.OS_Tasks[i];
		PnextTask = OS_CONROL.OS_Tasks[i+1];
		if(Ptask->Task_State != Suspend)
		{
			//in case we reached to the end of available OS_Tasks
			if(PnextTask -> Task_State == Suspend)
			{
				FIFO_enqueue(&Ready_Queue, Ptask);
				Ptask -> Task_State = Ready;
				break;
			}

			//if the Ptask priority > PnextTask then (lowest numbers means highest priority)
			if(Ptask -> priority < PnextTask -> priority )
			{
				FIFO_enqueue(&Ready_Queue, Ptask);
				Ptask -> Task_State = Ready;
				break;
			}else if (Ptask -> priority == PnextTask -> priority)
			{
				//if the Ptask priority == PnextTask then
				//		push Ptask to ready state
				//and make the Ptask = PnextTask and PnextTask++

				FIFO_enqueue(&Ready_Queue, Ptask);
				Ptask -> Task_State = Ready;

			}else if (Ptask -> priority > PnextTask -> priority)
			{
				//not allowed to happen as we already reordered it by bubble sort
				break;

			}



		}


		i++;
	}
}

//handler mode
void Decide_whatNext()
{
	//if Ready Queue is empty && OS_CONTROL -> CurrentTask != suspend
	if (Ready_Queue.count == 0 && OS_CONROL.Current_Task -> Task_State != Suspend) //FIFO is empty
	{
		OS_CONROL.Current_Task->Task_State = Running;
		//add the current task again (round robin)
		FIFO_enqueue(&Ready_Queue, OS_CONROL.Current_Task);
		OS_CONROL.Next_Task = OS_CONROL.Current_Task;

	}else
	{
		FIFO_dequeue(&Ready_Queue, &OS_CONROL.Next_Task);
		OS_CONROL.Next_Task->Task_State = Running;
		//update Ready Queue (To Keep round robin Algo. happen)
		if((OS_CONROL.Current_Task->priority == OS_CONROL.Next_Task->priority) && (OS_CONROL.Current_Task->Task_State != Suspend))
		{
			FIFO_enqueue(&Ready_Queue, OS_CONROL.Current_Task);
			OS_CONROL.Current_Task->Task_State =Ready;

		}
	}
}

// to execute specific service
//handler mode
void OS_SVC_Services(int* StackFrame)
{
	//r0,r1,r2,r3,r12,LR,return Address (PC) and XPSR
	unsigned char SVC_Number;

	SVC_Number = *((unsigned char*)(((unsigned char*) StackFrame[6])-2));
	switch (SVC_Number) {
		case SVC_Activate_Task:
		case SVC_Terminate_Task:
			// Update Scheduler Table, Ready Queue
			MY_RTOS_Update_Scheduler_Table();
			// OS is in Running State
			if (OS_CONROL.OS_Mode_ID == OS_Running)
			{
				if(strcmp(OS_CONROL.Current_Task->Task_Name , "IDEL_Task") != 0)
				{
					//Decide what next
					Decide_whatNext();
					//trigger OS_PendSV (Switch Context/Restore)
					OS_trigger_PendSV();

				}
			}
						break;
		case SVC_Task_Waiting_Time:
			MY_RTOS_Update_Scheduler_Table();

			break;
		default:
			break;
	}
}


//Thread Mode
MY_RTOS_OS_SVC_Set(SVC_ID ID)
{
	switch(ID)
	{
		case SVC_Activate_Task:
			__asm("SVC #0x00");

			break;
		case SVC_Terminate_Task:
			__asm("SVC #0x01");

			break;

		case SVC_Task_Waiting_Time:
			__asm("SVC #0x02");

			break;
	}
}

void MY_RTOS_ActivateTask(Task_ref* Tref)
{
	Tref ->Task_State = Waitng;
	MY_RTOS_OS_SVC_Set(SVC_Activate_Task);

}
void MY_RTOS_TerminateTask(Task_ref* Tref)
{
	Tref ->Task_State = Suspend;
	MY_RTOS_OS_SVC_Set(SVC_Terminate_Task);
}

void MY_RTOS_TaskWait(unsigned int NoTicks, Task_ref* SelfTref)
{
	SelfTref->TimngWaiting.Blocking = enable;
	SelfTref->TimngWaiting.Ticks_Count = NoTicks;
	// Task should be blocked
	SelfTref->Task_State = Suspend;
	// to be suspended immediately
	MY_RTOS_OS_SVC_Set(SVC_Terminate_Task);

}



void MY_RTOS_STARTOS()
{
	OS_CONROL.OS_Mode_ID = OS_Running;
	//Set Default "Current Task  = Idle Task"
	OS_CONROL.Current_Task = &MY_RTOS_IDEL_Task;
	//Activate IDLE Task
	MY_RTOS_ActivateTask(&MY_RTOS_IDEL_Task);
	//Start Ticker
	Start_Ticker(); //1ms

	OS_SET_PSP(OS_CONROL.Current_Task->Current_PSP);

	//switch Thread Mode SP from MSP to PSP
	OS_SWITCH_SP_TO_PSP;
	OS_SWITCH_TO_unprivileged;
	OS_CONROL.Current_Task->p_TaskEntry();

}


void MY_RTOS_Update_TaskWaitingTime()
{
	for(int i =0 ; i < OS_CONROL.NoOfActiveTasks ; i++)
	{
		if (OS_CONROL.OS_Tasks[i]->Task_State == Suspend)
		{
			if (OS_CONROL.OS_Tasks[i]->TimngWaiting.Blocking == enable)
			{
				OS_CONROL.OS_Tasks[i]->TimngWaiting.Ticks_Count--;
				if (OS_CONROL.OS_Tasks[i]->TimngWaiting.Ticks_Count == 1)
				{
					OS_CONROL.OS_Tasks[i]->TimngWaiting.Blocking = disable;
					OS_CONROL.OS_Tasks[i]->Task_State = Waitng;
					MY_RTOS_OS_SVC_Set(SVC_Task_Waiting_Time);
				}
			}
		}
	}
}






