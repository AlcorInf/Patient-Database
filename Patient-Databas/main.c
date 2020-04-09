
//Username and password in login.txt

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include"linked.h"
#include"validation.h"
#include"search.h"
#include"other.h"
#include"load.h"
#include"outputs.h"

//Struct to hold login information
typedef struct {
	char fileUserName[11];
	char filePassWord[7];
}login_t;


void main() {

	//Variables
	int menuChoice;//Main menu option
	int editChoice;//Edit patient
	char fNameIn[11];
	char lNameIn[11];
	char pidIn[9];
	char searchPID[9];//search
	int searchChoice;
	char searchFirst[11];
	char searchLast[11];
	int totalPatients;
	char userName[11];
	char passWord[7];
	int isLog = 0;
	int numInputs; //file read validation
	int i = 0; //loop control
	struct node* headPtr = NULL;

	FILE* readLogin; //pointer to login file
	readLogin = fopen("login.txt", "r"); //open login
	login_t login; //struct

	//Print Display
	printf("--------------------------------------------\n\nWELCOME TO THE BEST HOSPITAL IN THE WORLD\n\n--------------------------------------------\n\n");

	//Prompt and read user input for username and password
	printf("Enter User Name: \n");
	scanf("%s", userName);
	printf("\nEnter Password (max 6 characters): \n");

	do {
		passWord[i] = getch();
		if (passWord[i] != '\r') {
			printf("*");
		}
		i++;
	} while (passWord[i - 1] != '\r');
	passWord[i - 1] = '\0';

	//No login
	if (readLogin == NULL) {
		//No login file found
		printf("No Login File Found\n");
	}
	//Login found
	else {

		//Read login file
		while (!feof(readLogin)) {

			//Check num of inputs to prevent a re-read of last line in file
			numInputs = fscanf(readLogin, "%s %s", login.fileUserName, login.filePassWord);

			//Check numInputs and login details - If all ok, run program
			if (numInputs == 2 && strcmp(userName, login.fileUserName) == 0 && strcmp(passWord, login.filePassWord) == 0)
			{
				printf("\n\nLOGIN SUCCESS!\n");

				//acting as true false for failed log in
				isLog++;

				//open patient file
				FILE* readIn;
				readIn = fopen("patient.txt", "r");

				//load patient report
				if (readIn == NULL) {
					//No file found
					printf("\nPatient records not found!\n");
				}
				else {
					//load patient file
					while (!feof(readIn)) {
						//check if head pointer in null
						if (headPtr == NULL) {
							//First time around set the head pointer
							loadFront(&headPtr, readIn);
						}
						else {
							//Next time load from the end
							loadEnd(headPtr, readIn);
						}
					}//while

					//close file
					fclose(readIn);
				}//else
				system("cls");
				do {
					//print menu until user enters -1
					printf("\n--------------------------------------------\n");
					printf("(1) Add Patient\n(2) Display All Patients\n(3) Display Patient Details\n(4) Update Patient Details\n(5) Delete Patient\n"
						"(6) Create Report\n(-1) Exit\n");
					printf("--------------------------------------------\n");
					scanf("%d", &menuChoice);

					switch (menuChoice) {

					case 1:
						//If the database is empty, add at start. Otherwise add to end
						if (headPtr == NULL) {
							addElementAtStart(&headPtr);
						}
						else {
							addElementToEnd(headPtr);
						}
						break;

					case 2:
						//Print all patients
						printList(headPtr);
						break;

					case 3:
						//Search for patient via PID or Name, print details
						do {
							printf("---------------------------------------\n");
							printf("\n(1) Search via Name\n(2) Search via PID\n(0) Back\n");
							scanf("%d", &searchChoice);
							if (searchChoice == 1) {
								printf("Enter First Name:\n");
								scanf("%s", searchFirst);
								printf("Enter Last Name:\n");
								scanf("%s", searchLast);
								searchName(headPtr, searchFirst, searchLast);
							}
							else if (searchChoice == 2) {
								printf("Enter PID to search: \n");
								scanf("%s", searchPID);
								if (searchList(headPtr, searchPID) == 1) {
									printSingle(headPtr, searchPID);
								}
								else {
									printf("Sorry, the PID does not exist in the Database\n");
								}
							}
						} while (searchChoice != 0);
						break;

					case 4:
						//Search and Edit with either Name or PID
						do {
							printf("Please choose\n(1) Edit by Name or\n(2) Edit by PID\n");
							scanf("%d", &editChoice);
							switch (editChoice) {
							case 1:
								//Search via Name
								printf("Enter First Name:\n");
								scanf("%s", fNameIn);
								printf("Enter Last Name:\n");
								scanf("%s", lNameIn);
								if (searchListName(headPtr, fNameIn, lNameIn) == 1) {
									searchNameEdit(headPtr, fNameIn, lNameIn);
									system("cls");
								}
								else
									printf("Sorry, Name does not exist in the Database\n");
								break;
							case 2:
								//Search via PID
								printf("Enter PID:\n");
								scanf("%s", pidIn);
								if (searchList(headPtr, pidIn) == 1) {
									searchPIDEdit(headPtr, pidIn);
									system("cls");
								}
								else {
									printf("Sorry, the PID does not exist in the Database\n");
								}
								break;
							default:
								printf("Invalid choice, please try again.\n");
								break;
							}
						} while (editChoice != 1 && editChoice != 2);
						break;

					case 5:
						//Delete Patent via PID
						if (headPtr == NULL) {
							printf("Database is empty");
						}
						else
						{
							printf("Please enter PID of Patient to be removed:\n");
							scanf("%s", searchPID);
							int pos = findPos(headPtr, searchPID);
							if (pos == -1) {
								printf("Patient not found");
							}
							else if (pos == 0) {
								deleteElementAtStart(&headPtr);
							}
							else if (pos < listLength(headPtr)) {
								deleteElementAtPos(headPtr, pos);
							}
							else {
								deleteElementAtEnd(headPtr);
							}
						}
						break;

					case 6:
						//Create report.txt - User readable report on all patients
						reportPrint(headPtr);
						printf("Report Generated!\n\n");
						break;

					case -1:
						//Exit and print database to file patient.txt
						system("cls");
						filePrint(headPtr);
						printf("\n\nExiting\n\n\n");
						break;

					default:
						break;
					}
				} while (menuChoice != -1);
			}//if

		}//while

		//If login failed print warning to console, program ends
		if (isLog == 0) {
			printf("\nLogin Failed\n");
		}

		//close login file
		fclose(readLogin);

	}//else


}//main()
