/* C program to check Whether a number is positive or negative
 ============================================================================
 Name        : EX_4.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	float num;
	printf("Enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&num);
	if(num>0){
		printf("%.2f is positive.",num);
	}
	else if(num<0){
			printf("%.2f is negative.",num);
		}
	else{
				printf("You enterd zero.");
			}
}
