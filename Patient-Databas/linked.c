#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"linked.h"
#include"validation.h"
#include"search.h"
#include"other.h"
#include"load.h"
#include"outputs.h"

//Add patient, only used if no patients exist
void addElementAtStart(struct node** top) {

	//Variables
	struct node* newNode;
	char pid[9];
	char fName[11];
	char lName[11];
	char gender;
	char allergies;
	char emailAddress[31];
	int valEmail = 0;
	int valPID = 0;
	int updatePID;

	//Prompt and read PID
	printf("Enter the Patient's ID (Format - 1234567A) :\n");
	scanf("%s", pid);
	valPID = validPID(pid);
	while (valPID != 8) {
		printf("Invalid PID, try again...\n");
		printf("Enter valid Patient's ID (Format - 1234567A) :\n");
		scanf("%s", pid);
		valPID = validPID(pid);
	}

	//Add new patient node
	newNode = (struct node*)malloc(1 * sizeof(struct node));

	//copy pid from search into struct
	strcpy(newNode->pid, pid);

	//First name
	printf("Enter First Name:\n");
	scanf("%s", fName);
	strcapital(fName);
	strcpy(newNode->fName, fName);

	//Last name
	printf("Enter Last Name:\n");
	scanf("%s", lName);
	strcapital(lName);
	strcpy(newNode->lName, lName);
	
	//Age
	printf("Enter Age:\n");
	scanf("%d", &newNode->age);

	//Gender
	printf("Enter Gender:\nFormat: F - Female / M - Male\n");
	scanf(" %c", &gender);
	newNode->gender = toupper(gender);

	//Prompt, read and validate email address
	printf("Enter valid email:\n");
	scanf("%s", emailAddress);
	valEmail = validEmail(emailAddress);
	while (valEmail != 5) {
		printf("Invalid email, try again\n");
		printf("Enter valid email:\n");
		scanf("%s", emailAddress);
		valEmail = validEmail(emailAddress);
	}
	strcpy(newNode->email, emailAddress);

	//Dont allow weights of zero or less
	do {
		printf("Enter Weight (kg):\n");
		scanf("%f", &newNode->weight);
	} while (newNode->weight < 0);

	//Dont allow heights of zero or less
	do {
		printf("Enter Height (cm):\n");
		scanf("%f", &newNode->height);
	} while (newNode->height < 0);

	//Allergies to meds
	printf("Any Allergies to medication:\nFormat Y - Yes / N - No\n");
	scanf(" %c", &allergies);
	newNode->allergies = toupper(allergies);

	//Set BMI according to patients weight and height
	newNode->BMI = BMI(newNode->height, newNode->weight);

	//New nodes NEXT points to top
	newNode->NEXT = *top;
	//Top updated with newNode
	*top = newNode;
}

//Add patient, used every time but the first
void addElementToEnd(struct node* top) {

	//Variables
	struct node* temp;
	struct node* prevTemp;
	struct node* newNode;
	temp = top;
	char fName[11];
	char lName[11];
	char pid[9];
	char gender;
	char allergies;
	char emailAddress[31];
	int valEmail = 0;
	int valPID = 0;


	printf("Enter the Patient's ID (Format - 1234567A) :\n");
	scanf("%s", pid);
	valPID = validPID(pid);
	while (valPID != 8) {
		printf("Invalid PID, try again...\n");
		printf("Enter valid Patient's ID (Format - 1234567A) :\n");
		scanf("%s", pid);
		valPID = validPID(pid);
	}

	//If patient PID is already save ask if they want to update
	if (searchList(top, pid) == 1) {
		int choice;
		printf("Sorry the ID already exists in the Database\n");
		printf("Do you wish to edit the patients details?\n(1) Yes\n(2) No\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			searchPIDEdit(top, pid);
			break;
		case 2:
			return;
			break;
		default:
			printf("Incorrect choice\n");
			break;
		}
		return; //Break out of function
	}

	//Find end
	while (temp->NEXT != NULL) {
		temp = temp->NEXT;
	}

	//Add new patient node
	newNode = (struct node*)malloc(1 * sizeof(struct node));
	strcpy(newNode->pid, pid); //copy pid from search into struct

	printf("Enter First Name:\n");
	scanf("%s", fName);
	strcapital(fName);
	strcpy(newNode->fName, fName);

	printf("Enter Last Name:\n");
	scanf("%s", lName);
	strcapital(lName);
	strcpy(newNode->lName, lName);

	printf("Enter Age:\n");
	scanf("%d", &newNode->age);

	printf("Enter Gender:\nFormat: F - Female / M - Male\n");
	scanf(" %c", &gender);
	newNode->gender = toupper(gender);


	//Email validation - Must include '@' and '.com'
	printf("Enter valid email:\n");
	scanf("%s", emailAddress);
	valEmail = validEmail(emailAddress);
	while (valEmail != 5) {
		printf("Invalid email, try again...\n");
		printf("Enter valid email:\n");
		scanf("%s", emailAddress);
		valEmail = validEmail(emailAddress);
	}
	strcpy(newNode->email, emailAddress);

	do {
		printf("Enter Weight (kg):\n");
		scanf("%f", &newNode->weight);
	} while (newNode->weight < 0);

	do {
		printf("Enter Height (cm):\n");
		scanf("%f", &newNode->height);
	} while (newNode->height < 0);

	printf("Any Allergies to medication:\nFormat Y - Yes / N - No\n");
	scanf(" %c", &allergies);
	newNode->allergies = toupper(allergies);

	newNode->BMI = BMI(newNode->height, newNode->weight);

	//Point end to NULL
	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}

//Delete from start
void deleteElementAtStart(struct node** top) {
	struct node* temp;
	temp = *top;
	*top = temp->NEXT;
	free(temp);
	printf("Patient record deleted\n");
}

//Delete from end
void deleteElementAtEnd(struct node* top) {
	struct node* temp;
	struct node* prevTemp;

	temp = top;
	while (temp->NEXT != NULL) {
		prevTemp = temp;
		temp = temp->NEXT;
	}
	prevTemp->NEXT = NULL;
	free(temp);
	printf("Patient record deleted\n");
}

//Delete from Position, position found through patient PID
void deleteElementAtPos(struct node* top, int position) {
	int i;
	struct node* temp;
	struct node* prevTemp;
	struct node* newNode;

	temp = top;
	for (i = 0; i < (position); i++) {
		prevTemp = temp;
		temp = temp->NEXT;
	}

	prevTemp->NEXT = temp->NEXT;
	free(temp);
	printf("Patient record deleted\n");
}

//Return the length of the database
int listLength(struct node* top) {
	struct node* temp;
	int count = 0;
	temp = top;
	while (temp != NULL) {
		count++;
		temp = temp->NEXT;
	}
	return count;
}