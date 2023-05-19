/* c program to caculate factorial of a number using
 * recursion
 ============================================================================
 Name        : ex2.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int factorial (int x){
	if(x==0){
		return 1;
	}
	else{
		return x* factorial(x-1);
	}
}
int main(void) {
	int x;
	printf("Enter a Positive integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	printf("%d",factorial(x));
}
