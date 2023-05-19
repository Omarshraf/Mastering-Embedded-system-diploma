/*
 * main.c
 *
 *  Created on: May 19, 2023
 *      Author: Omar
 */
#include "lifo.h"
#include "stdio.h"
unsigned int buf[5];

void main(){
	int i,temp;
	Lifo_Buf_t uart_lifo;
	LIFO_init_item (&uart_lifo,&buf,5);
	for (i = 0; i < 5; ++i) {
		if(LIFO_add_item(&uart_lifo, i)==lifo_no_error)
			printf("Lifo add: %d \n",i);
	}
	printf("\n\n");

	for (i = 0; i < 5; ++i) {
		if(LIFO_get_item(&uart_lifo, &temp)==lifo_no_error)
			printf("Lifo get: %d \n",temp);
	}

}

