/* C Program to Search an element in Array
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

	int n,i;
	float e;
	// enter no of array's elements
	printf("Enter no of elements: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	// make an array
	float a[n];
	for (i=0;i<n;i++){
		a[i]=(i+1)*11;
		printf("%.2f   ",a[i]);
	}
	printf("\n");
	// enter the element to search
	printf("Enter the element to be searched: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&e);

	// location of the new element
	for(i=0;i<n;i++){
		if(a[i]==e){
			printf("Number found at the location= %d ",i+1);
			break;
		}
	}
	if(a[i]!=e){
		printf("Number not found");
	}
}
