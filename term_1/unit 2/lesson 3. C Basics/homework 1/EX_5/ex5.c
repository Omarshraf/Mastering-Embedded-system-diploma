/* Write C Program to Find ASCII Value of a Character
 * ex5.c
 *
 *  Created on: Dec 26, 2022
 *      Author: Omar
 */
#include<stdio.h>
int main(){
	char x;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);
	printf("ASCII value of %c = %d",x,x);
}

