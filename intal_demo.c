#include<stdio.h>
#include<stdlib.h>
#include "intal.h"
int main()
{
	char *s1=(char *)malloc(sizeof(char)*100000);//Arbitrary length, length can be adjusted.
	char *s2=(char *)malloc(sizeof(char)*100000);
	printf("Enter the first number with a preceeding sign.('+' for 0):\t");
	scanf("%s",s1);
	printf("Enter the second number with a preceeding sign.('+' for 0):\t");//Sign is must for the code to work.
	scanf("%s",s2);
	printf("Choose one of the following operations\n");
	printf("1.Addition\n 2.Subtraction\n 3.Multiplication\n 4.Division\n 5.Exponential\n");//Exponential power should not be negative.
	int c;//Choice of operations.
	padding(s1,s2);
	scanf("%d",&c);
		
	switch(c)
	{
		case 1: 
		printf("Addition:- %s\n", addition(s1,s2));
			break;
		
		case 2: 
		printf("Subtraction:- %s\n", subtraction(s1,s2));
			break;
		case 3:
		printf("Multiplication:- %s\n",multiplication(s1,s2));
			break;
		case 4:
		printf("Division:- %s\n",division(s1,s2));
		break;
		case 5:
		printf("Exponential:- %s\n",exponential_intal(s1,s2));
		break;
			
	}


}
