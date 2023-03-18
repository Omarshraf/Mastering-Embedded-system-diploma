/*
 ============================================================================
 Name        : EX_1.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	char f;
	int count=0;
	char text[100];
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&f);
	for(int i=0;text[i]!=0;i++){
		if(f==text[i]){
			count++;
		}
	}
	printf("Frequency of %c = %d",f,count);
}
