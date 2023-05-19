/*
 ============================================================================
 Name        : LIFO.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "lifo.h"
#include <stdio.h>
lifo_status LIFO_add_item (Lifo_Buf_t* lifo_buf,unsigned int item ){
	//lifo is valid
	if (!lifo_buf->base || !lifo_buf->head)return lifo_null;
	//lifo is full
	if (lifo_buf->count == lifo_buf->length )return lifo_full;

	//add value
	*(lifo_buf->head)=item;
	lifo_buf->head++;
	lifo_buf->count++;
	return lifo_no_error;
}


lifo_status LIFO_get_item (Lifo_Buf_t* lifo_buf,unsigned int* item ){
	//lifo is valid
	if (!lifo_buf->base || !lifo_buf->head)return lifo_null;
	//lifo is empty
	if (lifo_buf->count==0)return lifo_empty;
	//get value
	lifo_buf->head--;
	*item=*(lifo_buf->head);
	lifo_buf->count--;

	return lifo_no_error;

}


lifo_status LIFO_init_item (Lifo_Buf_t* lifo_buf,unsigned int buf,unsigned int length){
	if(buf==NULL)return lifo_null;
	lifo_buf->base =buf;
	lifo_buf->head =buf;
	lifo_buf->count =0;
	lifo_buf->length =length;
	return lifo_no_error;


}
