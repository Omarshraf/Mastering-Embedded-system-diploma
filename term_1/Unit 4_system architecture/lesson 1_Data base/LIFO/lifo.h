/*
 * LIFO.h
 *
 *  Created on: May 19, 2023
 *      Author: Omar
 */

#ifndef LIFO_H_
#define LIFO_H_


//type definitions
typedef struct{
	unsigned int length;
	unsigned int count ;
	unsigned int* base;
	unsigned int* head;
}Lifo_Buf_t;

typedef enum {
	lifo_no_error,
	lifo_full,
	lifo_empty,
	lifo_null
}lifo_status;


//APIs
lifo_status LIFO_add_item (Lifo_Buf_t* lifo_buf,unsigned int item );
lifo_status LIFO_get_item (Lifo_Buf_t* lifo_buf,unsigned int* item );
lifo_status LIFO_init_item (Lifo_Buf_t* lifo_buf,unsigned int buf,unsigned int length);


#endif /* LIFO_H_ */
