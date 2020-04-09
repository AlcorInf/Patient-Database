#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"linked.h"
#include"validation.h"
#include"other.h"
#include"search.h"
#include"outputs.h"

//PID Validation - Must be in the Format(1234567A)
int validPID(char pid[9]) {
	int len = strlen(pid);
	int valPID = 0;

	//Check for integer between index-0 to index-6 position
	for (int i = 0; i < 7; i++) {
		if (isdigit(pid[i])) {
			valPID++;
		}
	}
	//Check the last character of PID is alphabetic and uppercase
	if (isalpha(pid[len - 1]) && isupper(pid[len - 1])) {
		valPID++;
	}
	//Should return 8
	return valPID;
}

//Email Validation - Must include @ and .com
int validEmail(char email[31]) {

	int len = strlen(email);
	int valEmail = 0;

	//Check array for @ symbol
	for (int i = 0; i < len; i++) {
		if (email[i] == '@') {
			valEmail++;
			break; 
		}
	}

	//Check array for . at index-4 position
	if (email[len - 4] == '.') {
		valEmail++;
	}

	//Check array for c at index-3 position
	if (email[len - 3] == 'c') {
		valEmail++;
	}

	//Check array for c at index-2 position
	if (email[len - 2] == 'o') {
		valEmail++;
	}

	//Check array for c at index-1 position
	if (email[len - 1] == 'm') {
		valEmail++;
	}

	//Should return 5 
	return valEmail;
}