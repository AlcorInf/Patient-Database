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

//Search Database for patient via PID, return the position in the database
int searchList(struct node* top, char pid[9]) {
	int found = 0;
	struct node* temp= top;

	//Search until PID is encountered, adding to count each time. Return count when found, indicates position in linked list
	while (temp != NULL) {
		if (strcmp(temp->pid, pid) == 0) {
			found = 1;
			return found;
		}
		temp = temp->NEXT;
	}
	return found;
}

int searchListName(struct node* top, char first[11], char last[11]) {
	int found = 0;
	struct node* temp = top;
	strcapital(first); strcapital(last);


	while (temp != NULL) {
		if ((strcmp(temp->fName, first) == 0) && (strcmp(temp->lName, last) == 0)) {
			found = 1;
			return found;
		}
		temp = temp->NEXT;
	}
	return found;
}

//Specific to searching via PID number
void printSingle(struct node* top, char pid[9]) {
	struct node* temp = top;

	//Search until PID found, print details to console
	while (temp != NULL) {
		if (strcmp(temp->pid, pid) == 0) {
			printf("\n---------------------------------------\n");
			printf("PID: %s\n", temp->pid);
			printf("NAME: %s %s\n", temp->fName, temp->lName);
			printf("AGE: %d\n", temp->age);
			printf("GENDER: %c\n", temp->gender);
			printf("EMAIL: %s\n", temp->email);
			printf("WEIGHT - kg: %.3f\n", temp->weight);
			printf("HEIGHT - cm: %.3f\n", temp->height);
			printf("ALLERGIES TO MEDS: %c\n", temp->allergies);
			printf("BMI: %.2f\n", temp->BMI);
		}//if
		temp = temp->NEXT;
	}//while
}

//Search and print patent via name
void searchName(struct node* top, char first[11], char last[11]) {
	struct node* temp = top;
	strcapital(first); strcapital(last);

	while (temp != NULL) {
		if (strcmp(temp->fName, first) == 0 && strcmp(temp->lName, last) == 0) {
			printf("\n---------------------------------------\n");
			printf("PID: %s\n", temp->pid);
			printf("NAME: %s %s\n", temp->fName, temp->lName);
			printf("AGE: %d\n", temp->age);
			printf("GENDER: %c\n", temp->gender);
			printf("EMAIL: %s\n", temp->email);
			printf("WEIGHT - kg: %.3f\n", temp->weight);
			printf("HEIGHT - cm: %.3f\n", temp->height);
			printf("ALLERGIES TO MEDS: %c\n", temp->allergies);	
			printf("BMI: %.2f\n", temp->BMI);

			//If found get out of function after printing
			return;
		}//if

		//Point to next patient
		temp = temp->NEXT;
	}//while

	//If not found
	printf("Sorry, Name not found\n\n");
}

//Search and edit patient via PID number
void searchPIDEdit(struct node* top, char pid[9]) {
	struct node* temp = top;
	int choice;
	char fName[11];
	char lName[11];
	char gender;
	char email[31];
	char allergies;
	int valEmail;

	while (temp != NULL) {
		if (strcmp(temp->pid, pid) == 0) {
			do {
				printf("------------------------------------------\n");
				printf("\n(1) Edit First Name\n(2) Edit Last Name\n(3) Edit Age\n(4) Edit Gender\n(5) Edit Email\n(6) Edit Weight"
					"\n(7) Edit Height\n(8) Edit Allergies\n(0) Main Menu\n");
				scanf("%d", &choice);
				printf("------------------------------------------\n");
				switch (choice) {

				case 1:
					//First
					printf("Current first name: %s\n", temp->fName);
					printf("Enter new first name:\n");
					scanf("%s", fName);
					strcapital(fName);
					strcpy(temp->fName, fName);
					break;

				case 2:
					//Last
					printf("Current last name: %s\n", temp->lName);
					printf("Enter new last name:\n");
					scanf("%s", lName);
					strcapital(lName);
					strcpy(temp->lName, lName);
					break;

				case 3:
					//Age
					printf("Current age:%d\n", temp->age);
					printf("Enter new age:\n");
					scanf("%d", &temp->age);
					break;

				case 4:
					//Gender
					printf("Current gender: %c\n", temp->gender);
					printf("Enter new gender:\n");
					scanf(" %c", &gender);
					temp->gender = toupper(gender);
					break;

				case 5:
					//Email
					printf("Current Email: %s\n", temp->email);
					printf("Enter valid email:\n");
					scanf("%s", email);
					valEmail = validEmail(email);
					while (valEmail != 5) {
						printf("Invalid email, try again...\n");
						printf("Enter valid email:\n");
						scanf("%s", email);
						valEmail = validEmail(email);
					}
					strcpy(temp->email, email);
					break;

				case 6:
					//Weight
					printf("Current Weight: %.2f\n", temp->weight);
					printf("Enter new weight:\n");
					scanf("%f", &temp->weight);
					//Update BMI
					temp->BMI = BMI(temp->height, temp->weight);
					printf("BMI updated to: %.2f\n", temp->BMI);
					break;

				case 7:
					//Height
					printf("Current Height: %.2f\n", temp->height);
					printf("Enter new height:\n");
					scanf("%f", &temp->height);
					//Update BMI
					temp->BMI = BMI(temp->height, temp->weight);
					printf("BMI updated to: %.2f\n", temp->BMI);
					break;

				case 8:
					//Allergies
					printf("Current Allergies: %c\n", temp->allergies);
					printf("Enter Y/N whether allegeries present or not:\n");
					scanf(" %c", &allergies);
					temp->allergies = toupper(allergies);
					break;

				case 0:
					return;
					break;
				default:
					printf("EDIT VIA PID BROKEN\n");
				}
			} while (choice < 1 && choice > 6);
		}
		temp = temp->NEXT;
	}

	printf("Patient Details Updated!\n");
}

