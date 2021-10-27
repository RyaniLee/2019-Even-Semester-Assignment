#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include <conio.h>

char nameRoles[20] = {NULL};

struct menu{
	char productName[20];
	char type[15];
	int quantity;
	int index;
	long int price;
	struct menu *next;
	struct menu *prev;
}*head = NULL, *tail = NULL, *curr;

struct purchaseM{
	char productName[20];
	char type[15];
	int quantity;
	int index;
	long int price;
	struct purchaseM *nxt;
	struct purchaseM *prv;
}*hd = NULL, *tl = NULL, *crrnt;

//for add item
int idx = 3;
menu item(){
	menu in;
	curr = (menu*)malloc(sizeof(menu));
	
	do{
		printf("Insert item name: ");
		scanf("%[^\n]", in.productName);
		getchar();
		if(strlen(in.productName) < 5 || strlen(in.productName) > 20){
			printf("Length of name should be more than 5 and less than 20\n");
		}
	}while(strlen(in.productName) < 5 || strlen(in.productName) > 20);
	
	do{
		printf("Type of Coffee[yes/no]: ");
		scanf("%s", in.type);
		getchar();
		if(strcmpi(in.type, "yes") != 0 || strcmpi(in.type, "no") != 0){
			printf("Type of coffee only \"yes\" or \"no\" answer\n");
		}
		
		if(strcmpi(in.type, "yes") == 0){
			strcpy(in.type, "Coffee");
		}
		
		if(strcmpi(in.type, "no") == 0){
			strcpy(in.type, "Non-coffee");
		}
	}while(strcmpi(in.type, "yes") != 0 || strcmpi(in.type, "no") != 0);
	
	do{
		printf("Insert the quantity of item: ");
		scanf("%d%*c", &in.quantity);
	}while(in.quantity < 1 || in.quantity >100);
	
	do{
		printf("Insert the price of the item: ");
		scanf("%ld%*c", &in.price);
	}while(in.price < 10000 || in.price > 200000);
	idx++;
	return in;
}

menu basicMenu1(){
	menu bsc;
	curr = (menu*)malloc(sizeof(menu));
	bsc.index = 1;
	strcpy(bsc.productName, "Americano");// Chocolate Baked Alberto
	bsc.price = 19000; //24k 44k
	bsc.quantity = 20; //22 20
	strcpy(bsc.type, "Coffee");
	return bsc;
}

menu basicMenu2(){
	menu bsc;
	bsc.index = 2;
	strcpy(bsc.productName, "Chocolate Baked");// Chocolate Baked Alberto
	bsc.price = 24000; //24k 44k
	bsc.quantity = 22; //22 20
	strcpy(bsc.type, "Non-coffee");
	return bsc;
}

menu basicMenu3(){
	menu bsc;
	bsc.index = 3;
	strcpy(bsc.productName, "Alberto");// Chocolate Baked Alberto
	bsc.price = 44000; //24k 44k
	bsc.quantity = 20; //22 20
	strcpy(bsc.type, "Coffee");
	return bsc;
}

void addBscMenu(menu bsc){
	curr = (struct menu*)malloc(sizeof(struct menu));
	*curr = bsc;
	curr->next = curr->prev = NULL;
	
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
		menu *temporary = head;
		while(temporary->next->index < curr->index){
			temporary = temporary->next;
		}
		curr->next = temporary->next;
		temporary->next->prev = curr;
		temporary->next = curr;
		curr->prev = temporary;
	}
}

void addItem(menu in){
	curr = (struct menu*)malloc(sizeof(struct menu));
	*curr = in;
	curr->index = idx;
	curr->next = curr->prev = NULL;
	
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
		menu *temporary = head;
		while(temporary->next->index < curr->index){
			temporary = temporary->next;
		}
		curr->next = temporary->next;
		temporary->next->prev = curr;
		temporary->next = curr;
		curr->prev = temporary;
	}
	printf("Success in adding item!\n");
	printf("Press enter to continue...");
	getch();
}

menu* searchCodeproduct(int index){
	menu *search = head;
	while(search != NULL){
		if(search->index == index) break;
		search = search->next;
	}
	return search;
}

void removeItem(int index){
	menu *search = searchCodeproduct(index);
	if(head == NULL){
		printf("No data!\n\n");
	}
	else if (search == NULL){
		printf("Invalid number! Failed to delete!\n\n");
	}
	else{
		if(head == tail){
			free(search);
			head = tail = NULL;
		}
		else if(search == head){
			head = head->next;
			menu *tt = head;
			while(tt != NULL){
				tt->index = tt->index - 1;
				tt = tt->next;
			}
			idx = idx - 1;
			free(search);
			head->prev = NULL;
		}
		else if(search == tail){
			tail = tail->prev;
			idx = idx - 1;
			free(search);
			tail->next = NULL;
		}
		else{
			menu *temporary = head;
			while(temporary != NULL && temporary != search){
				temporary = temporary->next;
			}
			
			menu *tx = temporary;
			while(tx != NULL){
				tx->index = tx->index - 1;
				tx = tx->next;
			}
			idx = idx - 1;
			temporary->next->prev = temporary->prev;
			temporary->prev->next = temporary->next;
			free(temporary);
		}
		printf("Success removing the product!\n");
		printf("Press enter to continue...");
		getch();
	}
}

