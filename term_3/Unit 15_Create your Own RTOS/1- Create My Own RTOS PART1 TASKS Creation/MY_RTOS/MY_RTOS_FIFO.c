/*
 * MY_RTOS_FIFO.c
 *
 *  Created on: Jul 20, 2024
 *      Author: Omar
 */



#include <stdio.h>
#include "MY_RTOS_FIFO.h"


//FIFO APIs
FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo,element_type* buff,uint32_t length)
{
	if (buff==NULL)
		return FIFO_null;

	fifo->base = buff;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->count = 0;
	fifo->length = length;

	return FIFO_no_error;

}
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo,element_type* item)
{
	if (!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	//Check fifo is full or not
	if(FIFO_is_full(fifo) == FIFO_full)
		return FIFO_full;
	*(fifo->head)=*item;
	fifo->count++;
	if(fifo->head==(fifo->base + (fifo->length * sizeof(element_type))))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;


}
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo,element_type* item)
{
	if (!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	//Check fifo is empty or not
	if(FIFO_is_empty(fifo) == FIFO_empty){
		printf("FIFO is empty\n");
		return FIFO_empty;
	}
	//dnqueue an item
	*item = *(fifo->tail);
	fifo->count--;
	if(fifo->tail==(fifo->base + (fifo->length * sizeof(element_type))))
			fifo->tail = fifo->base;
		else
			fifo->tail++;

return FIFO_no_error;


}
FIFO_Buf_status FIFO_is_full(FIFO_Buf_t* fifo)
{
	if (!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;

	//Check if fifo is full or not
	if(fifo->count == fifo->length){
		printf("FIFO is full\n");
		return FIFO_full;
	}
	return FIFO_no_error;
}
FIFO_Buf_status FIFO_is_empty(FIFO_Buf_t* fifo)
{
	if (!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	if(fifo->count == 0)
		return FIFO_empty;
	else
		return FIFO_no_error;
}

void FIFO_print(FIFO_Buf_t* fifo)
{
	element_type* temp;
	int i;
	if(fifo->count==0)
		printf("FIFO is Empty");
	else{
		temp = fifo->tail;
		printf("\n=========FIFO is print===========\n");
		for(i=0;i<fifo->count;i++){
			printf("\t %x \n",*temp);
			temp++;

		}
		printf("\n========================\n");
	}

}
