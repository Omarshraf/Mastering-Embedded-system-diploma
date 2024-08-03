/*
 * MY_RTOS_FIFO.h
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */

#ifndef INC_MY_RTOS_FIFO_H_
#define INC_MY_RTOS_FIFO_H_


#include "stdio.h"
#include "stdint.h"
#include "scheduler.h"

//select element type
#define element_type Task_ref*


//fifo data type
typedef struct{
	unsigned int length;
	unsigned int count;
	element_type* head;
	element_type* base;
	element_type* tail;
}FIFO_Buf_t;

typedef enum{
	FIFO_no_error,
	FIFO_empty,
	FIFO_full,
	FIFO_null,
}FIFO_Buf_status;

//FIFO APIs
FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo,element_type* buff,uint32_t length);
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo,element_type* item);
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo,element_type* item);
FIFO_Buf_status FIFO_is_full(FIFO_Buf_t* fifo);
void FIFO_print(FIFO_Buf_t* fifo);
FIFO_Buf_status FIFO_is_empty(FIFO_Buf_t* fifo);









#endif /* INC_MY_RTOS_FIFO_H_ */
