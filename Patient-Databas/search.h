#ifndef SEARCH_FUNCTIONS
#define SEARCH_FUNCTIONS

int searchList(struct node* top, char pid[9]);
int searchListName(struct node* top, char first[11], char last[11]);
void printSingle(struct node* top, char pps[9]); //Print via search with PID
void searchName(struct node* top, char first[11], char last[11]);
void searchNameEdit(struct node* top, char first[11], char last[11]);
void searchPIDEdit(struct node* top, char pid[9]);
int findPos(struct node* top, char pid[9]);

#endif
