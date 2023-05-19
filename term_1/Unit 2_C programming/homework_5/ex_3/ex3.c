/* C Program to add two complex numbers by passing
 * structure to a function.
 ============================================================================
 Name        : ex3.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
// make a structures
struct SComplex {
	float real;
	float imag;
}c1,c2,result;

// make a function to add two structures
void add(struct SComplex c1 ,struct SComplex c2){
	result.real=c1.real+c2.real;
	result.imag=c1.imag+c2.imag;

}


int main(void) {


	for (int i=1;i<=2;i++){
		printf("For %dst complex number \n",i);
		printf("Enter real and imaginary respectively: ");
		switch (i){
		case 1:
		fflush(stdin); fflush(stdout);
		scanf("%f",&c1.real);
		fflush(stdin); fflush(stdout);
		scanf("%f",&c1.imag);
		break;
		case 2:
		fflush(stdin); fflush(stdout);
		scanf("%f",&c2.real);
		fflush(stdin); fflush(stdout);
		scanf("%f",&c2.imag);
		break;

		}
	}
	 add(c1,c2);
	 printf("sum = %.1f+%.1fi",result.real,result.imag);
}
