#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct wishList{
	char name[101];
	int priority;
	wishList *next;
	wishList *prev;	
}*head = NULL, *tail = NULL, *curr;

void printMenu(){
	printf("1. Add wish\n");
	printf("2. View wish list\n");
	printf("3. Remove Wish\n");
	printf("4. Exit\n");
	printf("Please choose: ");
}

//Choose 1: Add data
void addWish(wishList input){
	curr = (wishList*)malloc(sizeof(wishList));
	*curr = input;
	curr->next = curr->prev = NULL;
	
	if(head == NULL){
		head = tail = curr;	
	}
	else if(curr->priority < head->priority){
		curr->next = head;
		head->prev = curr;
		head = curr;
	}
	else if(curr->priority >= tail->priority){
		tail->next = curr;
		curr->prev = tail;
		tail = curr;
	}	
	else{
		wishList *temp = head;
		while(temp->next->priority < curr->priority){
			temp = temp->next;
		}
		curr->next = temp->next;
		curr->prev = temp;
		temp->next->prev = curr;
		temp->next = curr;
	}
}

//Choose 1 input
wishList Wish(){
	wishList input;
	curr = (wishList*)malloc(sizeof(wishList));
	do{
		printf("Input wish name [2..100]: ");
		scanf("[^\n]", input.name);
		getchar();
	}while(strlen(input.name) < 2 || strlen(input.name) > 100);
	
	do{
		printf("Input wish priority [1..10]: ");
		scanf("%d", &input.priority);
		getchar();
	}while(input.priority < 1 || input.priority > 10);
	return input;
}

//Choose 2: View data
void viewWish(){
	int index = 1;
	wishList* output = head;
	if(output == NULL){
		printf("Wish list is empty...\n");
	}
	while(output != NULL){
		printf("%d. %s #%d\n", index, output->name, output->priority);
		index++;
		output = output->next;
	}
	printf("\n");
}

//Choose 3 Search data
wishList* getNameWish(char name[101]){
	wishList *search = head;
	while(search != NULL){
		if(strcmp(search->name, name) == 0) break;
		search = search->next;
	}
	return search;
}

//Choose 3 success delete message
void printSucessdelete(char name[101]){
	wishList *output = getNameWish(name);
	printf("Success to delete wish\"%s #%d\" from download list.\n", output->name, output->priority);
}

//Choose 3: Remove wish
void removeWish(char name[101]){
	curr = getNameWish(name); 
	if(curr = NULL){
		printf("Wish not found...\n");
	}
	else{
		if(curr == head && curr == tail){
			printSucessdelete(name);
			free(curr);
			head = tail = NULL;
		}
		else if(curr == head){
			//??
			head = head->next;
			printSucessdelete(name);
			free(curr);
			head->prev = NULL;
		}
		else if(curr == tail){
			tail = tail->prev;
			printSucessdelete(name);
			free(curr);
			tail->next = NULL;
		}
		else{
			wishList *temp = head;
			while(temp != NULL && temp != curr){
				temp = temp->next;
			}
			temp->next->prev = temp->prev;
			curr->prev->next = curr->next;
			printSucessdelete(name);
			free(curr);
		}	
	}
}

int main(){
	int choose;
	do{
		printMenu();
		scanf("%d", &choose);
		getchar();
		printf("\n");
		if(choose == 1){
			addWish(Wish());
		}
		else if(choose == 2){
			viewWish();
		}
		else if(choose == 3){
			char nama[101];
			do{
				printf("Input wish name [2..100]: ");
				scanf("%[\n]", &nama);
				getchar();
			}while(strlen(nama) < 2 || strlen(nama) > 100);
			removeWish(nama);
		}
	} while(choose != 4);
	
	return 0;
}
