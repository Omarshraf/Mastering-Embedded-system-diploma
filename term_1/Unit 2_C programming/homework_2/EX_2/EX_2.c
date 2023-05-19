/* C Program to Check Vowel or Consonant
 ============================================================================
 Name        : EX_2.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	char x;
	printf("Enter an alphabet: ");
	fflush(stdout); fflush(stdin);
	scanf("%c",&x);
	printf("\n");
	if (x=='a' || x=='e' || x=='i' || x=='o' || x=='u'|| x=='A' || x=='E' || x=="I" || x=='O' || x=='U'){
		printf("%c is Vowels \n",x);

	}
	else{
		printf("%c is consonant \n",x);
	}

}
