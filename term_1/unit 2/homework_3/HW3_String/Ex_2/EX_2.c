/* C Program to find the Length of a String
 ============================================================================
 Name        : EX_2.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	char text[100];
	int i;
	printf("Enrter a string: ");
	fflush(stdin);fflush(stdout);
	gets(text);
	for(i=0;text[i]!=0;i++);
	printf("Length of string: %d",i);
}
