/*
 * credit_hours_test.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Omar
 */

#ifndef CREDIT_HOURS_TEST_H_
#define CREDIT_HOURS_TEST_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char fname [20];
	char lname [20];
	int roll;
	float GPA;
	int cid[5];
}student_t;
typedef struct{
	student_t* tail;
	student_t* head;
	student_t* base;
	unsigned int count;
	unsigned int lengtn;
}fifo_buf_t;
student_t buffer [50];
typedef enum{
	FIFO_no_error,
	FIFO_empty,
	FIFO_full,
	FIFO_null,
}FIFO_Buf_status;
typedef enum{
	ID_found,
	ID_not_found
}ID_status;

FIFO_Buf_status FIFO_init(fifo_buf_t* fifo,student_t* buff,unsigned int length);
void AddStudentManually (fifo_buf_t* student_fifo);
void AddStudentFrom_txt(fifo_buf_t* student_fifo);
void FindStudentByRoll(fifo_buf_t* student_fifo);
void count_of_students(fifo_buf_t* student_fifo);
void ShowAllInformation (fifo_buf_t* student_fifo);
void FindStudentByName(fifo_buf_t* student_fifo);
void FindStudentsRegisteredInCourse(fifo_buf_t* student_fifo);
void UpdateStudent(fifo_buf_t* student_fifo);
void DeleteStudent(fifo_buf_t* student_fifo);
#endif /* CREDIT_HOURS_TEST_H_ */
