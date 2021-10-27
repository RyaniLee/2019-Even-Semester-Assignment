#include<stdio.h>
#include<stdlib.h>

typedef struct data{
	int index;
	int goldProduction;
	int depth;
	struct data *left;
	struct data *right;	
} node;

node* caves(node in, int depth){
	node *newCaves = (node*)malloc(sizeof(node));
	newCaves->index = in.index;
	newCaves->goldProduction = in.goldProduction;
	newCaves->depth = depth;
	newCaves->left = NULL;
	newCaves->right = NULL;
	return newCaves;
}

void printMenu(){
	printf("Hov Mining Simulator\n");
	printf("====================\n");
	printf("[1] Insert Mining Data\n");
	printf("[2] Display All Cave Data\n");
	printf("[3] Display Mining Report\n");
	printf("[4] Exit\n");
	printf(">> ");
}

//single linked list for temporary storing index
struct temp{
	int value;
	struct temp *next;
} *head = NULL, *tail = NULL, *tempIndex;


int sameIndex(int value){
	int flag=1;
	temp *temporary = head;
	if(temporary ==  NULL) return 0;
	while(temporary->next != NULL){
		if(temporary->value == value){
			return 1000;
		} 
		else{
			temporary = temporary->next;
			flag++;
		}
	}
	return flag;
}

void push(int value){
	tempIndex = (struct temp*)malloc(sizeof(struct temp));
	tempIndex->value = value;
	tempIndex->next = NULL;
	
	int flag = sameIndex(value);
	if(flag != 1000){
		if(head == NULL){
			head = tail = tempIndex;	
		}
		else if (value < head->value){
			tempIndex->next = head;
			head = tempIndex;
		}
		else if (value > tail->value){
			tail->next = tempIndex;
			tail = tempIndex;
		}
		else{
			temp* tempo = head;
			while(tempo->next->value < value){
				tempo = tempo->next;
			}
			tempIndex->next = tempo->next;
			tempo->next = tempIndex;
		}
	}
}

int tempGoldProduction [3000] = {NULL};
int tDepth = 1;
node *insert(node *root, node in){
	if(root == NULL){
		printf("New cave index detected.\n");
		printf("Total gold production for Cave %d is %d.\n", in.index, in.goldProduction);
		tempGoldProduction[tDepth] += in.goldProduction; 
		in.depth = 1;
		return caves(in, tDepth);
	}
	else if(in.index == root->index){
		root->goldProduction = root->goldProduction + in.goldProduction;
		printf("Cave index already exist.\n");
		printf("New total gold production for Cave %d is %d.\n", in.index, root->goldProduction);
		tempGoldProduction[tDepth] += in.goldProduction;
	}
	else if(in.index < root->index){
		tDepth++;
		root->left = insert(root->left, in);
	}
	else if(in.index > root->index){
		tDepth++;
		root->right = insert(root->right, in);
	}
	return root;
}

void inorder(node *root){
	if(root != NULL){
		inorder(root->left);
		printf(">> Cave %d  (depth %d ), total gold production is %d\n", root->index, root->depth, root->goldProduction);
		inorder(root->right);
	}
}

void displayAllCave(node *root){
	if(root != NULL){
		temp *tempor = head;
		while(tempor->next != NULL){
			if(tempor->value == root->index){
				printf(">> Cave %d  (depth %d ), total gold production is %d\n", root->index, root->depth, root->goldProduction);
			}
			else if(tempor->value < root->index){
				displayAllCave(root->left);
			}
			else if(tempor->value > root->index){
				displayAllCave(root->right);
			}
			tempor = tempor->next;
		}
	}
}


void displayMiningReport(node *root){
	if(root == NULL){
		printf("Cave data is empty, nothing to report.\n");
	}
	else{	
		int a = 1;
		while(tempGoldProduction[a] != NULL){
			printf(">> Total gold production for depth %d   is %d\n", a, tempGoldProduction[a]);
			a++;
		}
	}
	printf("\n\n");
	printf("Press any key to continue...\n");
	scanf("%*c");
}

node *removeAll(node *root){
	if(root == NULL) return NULL;
	root->left = removeAll(root->left);
	root->right = removeAll(root->right);
	free(root);
	return NULL;
}

int main(){
	int menu;
	node *root = NULL;
	node in;
	int idx = 0;
	do{
		system("cls");
		printf("\n");
		printMenu();
		scanf("%d", &menu);
		getchar();
		system("cls");
		printf("\n");
		if(menu == 1){
			do{
				printf("Input cave index [1-999]: ");
				scanf("%d%*c", &in.index);
			}while(in.index < 1 || in.index > 999);
			//Store temporary Index[1-999]  that was availble and in order;
			//for void displayAllCaves
			push(in.index);
			
			do{
				printf("Input gold production [1-100]: ");
				scanf("%d%*c", &in.goldProduction);
			}while(in.goldProduction < 1 || in.goldProduction > 100);
			
			printf("\n");	
			tDepth = 1;
			root = insert(root, in);
			printf("\n\n");
			printf("Press any key to continue...\n");
			scanf("%*c");
		}
		else if(menu == 2){
			//displayAllCave function maybe repeat too much
//			if(root != NULL){
//				displayAllCave(root);
//			}
//			else{
//				printf("Cave data is empty, nothing to display.\n");
//			}
			//for this input, it will display exactly like in order
			if (root != NULL){
				inorder(root);	
			}else{
				printf("Cave data is empty, nothing to display.\n");
			}
			printf("\n\n");
			printf("Press any key to continue...\n");
			scanf("%*c");
		}
		else if(menu == 3){
			displayMiningReport(root);
		}
		else if(menu == 4){
			removeAll(root);
			printf("All data has been removed from memory.\n");
			printf("Thank you for playing, see you again....\n");
		}
	}while(menu != 4);
	return 0;
}
