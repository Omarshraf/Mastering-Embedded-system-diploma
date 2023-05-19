/* C program to calculate summ of natural numbers
 ============================================================================
 Name        : EX_6.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	int x;
	int y=0;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &x);
	for(int i=1; i<= x ;i++){
		 y+=i;
	}
	printf("Sum = %d",y);
}
