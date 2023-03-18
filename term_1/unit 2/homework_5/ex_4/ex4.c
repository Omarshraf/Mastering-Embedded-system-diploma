/*
 ============================================================================
 Name        : ex4.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct SStudents{
	int roll;
	char name[20];
	float marks;
}students[10];
int main(void) {
	printf("Enter information of students: \n");
	for(int i=0;i<10;i++){
		printf("For roll number: ");
		fflush(stdin);fflush(stdout);
		scanf("%d",&students[i].roll);

		printf("Enter name: ");
		fflush(stdin);fflush(stdout);
		scanf("%s",&students[i].name);

		printf("Enter marks: ");
		fflush(stdin);fflush(stdout);
		scanf("%f",&students[i].marks);

	}
	printf("\n \n");
	printf("Displaying information of students:\n ");
	for(int i=0;i<10;i++){
		printf("Information for roll number: %d\n",students[i].roll);
		printf("Name: %s\n",students[i].name);
		printf("Name: %.1f\n",students[i].marks);
	}
}
