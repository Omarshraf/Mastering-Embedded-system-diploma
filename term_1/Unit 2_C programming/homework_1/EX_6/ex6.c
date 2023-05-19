/* Write Source Code to Swap Two Numbers
 * ex6.c
 *
 *  Created on: Dec 26, 2022
 *      Author: Omar
 */
#include<stdio.h>
int main(){
	float a,b,c;
	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&a);
	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&b);
	c=a;
	a=b;
	b=c;
	printf("\n");
	printf("\n");
	printf("After sapping, value of a = %.2f \n",a);
	printf("After sapping, value of b = %.2f",b);
}
