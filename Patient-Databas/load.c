#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"linked.h"
#include"validation.h"
#include"other.h"
#include"search.h"
#include"load.h"
#include"outputs.h"

//Load database from front
void loadFront(struct node** top, FILE* report) {

	//file input variables
	int numRead;
	char pid[9];
	char fName[11];
	char lName[11];
	int age;
	char gender;
	char email[31];
	float weight;
	float height;
	char allergies;
	float BMI;

	//check number of entries
	numRead = fscanf(report, "%s %s %s %d %c %s %f %f %c %f", pid, fName, lName, &age, &gender, email, &weight, &height, &allergies, &BMI);

	if (numRead == 10)
	{
		if (*top == NULL)
		{
			//set new node pointer
			struct node* newNode;

			//allocate memory for new node and set patient variables
			newNode = (struct node*)malloc(1 * sizeof(struct node));
			strcpy(newNode->pid, pid);
			strcpy(newNode->fName, fName);
			strcpy(newNode->lName, lName);
			newNode->age = age;
			newNode->gender = gender;
			strcpy(newNode->email, email);
			newNode->weight = weight;
			newNode->height = height;
			newNode->allergies = allergies;
			newNode->BMI = BMI;

			//Point to next patient
			newNode->NEXT = *top;
			*top = newNode;

		}//if
	}//if
}//loadFront

//Load Database from end
void loadEnd(struct node* top, FILE* report) {

	//Variables
	int numRead;
	char pid[9];
	char fName[11];
	char lName[11];
	int age;
	char gender;
	char email[31];
	float weight;
	float height;
	char allergies;
	float BMI;

	//check number of entries
	numRead = fscanf(report, "%s %s %s %d %c %s %f %f %c %f", pid, fName, lName, &age, &gender, email, &weight, &height, &allergies, &BMI);

	if (numRead == 10) {

		//set new node pointer
		struct node* temp = top;
		struct node* newNode;

		//find end of list
		while (temp->NEXT != NULL)
		{
			temp = temp->NEXT;
		}

		//allocate memory for new node and set patient variables
		newNode = (struct node*)malloc(1 * sizeof(struct node));
		strcpy(newNode->pid, pid);
		strcpy(newNode->fName, fName);
		strcpy(newNode->lName, lName);
		newNode->age = age;
		newNode->gender = gender;
		strcpy(newNode->email, email);
		newNode->weight = weight;
		newNode->height = height;
		newNode->allergies = allergies;
		newNode->BMI = BMI;

		//point to next patient
		newNode->NEXT = NULL;
		temp->NEXT = newNode;

	}//if
}//loadEnd