//Search and edit patient via name
void searchNameEdit(struct node* top, char first[11], char last[11]) {
	struct node* temp = top;
	int choice;
	char fName[11];
	char lName[11];
	char gender;
	char email[31];
	char allergies;
	int valEmail;
	strcapital(first); strcapital(last);


	while (temp != NULL) {
		if (strcmp(temp->fName, first) == 0 && strcmp(temp->lName, last) == 0) {
			do {
				printf("------------------------------------------\n");
				printf("\n(1) Edit First Name\n(2) Edit Last Name\n(3) Edit Age\n(4) Edit Gender\n(5) Edit Email\n(6) Edit Weight"
					"\n(7) Edit Height\n(8) Edit Allergies\n(0) Main Menu\n");
				printf("------------------------------------------\n\n");
				scanf("%d", &choice);
				switch (choice) {

				case 1:
					//First
					printf("Current first name: %s\n", temp->fName);
					printf("Enter new first name:\n");
					scanf("%s", fName);
					strcapital(fName);
					strcpy(temp->fName, fName);
					break;

				case 2:
					//Last
					printf("Current last name: %s\n", temp->lName);
					printf("Enter new last name:\n");
					scanf("%s", lName);
					strcapital(lName);
					strcpy(temp->lName, lName);
					break;

				case 3:
					//Age
					printf("Current age:%d\n", temp->age);
					printf("Enter new age:\n");
					scanf("%d", &temp->age);
					break;

				case 4:
					//Gender
					printf("Current gender: %c\n", temp->gender);
					printf("Enter new gender:\n");
					scanf(" %c", &gender);
					temp->gender = toupper(gender);
					break;

				case 5:
					//Email
					printf("Current Email: %s\n", temp->email);
					printf("Enter valid email:\n");
					scanf("%s", email);
					valEmail = validEmail(email);
					while (valEmail != 5) {
						printf("Invalid email, try again...\n");
						printf("Enter valid email:\n");
						scanf("%s", email);
						valEmail = validEmail(email);
					}
					strcpy(temp->email, email);
					break;

				case 6:
					//Weight
					printf("Current Weight: %.2f\n", temp->weight);
					printf("Enter new weight:\n");
					scanf("%f", &temp->weight);
					//Update BMI
					temp->BMI = BMI(temp->height, temp->weight);
					printf("BMI updated to: %.2f\n", temp->BMI);
					break;

				case 7:
					//Heights
					printf("Current Height: %.2f\n", temp->height);
					printf("Enter new height:\n");
					scanf("%f", &temp->height);
					//Update BMI
					temp->BMI = BMI(temp->height, temp->weight);
					printf("BMI updated to: %.2f\n", temp->BMI);
					break;
					
				case 8:
					//Allergies
					printf("Current Allergies: %c\n", temp->allergies);
					printf("Enter Y/N whether allegeries present or not:\n");
					scanf(" %c", &allergies);
					temp->allergies = toupper(allergies);
					break;

				case 0:
					return;
					break;
				default:
					printf("Invalid Choice, please try again\n");
				}
			} while (choice != 0);
		}//if
		temp = temp->NEXT;
	}//while
	printf("Patient Details Updated!\n");
}//searchNameEdit

//Find position in list passed on patient pid, return value and use for delete function
int findPos(struct node* top, char pid[9]) {
	struct node* temp = top;
	int count = 0;
	while (temp != NULL && (strcmp(temp->pid, pid)!=0)) {
		count++;
		temp = temp->NEXT;
	}//while
	return (temp != NULL) ? count : -1;
}