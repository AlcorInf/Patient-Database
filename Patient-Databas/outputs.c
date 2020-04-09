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

//Print Patient details to screen - Option 2
void printList(struct node* top) {
	struct node* temp;
	temp = top;
	while (temp != NULL) {
		printf("---------------------------------------\n\n");
		printf("PID: %s\n", temp->pid);
		printf("NAME: %s %s\n", temp->fName, temp->lName);
		printf("AGE: %d\n", temp->age);
		printf("GENDER: %c\n", temp->gender);
		printf("EMAIL: %s\n", temp->email);
		printf("WEIGHT - kg: %.3f\n", temp->weight);
		printf("HEIGHT - cm: %.3f\n", temp->height);
		printf("ALLERGIES TO MEDS: %c\n", temp->allergies);
		printf("BMI: %.2f\n", temp->BMI);

		temp = temp->NEXT;
	}
}

//Print User Readable Report on all patients and their details to file - report.txt
void reportPrint(struct node* top) {

	//File pointer & open as patient.txt
	FILE* output;
	output = fopen("report.txt", "w");

	//Variables
	struct node* temp;
	temp = top;

	//Go through database
	while (temp != NULL) {

		//Print to file report.txt
		fprintf(output, "PID: %s\n", temp->pid);
		fprintf(output, "Fname: %s\n", temp->fName);
		fprintf(output, "Lname: %s\n", temp->lName);
		fprintf(output, "Age: %d\n", temp->age);
		fprintf(output, "Gender: %c\n", temp->gender);
		fprintf(output, "Email: %s\n", temp->email);
		fprintf(output, "Weight: %.2f\n", temp->weight);
		fprintf(output, "Height: %.2f\n", temp->height);
		fprintf(output, "Allergies: %c\n", temp->allergies);
		fprintf(output, "BMI: %.2f\n", temp->BMI);
		fprintf(output, "---------------------------------------\n");

		//point to next node
		temp = temp->NEXT;
	}
	//Close file
	fclose(output);
}

//Print database to file
void filePrint(struct node* top) {

	//File pointer & open as patient.txt
	FILE* output;

	output = fopen("patient.csv", "w");

	struct node* temp;
	temp = top;
	fprintf(output, "PID, Name, Age, Gender, Email, Weight, Height, Allergies, BMI\n");

	//Go through database
	while (temp != NULL) {

		//Print patient variables to file
		fprintf(output, "%s, %s %s, %d, %c, %s, %f, %f, %c, %f\n", temp->pid, temp->fName, temp->lName, temp->age, temp->gender,
			temp->email, temp->weight, temp->height, temp->allergies, temp->BMI);

		//Point to next patient
		temp = temp->NEXT;
	}
	//Close file
	fclose(output);
}