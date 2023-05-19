/* c program to add two distances (in inch-feet) system
 * using struction
 ============================================================================
 Name        : ex2.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
struct SDistances{
	int feet;
	float inch;
}d1,d2,result;
int main(void) {
	printf("Enter 1st distance\n");

	printf("Enter Feet: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&d1.feet);

	printf("Enter inch: ");
	fflush(stdin);fflush(stdout);
	scanf("%f12",&d1.inch);

	printf("Enter 2st distance\n");

	printf("Enter Feet: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&d2.feet);

	printf("Enter inch: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&d2.inch);

	result.feet=d1.feet+ d2.feet;
	result.inch=d1.inch+ d2.inch;

	while (result.inch>=12.0){
		result.inch =result.inch-12.0;
		++result.feet;

	}
	printf("Sum of distances= %d\'-%.1f\"",result.feet,result.inch);
}
