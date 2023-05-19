/* C Program to make a simple calculator to Add, Subtract, Multiply or Divide Using switch...case
 ============================================================================
 Name        : EX_8.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main(void) {
	char operator;
	float num1,num2;
	printf("Enter operator rither + or - or * or / :- ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&operator);
	printf("Enter two operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&num1,&num2);
	switch(operator){
	case 43:
	{
		printf("%.2f + %.2f = %.2f",num1,num2,num1+num2);

	}
	break;

	case 45:
		{
			printf("%.2f - %.2f = %.2f",num1,num2,num1-num2);

		}
		break;
	case 42:
		{
			printf("%.2f * %.2f = %.2f",num1,num2,num1*num2);

		}
		break;
	case 47:
		{
			printf("%.2f / %.2f = %.2f",num1,num2,num1/num2);

		}
		break;
	default:
	{
		printf("Wrong operator");
	}
	break;

	}

}
