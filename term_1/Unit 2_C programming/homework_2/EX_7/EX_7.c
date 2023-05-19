/* C Program to Find Factorial of a Number
 ============================================================================
 Name        : EX_7.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	int n;
	int f=1;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	if(n>=0){

		for(int i=1; i<=n; i++){

			f=f*i;
		}
		printf("Factorial = %d",f);
	}
	else{
		printf("Error!!! Factorial of negative number doesn't exist.");
	}

}
