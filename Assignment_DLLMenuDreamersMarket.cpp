#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
 
struct product{
	char productName[101];
	int quantity;
	int index;
	long int price;
	struct product *next;
	struct product *prev;
} *head = NULL, *tail = NULL, *curr;

int idx = 0;

product item(){
	product in;
	curr = (product*)malloc(sizeof(product));
	printf("Input the product name: ");
	scanf("%[^\n]", &in.productName);
	
	printf("Input quantity of product: ");
	scanf("%d%*c", &in.quantity);
	idx ++;
	return in;
}

void addItem(product in){
	curr = (struct product*)malloc(sizeof(struct product));
	*curr = in;
	curr->next = curr->prev = NULL;
	curr->index = idx;
	
	if(head == NULL){
		head = tail = curr;	
	}
	else if (curr->index < head->index){
		curr->next = head;
		head->prev = curr;
		head = curr;
		curr->prev = NULL;
	}
	else if (curr->index >= tail->index){
		tail->next = curr;
		curr->prev = tail;
		tail = curr;
	}
	else{
		product *temporary = head;
		while(temporary->next->index < curr->index){
			temporary = temporary->next;
		}
		curr->next = temporary->next;
		temporary->next->prev = curr;
		temporary->next = curr;
		curr->prev = temporary;
	}
	printf("Success in adding item!\n\n");
}

product* searchCodeproduct(int index){
	product *search = head;
	while(search != NULL){
		if(search->index == index) break;
		search = search->next;
	}
	return search;
}

void editQuantity(int index){
	int newQuantity; 
	product *search = searchCodeproduct(index);
	if(head == NULL){
		printf("No data in Basket!\n\n");
	} 
	else if(search == NULL){
		printf("Invalid code product!\n\n");
	}
	else{
		printf("Input new quantity: ");
		scanf("%d*c", &newQuantity);
		
		curr = search;
		curr->quantity = newQuantity;
		
		printf("Success edit quantity! new quantity for product %s is %d.\n\n", curr->productName, curr->quantity);
	}
}

void deleteProduct(int index){
	product *search = searchCodeproduct(index);
	if(head == NULL){
		printf("No data in Basket!\n\n");
	}
	else if (search == NULL){
		printf("Invalid code product! Failed to delete!\n\n");
	}
	else{
		if(head == tail){
			free(search);
			head = tail = NULL;
		}
		else if(search == head){
			head = head->next;
			free(search);
			head->prev = NULL;
		}
		else if(search == tail){
			tail = tail->prev;
			free(search);
			tail->next = NULL;
		}
		else{
			product *temporary = head;
			while(temporary != NULL && temporary != search){
				temporary = temporary->next;
			}
			temporary->next->prev = temporary->prev;
			temporary->prev->next = temporary->next;
			free(temporary);
		}
		printf("Success removing the product from basket!\n\n");
	}
}

void printAllItem(){
	product *out = head;
	printf("List item\n");
	printf("[code - name - quantity]\n");
	while(out != NULL){
		printf("%d. %s - %d\n", out->index, out->productName, out->quantity);
		out = out->next; 
	}
}

long int getRandoms() { 
	long int lower = 100000;
	long int upper = 2000000;
    long int num = (rand() % (upper - lower + 1)) + lower;
    return num;
} 

void printAllItemCheckOut(){
	product *out = head;
	long int sum = 0;
	printf("List item\n");
	printf("[code - name - quantity - price - sum]\n");
	while(out != NULL){
		out->price = getRandoms();
		long int total = 0;
		total = (out->price)*(out->quantity);
		printf("%d. %s - %d - %ld -> %ld\n", out->index, out->productName, out->quantity, out->price, total);
		sum = sum + total;
		out = out->next; 
	}
	printf("\n\n");
	printf("Total price: %ld\n\n", sum);
}

void freeAll(){
	while (head != NULL){
		product *temporary = head;
		head = head->next;
		free(temporary);
	}
	idx = 0;
}

void printMenu(){
	printf(" Welcome to Dreamers Market!\n");
	printf("-----------------------------\n");
	printf("1. Add Product to Basket\n");
	printf("2. Edit Product quantity in Basket\n");
	printf("3. Delete Product in Basket\n");
	printf("4. Check out Product\n");
	printf("5. Exit\n");
	printf("\n");
	printf("Input your choice: ");
}

int main(){
	int menu, kuantitasBarang, inputIndex;
	char namaBarang[101];
	do{
		printMenu();
		scanf("%d%*c", &menu);
		
		if(menu == 1){
			addItem(item());
		}
		else if(menu == 2){
			printAllItem();
			inputIndex = 0;
			printf("Input code product: ");
			scanf("%d*c", &inputIndex);
			editQuantity(inputIndex);
		}
		else if(menu == 3){
			printAllItem();
			inputIndex = 0;
			printf("Input code product: ");
			scanf("%d*c", &inputIndex);
			deleteProduct(inputIndex);
		}
		else if(menu == 4){
			printAllItemCheckOut();
			printf("Kindness is free!\n\n");
			freeAll();
		}else if(menu == 5){
			freeAll();
			printf("Thanks for shopping! Hope you enjoy!\n");
		}else{
			printf("Your input is invalid. Please try again!\n");
			printf("\n");
		}
	}while(menu != 5);
	
	return 0;
}
