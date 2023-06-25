/*
 ============================================================================
 Name        : credit_hours.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "credit.h"
#include <stdio.h>

fifo_buf_t student_fifo;
int main()
{


	if(FIFO_init(&student_fifo,buffer,50)==FIFO_no_error){

		int choise;
		while(1){

			printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
			printf("================Student Data============\n");
			printf("1: Add Student Details From File\n");
			printf("2: Add Student Details Manually\n");
			printf("3: Find the Student by given roll number\n");
			printf("4: Find the Student by given first name\n");
			printf("5: Find the Student registered in a course\n");
			printf("6: count of Student\n");
			printf("7: Delete a Student\n");
			printf("8: update Student\n");
			printf("9: Show Student Information\n");
			printf("10: Exit\n");
			printf("=========================================\n");
			printf("Enter your choise number (1,2,3,....,10): ");
			fflush(stdin);fflush(stdout);
			scanf("%d",&choise);
			printf("=========================================\n");
			switch(choise){
			case 1:
			{
				AddStudentFrom_txt(&student_fifo);
			}
			break;
			case 2:
			{
				AddStudentManually(&student_fifo);
			}
			break;
			case 3:
			{
				FindStudentByRoll(&student_fifo);
			}
			break;
			case 4:
			{
				FindStudentByName(&student_fifo);
			}
			break;
			case 5:
			{
				FindStudentsRegisteredInCourse(&student_fifo);
			}
			break;
			case 6:
			{
				count_of_students(&student_fifo);
			}
			break;
			case 7:
			{
				DeleteStudent(&student_fifo);
			}
			break;
			case 8:
			{
				UpdateStudent(&student_fifo);
			}
			break;
			case 9:
			{
				ShowAllInformation(&student_fifo);
			}
			break;
			case 10:
			{
				printf("==============system is clossing===============\n");
				return 1;
			}
			break;
			default:
			{
				printf("Error: Wrong choise\n");
			}
			break;

			}
		}
	}
	else
		printf("ERORR");
	return 0;
}
