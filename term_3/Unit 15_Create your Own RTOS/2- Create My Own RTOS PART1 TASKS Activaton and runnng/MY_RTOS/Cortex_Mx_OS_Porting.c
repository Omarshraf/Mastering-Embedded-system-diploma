/*
 * Cortex_Mx_OS_Porting.c
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */

#include "Cortex_Mx_OS_Porting.h"

unsigned char SysTickLED;

  void HardFault_Handler(void)
  {
	  while(1);
  }
  void	MemManage_Handler(void)
  {
	  while(1);
  }
  void	BusFault_Handler(void)
  {
	  while(1);
  }
  void	UsageFault_Handler(void)
  {
	  while(1);
  }




  __attribute((naked)) void SVC_Handler ()	//Don't create a stack for this function
  {

  	__asm("TST LR, #0x04 \n\t"
  			"ITE EQ \n\t"
  			"MRSEQ R0, MSP \n\t"
  			"MRSNE R0, PSP \n\t"
  			"B OS_SVC_Services");
  }



  void HW_init()
  {
	  // initialize ClockTree (RCC -> Systick Timer & CPU ) 8MHz
	  // init HW
	  // 8MHz
	  // 1 count -> 0.125 us
	  // x count -> 1 ms
	  // x = 8000 count


	  //decrease PendSV interrupt priority to be smaller than or equal SysTick Timer.
	  //SysTick have a priority 14
	  __NVIC_SetPriority(PendSV_IRQn, 15);

  }



void OS_trigger_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}




void Start_Ticker()
{
	// 8MHz
	// 1 count -> 0.125 us
	// x count -> 1 ms
	// x = 8000 count

	SysTick_Config(8000);
}


void SysTick_Handler(void)
{
	SysTickLED ^= 1;
	//determine Pcurrent & Pnext
	Decide_whatNext();
	//Switch Context & Restore
	OS_trigger_PendSV();
}




