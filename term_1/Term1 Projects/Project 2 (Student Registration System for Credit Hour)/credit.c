/*
 * cridit_hours_test.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Omar
 */
#include <stddef.h>
#include <string.h>
#include "credit.h"
static ID_status ID_check(fifo_buf_t* student_fifo,int ID);
void print_student(student_t* temp);

void AddStudentManually (fifo_buf_t* student_fifo){
	//check buffer is full
	if(student_fifo->count==student_fifo->lengtn){
		printf("the list is full\n");
		return;

	}
	student_t temp;
	printf("==============================\n");
	printf("  Add the Student Details\n");
	printf("==============================\n");
	printf("Enter the Roll Number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&temp.roll);


	if(ID_check(student_fifo,temp.roll)==ID_found){
		printf("This ID is already Exists\n");
		return;
	}


	printf("Enter the first name of the student: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&temp.fname);
	printf("Enter the last name of the student: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&temp.lname);
	printf("Enter the GPA you obtained: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&temp.GPA);
	printf("Enter the course ID of each course:-\n");
	for(int i=0; i<5;i++){
		printf("course %d ID: ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",&temp.cid[i]);
	}
	*student_fifo->tail=temp;
	if (student_fifo->tail == (student_fifo->base + student_fifo->lengtn -1))
		student_fifo->tail = student_fifo->base;
	else
		student_fifo->tail++;

	student_fifo->count++;
	printf("================================================\n");
	printf("     Student Details Added Successfully\n");
	printf("================================================\n");
	count_of_students(student_fifo);

}

void AddStudentFrom_txt(fifo_buf_t* student_fifo)
{
	//check buffer is full
	if(student_fifo->count==student_fifo->lengtn){
		printf("the list is full\n");
		return;

	}

	FILE* Pstudents_file;
	student_t* temp;
	int count = 0;
	Pstudents_file = fopen("student_data.txt","r"); 
	if(Pstudents_file==NULL)
	{
		printf("Student Data can not be open\n");
		return;
	}
	while(!feof(Pstudents_file))
	{
		//check buffer is full while entering the students
		if(student_fifo->count==student_fifo->lengtn){
			printf("the list is full\n");
			return; 
		}
		temp = student_fifo->tail;
		fflush(stdin); fflush(stdout);
		fscanf(Pstudents_file,"%d",temp->roll);
		//Check for Dublicated ID
		if (ID_check(student_fifo, temp->roll)==ID_found)
		{
			printf("The id %d is already Exists\n",temp->roll );
			fscanf(Pstudents_file,"%*[^\n]");
			continue;
		}
		fflush(stdin); fflush(stdout);
		fscanf(Pstudents_file,"%s",*temp->fname);
		fflush(stdin); fflush(stdout);
		fscanf(Pstudents_file,"%s",*temp->lname);
		fflush(stdin); fflush(stdout);
		fscanf(Pstudents_file,"%f",temp->GPA);
		for (int i = 0; i < 5; ++i)
		{
			fflush(stdin); fflush(stdout);
			fscanf(Pstudents_file,"%d",temp->cid[i]);
		}
		if (student_fifo->tail == (student_fifo->base + student_fifo->lengtn -1))
			student_fifo->tail = student_fifo->base;
		else
			student_fifo->tail++;

		student_fifo->count++;
		printf("\n================================================\n");
		printf("    Student with ID (%d) is added Successfully\n",student_fifo->tail->roll );
		printf("\n================================================\n");

		count++;

	}
	fclose(Pstudents_file);



}












FIFO_Buf_status FIFO_init(fifo_buf_t* fifo,student_t* buff,unsigned int length){
	if (buff== NULL)
		return FIFO_null;
	fifo->base=buff;
	fifo->head=fifo->base;
	fifo->tail=fifo->base;
	fifo->count=0;
	fifo->lengtn=length;
	return FIFO_no_error;
}

static ID_status ID_check(fifo_buf_t* student_fifo,int ID){
	student_t* temp= student_fifo->head;
	for(int i=0;i<student_fifo->count;i++){
		if(temp->roll== ID)
			return ID_found;
		if (temp == (student_fifo->base + student_fifo->lengtn -1))
			temp = student_fifo->base;
		else
			temp++;
	}
	return ID_not_found;

}

void count_of_students(fifo_buf_t* student_fifo){
	printf("[INFO] The total number of students is %d\n",student_fifo->count);
	printf("[INFO] You can Add up to %d students\n",student_fifo->lengtn);
	printf("[INFO] You can Add %d more students\n\n\n",student_fifo->lengtn - student_fifo->count);
}

void FindStudentByRoll(fifo_buf_t* student_fifo){
	
	//cheak fifo is empty
	if (student_fifo->count==0){
		printf("The list is empty\n");
		return;
	}
	int id_to_search;
	student_t* temp = student_fifo->head;


	printf("Enter the Roll Number of the student: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&id_to_search);


	if (ID_check(student_fifo,id_to_search)==ID_not_found)
	{
		printf("Not found this ID\n");
		return;
	}
	for (int i = 0; i < student_fifo->count; ++i)
	{
		if(temp->roll==id_to_search)
			print_student(temp);

		if (temp==(student_fifo->base + student_fifo->lengtn - 1))
			temp=student_fifo->base;
		else
			temp++;

	}
	return;
}
void print_student(student_t* temp){
	printf("The Students Details are:-\n");	
	printf("The Student ID: %d\n",temp->roll );
	printf("The First name is %s\n",temp->fname);		
	printf("The Last name is %s\n",temp->lname);
	printf("the GPA is %f\n",temp->GPA);		
	printf("The course ID of each course:-\n");
	for(int i=0; i<5;i++)
		printf("course %d ID is %d\n",i+1,temp->cid[i]);
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	return;
}


void ShowAllInformation (fifo_buf_t* student_fifo){
	//cheak fifo is empty
	if (student_fifo->count==0){
		printf("The list is empty\n");
		return;
	}
	student_t* temp =student_fifo->head;
	for (int i = 0; i < student_fifo->count; ++i){
		print_student(temp);
		printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
		if (temp == (student_fifo->base + student_fifo->lengtn -1))
			temp = student_fifo->base;
		else
			temp++;
	}
	count_of_students(student_fifo);
	return;
}


void FindStudentByName(fifo_buf_t* student_fifo){
	//cheak fifo is empty
	if (student_fifo->count==0){
		printf("The list is empty\n");
		return;
	}
	int j=0;
	char name_to_search[20];
	student_t* temp = student_fifo->head;

	printf("Enter the name of the student: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&name_to_search);
	for (int i = 0; i < student_fifo->count; ++i)
	{
		if(!stricmp(temp->fname,name_to_search) || !stricmp(temp->lname,name_to_search))
		{
			print_student(temp);
			if (student_fifo->tail == (student_fifo->base + student_fifo->lengtn -1))
				student_fifo->tail = student_fifo->base;
			else
				student_fifo->tail++;
			j++;

		}
		else
			if (student_fifo->tail == (student_fifo->base + student_fifo->lengtn -1))
				student_fifo->tail = student_fifo->base;
			else
				student_fifo->tail++;
	}
	if(j==0){
		printf("\n==============================\n");
		printf("     This name in not Found");
		printf("\n==============================\n");

	}

return;


}


void FindStudentsRegisteredInCourse(fifo_buf_t* student_fifo)
{
	//cheak fifo is empty
	if (student_fifo->count==0){
		printf("The list is empty\n");
		return;
	}
	int k=0;
	int cid_to_search;
	student_t* temp = student_fifo->head;
	printf("Enter the course ID to search: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&cid_to_search);

	for (int i = 0; i < student_fifo->count; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if(temp->cid[j] == cid_to_search)
			{
				print_student(temp);
				j=5;
				k++;
			}
		}
		
		if (student_fifo->tail == (student_fifo->base + student_fifo->lengtn -1))
			student_fifo->tail = student_fifo->base;
		else
			student_fifo->tail++;


	}
	if (k==0){
		printf("\n=================================\n");
		printf("    This course ID in not Found");
		printf("\n=================================\n");

	}


}



void UpdateStudent(fifo_buf_t* student_fifo)
{
	//cheak fifo is empty
	if (student_fifo->count==0){
		printf("The list is empty\n");
		return;
	}
	int id_to_search;
	student_t* temp = student_fifo->head;
	int update_choise;

	printf("Enter the Roll Number of the student: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&id_to_search);


	if (ID_check(student_fifo,id_to_search)==ID_not_found)
	{
		printf("Not found this ID\n");
		return;
	}
	for (int i = 0; i < student_fifo->count; ++i)
	{
		if(temp->roll==id_to_search)
		{
			printf("\n\n-------------------------------------------------------------------------\n");
			print_student(temp);
			printf("\n-------------------------------------------------------------------------\n");
			printf("================Student Updata============\n");
			printf("1: student first name\n");
			printf("2: student last name\n");
			printf("3: student ID\n");
			printf("4: student GPA\n");
			printf("5: student course codes\n");
			printf("=========================================\n");
			printf("Enter your choise number (1,2,3,4,5): ");
			fflush(stdin);fflush(stdout);
			scanf("%d",&update_choise);
			printf("=========================================\n");

			switch(update_choise){
			case 1:
			{
				printf("Enter The Student First Name: ");
				fflush(stdin); fflush(stdout);
				scanf("%s",&temp->fname);
			}
			break;
			case 2:
			{
				printf("Enter The Student Last Name: ");
				fflush(stdin); fflush(stdout);
				scanf("%s",&temp->lname);
			}
			break;
			case 3:
			{
				printf("Enter The Student ID: ");
				fflush(stdin); fflush(stdout);
				scanf("%d",&temp->roll);
			}
			break;
			case 4:
			{
				printf("Enter The Student GPA: ");
				fflush(stdin); fflush(stdout);
				scanf("%f",&temp->GPA);
			}
			break;
			case 5:
			{
				
				for (int i = 0; i < 5; ++i)
				{
				printf("Enter The Student course %d code: ",i+1);
				fflush(stdin); fflush(stdout);
				scanf("%d",&temp->cid[i]);
				}

			}
			break;
			default:
			{
				printf("Error: Wrong choise\n");
			}
			break;

			}

			printf("================================================\n");
			printf("     Student Details is Updated Successfully\n");
			printf("================================================\n");

		}

		if (temp==(student_fifo->base + student_fifo->lengtn - 1))
			temp=student_fifo->base;
		else
			temp++;
	}
	
	return;



}

void DeleteStudent(fifo_buf_t* student_fifo)
{
	//cheak fifo is empty
	if (student_fifo->count==0){
		printf("The list is empty\n");
		return;
	}
	student_t* current= student_fifo->head;
	student_t* next= student_fifo->head +1;
	int ID;

	printf("Enter The Student ID to remove: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&ID);
	for (int i = 0; i < student_fifo->count; ++i)
	{
		if (current->roll==ID)
		{
			*current=*next;
			for(int j = 0 ; j<student_fifo->count-(i+1);j++)
			{
				if (current==(student_fifo->base + student_fifo->lengtn - 1))
					current=student_fifo->base;
				else
					current++;

				if (next==(student_fifo->base + student_fifo->lengtn - 1))
					next=student_fifo->base;
				else
					next++;	
				*current=*next;	
			}
			break;
		}
		else
		{
			if (current==(student_fifo->base + student_fifo->lengtn - 1))
				current=student_fifo->base;
			else
				current++;

			if (next==(student_fifo->base + student_fifo->lengtn - 1))
				next=student_fifo->base;
			else
				next++;	

		}

		



	}
	if (student_fifo->tail == student_fifo->base )
		student_fifo->tail = &buffer[49];

	else
		student_fifo->tail--;

	student_fifo->count--;

	printf("================================================\n");
	printf("  Student with ID (%d) is deleted Successfully\n",ID);
	printf("================================================\n");	

	count_of_students(student_fifo);
}


