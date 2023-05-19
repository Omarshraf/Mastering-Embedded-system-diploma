/*Write a program in C to show a pointer to an array which contents are pointer to structure.
 ============================================================================
 Name        : ex5.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
struct SEmployee {
	char name[20];
	unsigned int id;
};
int main(void) {
//structure values
	struct SEmployee emplo ={"Alex",1002};
//pointer on the structure
	struct SEmployee* P_emplo=&emplo;
//array of pointers that point on the structure
	struct SEmployee* arr[2]={P_emplo,P_emplo};
//pointer on that array
	struct SEmployee *ptr=arr[0];

	printf("Exmployee Name :%s \n",ptr->name);

	printf("Exmployee ID :%d \n",ptr->id);

}
