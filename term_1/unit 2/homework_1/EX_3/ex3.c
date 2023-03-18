/* Write C Program to Add Two Integers
 * ex3.c
 *
 *  Created on: Dec 26, 2022
 *      Author: Omar
 */
#include<stdio.h>
int main(){
	int x,y;
	printf("Enter two integers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	fflush(stdin); fflush(stdout);
    scanf("%d",&y);
    printf("sum: %d",x+y);
}

