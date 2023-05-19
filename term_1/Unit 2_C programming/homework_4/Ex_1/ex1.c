/*
 ============================================================================
 Name        : ex3.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
void prime_numbers(int x,int y){
	int i,j,f;
	for(i=x;i<y;i++){
		f=0;
		for(j=2;j<i;j++){
			if(i%j==0){
			   f++;
			}

		}
		if(f==0){
			printf("\n %d",i);
		}
	}
}
int main(void) {
	int x,y;
	printf("enter the first number: ");

	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	printf("enter the second number: ");

	fflush(stdin); fflush(stdout);
	scanf("%d",&y);
	prime_numbers(x,y);
}
