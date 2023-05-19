/*
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
	int nd,i;
	float sum=0;

	printf("Enter the number of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&nd);
	float num[nd];
	for (i=0;i<nd;i++){
		printf("%d. Enter number: ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&num[i]);

	}
	for(i=0;i<nd;i++){
		sum+=num[i];

	}
	printf("Average= %.2f",sum/nd);
}
