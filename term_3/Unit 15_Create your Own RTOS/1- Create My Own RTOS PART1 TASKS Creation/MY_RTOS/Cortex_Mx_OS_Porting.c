/*
 * Cortex_Mx_OS_Porting.c
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */

#include "Cortex_Mx_OS_Porting.h"

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
  }














