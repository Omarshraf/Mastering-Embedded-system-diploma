/*
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

	int n,i,l;
	float e;
	// enter no of array's elements
	printf("Enter no of elements: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	// make an array
	float a[n];
	for (i=0;i<n;i++){
		a[i]=i+1;
		printf("%.2f   ",a[i]);
	}
	printf("\n");
	// enter the element to insert
	printf("Enter the element to be inserted: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&e);

	// location of the new element
	printf("Enter the loction: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&l);

	for (i=0;i<n;i++){
			if(i==l-1){
				a[i]=e;
			}
			printf("%.2f   ",a[i]);
		}

}
