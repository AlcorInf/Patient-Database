#ifndef LINKED_LIST
#define LINKED_LIST

//Structure of a Patient
typedef struct node {
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

	struct node* NEXT;
}patient_t;

/*Function declarations*/

//LinkedList
void addElementAtStart(struct node** top);
void addElementToEnd(struct node* top);
void deleteElementAtStart(struct node** top);
void deleteElementAtEnd(struct node* top);
void deleteElementAtPos(struct node* top, int position);
int listLength(struct node* top);


#endif // !LINKED_LIST

