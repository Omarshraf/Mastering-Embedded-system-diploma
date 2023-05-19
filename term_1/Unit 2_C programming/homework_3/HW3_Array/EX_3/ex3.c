/*  transpose matrix
 ============================================================================
 Name        : test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	// recive number of columns and rows from user
	int row, col;
	printf("ENter rows and column of matrix: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&row);
	scanf("%d",&col);

	float a[row][col];
	float t[col][row];
	int r,c;
	//build a matrix
	for(r=0;r<row;r++){
		for(c=0;c<col;c++){
			printf("enter the item a(%d,%d): ",r,c);
			fflush(stdin);fflush(stdout);
			scanf("%f",&a[r][c]);
		}
	}
	//print the matrix
	printf("your matrix is: \n");

	for(r=0;r<row;r++){
		for(c=0;c<col;c++){
			printf("%f  ",a[r][c]);
		}
		printf("\n");
	}



// make the transpose
	for(r=0;r<col;r++){
			for(c=0;c<row;c++){
				t[r][c]=a[c][r];
			}
		}
	//print the transpose
	printf("the transpose matrix is: \n");
	for(r=0;r<col;r++){
		for(c=0;c<row;c++){

			printf("%.2f  ",t[r][c]);
		}
		printf("\n");
	}
}


