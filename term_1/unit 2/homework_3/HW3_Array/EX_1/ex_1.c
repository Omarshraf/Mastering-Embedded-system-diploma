/* the sum of teo matrix of order 2*2 using multidimensional array
 ============================================================================
 Name        : ex_1.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	int r,c;
	float a[2][2];
	float b[2][2];
	printf("Enter the elements of 1st matrix: \n");

	for(r=0;r<2;r++){
		for(c=0;c<2;c++){
			printf("Enter a(%d,%d): ",r,c);
			fflush(stdin); fflush(stdout);
			scanf("%f",&a[r][c]);
		}
	}
	printf("Enter the elements of 2st matrix: \n");

	for(r=0;r<2;r++){
		for(c=0;c<2;c++){
			printf("Enter b(%d,%d): ",r,c);
			fflush(stdin); fflush(stdout);
			scanf("%f",&b[r][c]);
		}
	}
	printf("Sum Of Matrix: \n");
	for(r=0;r<2;r++){
		for(c=0;c<2;c++){
			printf("%.2f   ",(a[r][c]+b[r][c]));

		}
		printf("\n");
	}

}
