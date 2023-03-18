/* Write C Program to Multiply two Floating Point Numbers
 * ex4.c
 *
 *  Created on: Dec 26, 2022
 *      Author: Omar
 */
#include<stdio.h>
int main(){
	int x,y;
	printf("Enter two numbers to multiply: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	fflush(stdin); fflush(stdout);
	scanf("%d",&y);
	printf("Product: %d ",x*y);
}
