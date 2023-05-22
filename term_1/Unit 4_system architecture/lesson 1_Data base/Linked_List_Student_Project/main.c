/*
 ============================================================================
 Name        : Linked_list_student_project.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


struct Sdata{
    int id;
    char name[40];
    float hight;

};

//linked list node
struct SStudent{
    struct Sdata student;
    struct SStudent* PNextStudent;

};



struct SStudent* gpFirstStudent=NULL;



void add_student(){
    struct SStudent* plastStudent;
    struct SStudent* pNewStudent;
    char temp_text[40];
    //check list is empty ==yes
    if(gpFirstStudent==NULL){
        //create new record
        pNewStudent= (struct SStudent*)malloc(sizeof(struct SStudent));

        //assign it to gpfirst
        gpFirstStudent=pNewStudent;
    }
    else //if list contains records
    {
        //navigate untill reach the last student
        plastStudent=gpFirstStudent;

        while(plastStudent->PNextStudent)
            plastStudent = plastStudent->PNextStudent;
        //cerat new record
        pNewStudent=(struct SStudent*)malloc(sizeof(struct SStudent));
        plastStudent->PNextStudent=pNewStudent;
    }

    //fill new record
    printf("\nEnter the ID: ");
    gets(temp_text);
    pNewStudent->student.id =atoi(temp_text);

    printf("\nEnter student full name: ");
    gets(pNewStudent->student.name);

    printf("\nEnter the height: ");
    gets(temp_text);
    pNewStudent->student.hight =atoi(temp_text);

    //set the Next pointer (New student)to NULL
    pNewStudent->PNextStudent=NULL;
}


int delete_student(){
    char temp_text[40];
    unsigned int selected_id;

    //get the selected id
    printf("Enter the student ID to be deleted: ");
    gets(temp_text);
    selected_id=atoi(temp_text);

    //Check list is not empty
    if(gpFirstStudent){
        struct SStudent* pPreviousStudent = NULL;
        struct SStudent* pSelectedStudent = gpFirstStudent;
        while(gpFirstStudent){
            //compare the recorded ID with the selected ID
            if(pSelectedStudent->student.id==selected_id){
                if(pPreviousStudent){
                    pPreviousStudent->PNextStudent= pSelectedStudent->PNextStudent;
                }
                else{
                    gpFirstStudent=pSelectedStudent->PNextStudent;
                }
                free(pSelectedStudent);
                return 1;
            }
            //store previous record pointer
            pPreviousStudent=pSelectedStudent;
            pSelectedStudent=pSelectedStudent->PNextStudent;

        }




    }
    printf("\n connot find student ID.");
    return 0;
}


void view_student(){
    int count = 0;
    struct SStudent* pCurrentStudent = gpFirstStudent;
    if (gpFirstStudent == NULL)
        printf("\nEmpty list\n");

    while(pCurrentStudent){
        printf("\n Record Number %d",count+1);
        printf("\n ID Number: %d",pCurrentStudent->student.id);
        printf("\n Name: %s",pCurrentStudent->student.name);
        printf("\n Hight: %f",pCurrentStudent->student.hight);
        printf("\n");
        printf("\n ---------------------");
        printf("\n");

        pCurrentStudent=pCurrentStudent->PNextStudent;
        count++;

    }
}


void DeleteAll(){
    struct SStudent* pCurrentStudent = gpFirstStudent;
    if (gpFirstStudent == NULL)
        printf("\nEmpty list\n");

    while(pCurrentStudent){
        struct SStudent* pTempStudent = pCurrentStudent;
        pCurrentStudent=pCurrentStudent->PNextStudent;
        free(pTempStudent);
    }
    gpFirstStudent = NULL;
}


int main(int argc, char const *argv[])
{
    char temp_text[40];
    while(1){
        printf("\n =========================");
        printf("\n\t Choose one of the following Options\n");
        printf("\n 1: Add student");
        printf("\n 2: Delete student");
        printf("\n 3: View Students");
        printf("\n 4: Delete All");
        printf("\n Enter Option Number: ");

        gets(temp_text);
        printf("\n =========================\n");

        switch(atoi(temp_text)){
        case 1:
            add_student();
            break;
        case 2:
            delete_student();
            break;
        case 3:
            view_student();
            break;
        case 4:
            DeleteAll();
            break;
        default:
            printf("\n Wrong Option");
            break;
        }


    }
    return 0;
}
