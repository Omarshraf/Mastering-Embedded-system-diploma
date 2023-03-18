/* C Programe to Reverse String Without Using Lib. Function (you can only use lib. function strlen())
 ============================================================================
 Name        : EX_3.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
int main(void) {
	int i;
	char text[100], reverse[100];
	int l,ll;
	// get the text to reverse
	printf("Enter the string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	l= strlen(text);
	ll=strlen(text);
	for(i=0;i<l;i++){
		ll--;
		reverse[i]=text[ll];
	}
	reverse[i]=0;
	printf("%s",reverse);

}
/*
 * char text[100];
 * int i;
 * printf("Enter the string");
 * gets(text);
 * for(i=strlen(text)-1;i>=0;i--){
 * putchar (text[1]);
 */
