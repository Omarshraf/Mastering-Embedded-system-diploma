/* write c program to check whether a number is even or odd
 * ex1.c
 *
 *  Created on: Dec 26, 2022
 *      Author: Omar
 */

#include<stdio.h>
void check(){
	int x;
	printf("Enter an integer to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	if(x%2==0)
		printf("%d is even \n",x);
	else
		printf("%d is odd \n",x);

}
int main(){
	check();
	printf("\n");

	check();
}
