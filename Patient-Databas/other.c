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

//Calculate BMI
float BMI(float h, float w) {
	// BMI = kg/(M^M) where M is height in meters
	float hM = h / 100; //hM = height in Meters
	return w / (hM * hM);
}

char strcapital(char str[]){
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		//check first character is lowercase alphabet
		if (i == 0)
		{
			if ((str[i] >= 'a' && str[i] <= 'z'))
				str[i] = str[i] - 32; //subtract 32 to make it capital
			continue; //continue to the loop
		}
		if (str[i] == ' ')//check space
		{
			//if space is found, check next character
			++i;
			//check next character is lowercase alphabet
			if (str[i] >= 'a' && str[i] <= 'z')
			{
				str[i] = str[i] - 32; //subtract 32 to make it capital
				continue; //continue to the loop
			}
		}
		else
		{
			//all other uppercase characters should be in lowercase
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] = str[i] + 32; //subtract 32 to make it small/lowercase
		}
	}
}
