/* C porgram to find area of a circle, passing argument to macros.
 * [Area of circle = pi*r2]
 ============================================================================
 Name        : ex5.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#define circular_area(r) 3.14*r*r

int main(void) {

	float r,a;
	printf("Enter the radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&r);
	a= circular_area(r);
	printf("Area= %.2f",a);
}
