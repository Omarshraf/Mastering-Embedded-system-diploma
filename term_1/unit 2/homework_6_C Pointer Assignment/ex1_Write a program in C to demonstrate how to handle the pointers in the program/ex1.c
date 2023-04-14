/*ex1_Write a program in C to demonstrate how to handle the pointers in the program
 ============================================================================
 Name        : ex1.c
 Author      :Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	int m=29;
	int*ab =&m;
	printf("Address of pointer ab : %x\n",(unsigned int)ab);
	printf("content of pointer ab : %d\n",*ab);
	*ab=34;
	printf("Address of pointer ab : %x\n",(unsigned int)ab);
	printf("Content of pointer ab : %d\n",m);
	m=7;
	printf("Address of m : %x\n",(unsigned int)&m);
	printf("Value of m : %d\n",m);

}
