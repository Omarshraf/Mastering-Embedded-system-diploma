/*Write a program in C to print the elements of an array in reverse order.
 ============================================================================
 Name        : ex4.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	int arr[5],i;
	int* ptr;
	for(i=0;i<5;i++){
		ptr=arr+i;
		printf("element-%d: ",i+1);
		fflush(stdout); fflush(stdin);
		scanf("%d",ptr);
	}

	printf("The elements of array in reverse order are :\n");
	for(i=5;i>0;i--){
			printf("element-%d: %d\n ",i,*ptr);
			ptr--;
		}
}
