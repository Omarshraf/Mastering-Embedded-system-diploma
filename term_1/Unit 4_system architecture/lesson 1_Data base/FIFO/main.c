/*
 * main.c
 *
 *  Created on: May 20, 2023
 *      Author: Omar
 */
#include "fifo.h"
#define width 5
element_type uart_buffer[width];


int main (void){
	element_type i,temp=0;
	FIFO_Buf_t FIFO_UART;
	if(FIFO_init(&FIFO_UART, uart_buffer, width)==FIFO_no_error)
		printf("%%%%%FIFO init is done%%%%%\n");
	for (i=0;i<7;i++){
		printf("FIFO enqueue (%x)\n",i);
		if(FIFO_enqueue(&FIFO_UART, &i)==FIFO_no_error)
			printf("%%%%FIFO enqueue is done%%%%%\n");
		else
			printf("FIFO enqueue is faild\n");

	}
	FIFO_print(&FIFO_UART);
	if(FIFO_dequeue(&FIFO_UART, &temp)==FIFO_no_error)
		printf("FIFO dequeue %x ---->Done\n",temp);
	if(FIFO_dequeue(&FIFO_UART, &temp)==FIFO_no_error)
		printf("FIFO dequeue %x ---->Done\n",temp);
	FIFO_print(&FIFO_UART);
}