void listBuy(menu *search, int buy){
	int j = 1;
	crrnt = (struct purchaseM*)malloc(sizeof(struct purchaseM));
	crrnt->price = search->price*(long int)buy;
	strcpy(crrnt->productName, search->productName);
	crrnt->quantity = buy;
	strcpy(crrnt->type, search->type);
	crrnt->index = j;
	crrnt->nxt = crrnt->prv = NULL;
	
	if(hd == NULL){
		hd = tl = crrnt;	
	}
	else if (crrnt->index < hd->index){
		crrnt->nxt = hd;
		hd->prv = crrnt;
		hd = crrnt;
		crrnt->prv = NULL;
	}
	else if (crrnt->index >= tl->index){
		tl->nxt = crrnt;
		crrnt->prv = tl;
		tl = crrnt;
	}
	else{
		purchaseM *temporary = hd;
		while(temporary->nxt->index < crrnt->index){
			temporary = temporary->nxt;
		}
		crrnt->nxt = temporary->nxt;
		temporary->nxt->prv = crrnt;
		temporary->nxt = crrnt;
		crrnt->prv = temporary;
	}
	j++;
}

void receipt(){
	printf("No.| Menu                                              | Type       | Quantity | Price             |\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	while(crrnt != NULL){
		printf("%-3d| %-32s| %-12s| %-9d| %-19ld|\n", crrnt->index, crrnt->productName, crrnt->type, crrnt->quantity, crrnt->price);
		crrnt = crrnt->nxt;
	}
	printf("----------------------------------------------------------------------------------------------------\n\n");
	
}

void buyItem(int index){
	int buyQ;
	menu *search = searchCodeproduct(index);
	if(head == NULL){
		printf("No data!\n\n");
	}
	else if (search == NULL){
		printf("please input number between 1 - %d.\n", idx);
	}
	else{
		do{
			printf("enter the quantity[1 - %d]: ", search->quantity);
			scanf("%d", &buyQ);
			
			if(search->quantity == 0){
				printf("The item has been sold out!\n\n");
				break;
			}
			else if(buyQ < 1 || buyQ > search->quantity){
				printf("input number between 1 - %d.\n", search->quantity);
			}	
		}while(buyQ < 1 || buyQ >= search->quantity);
		
		search->index = search->index - buyQ;
		listBuy(search, buyQ);
		receipt();
	}
}

void cancelAll(){
	while(hd != NULL){
		purchaseM *out = hd;
		hd = hd->nxt;
		free(out);
	}
}

void checkNameRoles(){
	do{
		printf("enter your name: ");
		scanf("%[^\n]", nameRoles);
		getchar();
		if(strlen(nameRoles) < 5 || strlen(nameRoles) > 20){
			printf("Length of your name should be between 5 and 19\n");
		}
	}while(strlen(nameRoles) < 5 || strlen(nameRoles) > 20);
}

void printHeading(){
	printf("====================================================================================================\n");
	printf("                                        +++++  Brew Coffee Shop  +++++                              \n");
	printf("Welcome, Mr./Mrs. %s\n\n", nameRoles);
	printf("====================================================================================================\n");
}

void printListMenu(){
	menu *out = head;
	printf("No.| Menu                                              | Type       | Quantity | Price             |\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	while(out != NULL){
		printf("%-3d| %-50s| %-11s| %-9d| %-18ld|\n", out->index, out->productName, out->type, out->quantity, out->price);
		out = out->next;
	}
	printf("----------------------------------------------------------------------------------------------------\n");
}

void customerMenu(){
	printf("1. Buy item\n");
	printf("2. Cancel all\n");
	printf("3. Exit\n");
	printf("____________________________________________________________________________________________________\n");
}

void adminMenu(){
	printf("1. Add item\n");
	printf("2. Remove item\n");
	printf("3. Exit\n");
	printf("____________________________________________________________________________________________________\n");
}

int main(){
	checkNameRoles();
	int menu, removeIdx, buyMenu;
//	char upperName[20];
//	char lowerName[20];
	if(strcmpi(nameRoles, "admin") == 0){
		strcpy(nameRoles, "Admin");
		addBscMenu(basicMenu1());
		addBscMenu(basicMenu2());
		addBscMenu(basicMenu3());
		do{
			printHeading();
			printListMenu();
			adminMenu();
			
			do{
				printf("Enter your action: ");
				scanf("%d", &menu);
				if(menu < 1 || menu >3){
					printf("please insert number between 1 - 3\n\n");
				}
			}while(menu < 1 || menu >3);
			
			if(menu == 1){
				addItem(item());
			}
			else if(menu == 2){
				do{
					printf("Which product do you want to remove [1- %d]:", idx);
					scanf("%d%*c", &removeIdx);
					if(removeIdx < 1 || removeIdx > idx){
						printf("select the data between 1 - %d\n", idx);
					}
					removeItem(removeIdx);
				}while(removeIdx < 1 || removeIdx > idx);
			}
			else if(menu == 3){
				idx = 3;
				printf("Done with settings\n.");
			}
		}while(menu != 3);
	}else{
//		strcpy(upperName, toupper(nameRoles));
//		strcpy(lowerName, tolower(nameRoles));
//		strncpy(lowerName, upperName, 1);
//		strcpy(nameRoles, lowerName);
		addBscMenu(basicMenu1());
		addBscMenu(basicMenu2());
		addBscMenu(basicMenu3());
		do{
			printHeading();
			printListMenu();
			printf("data is empty\n\n");
			customerMenu();
			
			do{
				printf("Enter your action: ");
				scanf("%d", &menu);
				if(menu < 1 || menu >3){
					printf("please insert number between 1 - 3\n\n");
				}
			}while(menu < 1 || menu >3);
			
			if(menu == 1){
				do{
					printf("choose your menu[1 - %d]: ", idx);
					scanf("%d%*c", &buyMenu);
				}while(buyMenu < 1 || buyMenu > idx);
				buyItem(buyMenu);
			}
			else if(menu == 2){
				cancelAll();
			}
			else if(menu == 3){
				printf("Thanks for buying! See you next time!\n\n");
			}
		}while(menu != 3);
	}
	return 0;
}
