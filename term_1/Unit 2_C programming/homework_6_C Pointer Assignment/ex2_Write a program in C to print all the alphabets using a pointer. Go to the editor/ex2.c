/* ex2_Write a program in C to print all the alphabets using a pointer.
 ============================================================================
 Name        : ex2.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	char alph []="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ptr=alph;
	for(int i=0;i<26;i++){
		printf("%c  ",*ptr);
		ptr++;
	}
}
