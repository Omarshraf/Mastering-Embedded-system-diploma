/* C program to calculate the power of a number using recursion
 ============================================================================
 Name        : ex4.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>

double power(float base, int exponent);

int main() {
	float base;
	int exponent;

	printf("Enter the base number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f", &base);

	printf("Enter the exponent: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &exponent);

	float result = power(base, exponent);

	printf("%.2f^%d = %.2f\n", base, exponent, result);

	return 0;
}

double power(float base, int exponent) {
	if (exponent == 0) {
		return 1;
	} else if (exponent < 0) {
		return 1 / power(base, -exponent);
	} else {
		return base * power(base, exponent - 1);
	}
}

