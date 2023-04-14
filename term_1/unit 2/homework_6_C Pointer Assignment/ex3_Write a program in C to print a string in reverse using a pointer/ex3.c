/*Write a program in C to print a string in reverse using a pointer
 ============================================================================
 Name        : ex3.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	char text [100];
	char *ptr;
	int len,i;
	printf("Enter a text: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",text);
	len=strlen(text);
	ptr=text+len-1;
	printf("Reverse of the text: ");
	for(i =0;i<len;i++){
		printf("%c",*ptr);
		ptr--;

	}
}
