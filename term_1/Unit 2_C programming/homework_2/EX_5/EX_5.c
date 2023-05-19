/* C program to check whether a character is an alphabet or not
 ============================================================================
 Name        : EX_5.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	char x;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);
	if (x>=65 && x<=90 || x>=97 && x<=122)
	{
		printf("%c is an alphabet",x);
	}
	else{
		printf("%c is not an alphabet",x);
	}
}
