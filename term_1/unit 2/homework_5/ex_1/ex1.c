/* C Program to store information (name,rolland marks)
 * of a Student using structure.
 ============================================================================
 Name        : ex1.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
struct Sstudents{
	char name[50];
	int roll;
	int mark;
};
int main(void) {
	struct Sstudents student;
	printf("Enter information of students: \n");
	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&student.name);
	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&student.roll);
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&student.mark);
	printf("Displaying information\n");
	printf("\n");
	printf("Name: %s\n",student.name);
	printf("Roll: %d\n",student.roll);
	printf("Marks: %d\n",student.mark);

}
