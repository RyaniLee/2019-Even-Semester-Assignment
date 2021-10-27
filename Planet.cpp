#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct Planet {
	long long int temperature;
	char name[31];
	
	struct Planet* left;
	struct Planet* right;
	int height;
} Planet;

int height(Planet* rt) {
	if (rt == NULL) return 0;
	return rt->height;
}

int max(int x, int y) {
	return x > y ? x : y;
}

int getBalanceFactor(Planet* rt) {
	if (rt == NULL) return NULL;
	return height(rt->left) - height(rt->right);
}

Planet *newNode(long long int temp, char name[31]){
	Planet* curPl = (Planet*) malloc(sizeof(Planet));
	curPl->temperature = temp;
	strcpy(curPl->name, name);
	curPl->left = curPl->right = NULL;
	curPl->height = 1;
	return curPl;
}

Planet* rightRotate(Planet*& cur) {
	Planet* left = cur->left;
	Planet* leftRight = left->right;
	
	cur->left = leftRight;
	left->right = cur;
	
	cur->height = max(height(cur->left), height(cur->right)) + 1;
	left->height = max(height(left->left), height(left->right)) + 1;
	
	return left;
}

Planet* leftRotate(Planet*& cur) {
	Planet* right = cur->right;
	Planet* rightLeft = right->left;
	
	cur->right = rightLeft;
	right->left = cur;
	
	cur->height = max(height(cur->left), height(cur->right)) + 1;
	right->height = max(height(right->left), height(right->right)) + 1;
	
	return right;
}

Planet* insertData(Planet*& root, long long int temp, char name[31]) {
	if (root == NULL) {
		return root = newNode(temp, name);
	}
	if (temp < root->temperature) {
		insertData(root->left, temp, name);
	}
	else if (temp > root->temperature) {
		insertData(root->right, temp, name);
	}
	else return root;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balanceFactor = getBalanceFactor(root);
	
	if (balanceFactor > 1 && temp < root->left->temperature) {
		return rightRotate(root);
	}
    if (balanceFactor < -1 && temp > root->right->temperature) {
    	return leftRotate(root);
	}
    if (balanceFactor > 1 && temp > root->left->temperature) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    }
    if (balanceFactor < -1 && temp < root->right->temperature) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    }
    
    return root;
}

Planet* searchData(Planet* root, long long int temp) {
	if (root == NULL) {
		return NULL;
	}
	if (temp < root->temperature) {
		return searchData(root->left, temp);
	}
	else if (temp > root->temperature) {
		return searchData(root->right, temp);
	}
	else {
		return root;
	}
}

Planet* predecessor(Planet* root){
	Planet* currnt = root;
	while(currnt->right != NULL){
		currnt = currnt->right;
	}
	return currnt;
}

Planet* sucessor(Planet* root){
	Planet* currnt = root;
	while(currnt->left != NULL){
		currnt = currnt->left;
	}
	return currnt;
}

Planet* deleteData(Planet* root, long long int temp){
	if (root == NULL) {
		return NULL;
	}
	if (temp < root->temperature) {
		deleteData(root->left, temp);
	}
	else if (temp > root->temperature) {
		deleteData(root->right, temp);
	}
	else{
		//no child
		//left child
		//right child
		//two children
		
		if(root->left == NULL|| root->right == NULL){
			Planet* tempor = NULL;
			if(root->left == NULL){
				tempor = root->right;
			}else{
				tempor = root->left;
			}
			
			//1
			if(tempor == NULL){
				tempor = root;
				root = tempor;
			}
			//2 & 3
			else {
				*root = *tempor;
			}
			free(tempor);
		}else{
			Planet* tempor = predecessor(root->left);
			root->temperature = tempor->temperature;
			strcpy(root->name, tempor->name);
			
			root->left = deleteData(root->left, tempor->temperature);
		}
	}
	if(root == NULL) return root;
	root->height = max(height(root->left), height(root->right)) + 1;
	int balanceFactor = getBalanceFactor(root);
	
	if (balanceFactor > 1 && temp < root->left->temperature) {
		return rightRotate(root);
	}
	if (balanceFactor < -1 && temp > root->right->temperature) {
	 	return leftRotate(root);
	}
	if (balanceFactor > 1 && temp > root->left->temperature) { 
	    root->left =  leftRotate(root->left); 
	    return rightRotate(root); 
	}
	if (balanceFactor < -1 && temp < root->right->temperature) { 
	    root->right = rightRotate(root->right); 
	   return leftRotate(root); 
    }
	return root;
}

void inOrder(Planet* root) {
	if (root != NULL) {
		inOrder(root->left);
		printf("%d\n", root->temperature);
		inOrder(root->right);
	}
}

void big(Planet* root, long long int temp){
	long long int big = 0;
	if (root != NULL) {
		inOrder(root->left);
		if(root->temperature > temp){
			big ++;
		}
		inOrder(root->right);
	}
	printf("%lld\n", big);
}

int main() {
	int input;
	int menu;
	Planet* root = NULL;
	
	long long int nowIdx= 1;
	long long int temp = 0;
	char namePlanet[31];
	long long int idxFrom = 0;
	long long int idxTo = 0;
	
	scanf("%d", &input);
	for(int i = 0; i < input; i++){
		scanf("%d", &menu);
		
		if(menu == 1){
			scanf("%lld %s", &temp, namePlanet);
			getchar();
			insertData(root, temp, namePlanet);
			big(root, temp);
//			printf("1 %lld\n", temp);
		}else if(menu == 2){
			scanf("%lld", &temp);
			getchar();
			deleteData(root, temp);
			big(root, temp);
//			printf("2 %lld\n", temp);
		}else if(menu == 3){
			scanf("%lld", &temp);
			getchar();
//			printf("3 %lld\n", temp);
		}else if(menu == 4){
			scanf("%lld %lld", &idxFrom, &idxTo);
			getchar();
//			printf("4 %lld %lld\n", idxFrom, idxTo);
		}
	}
	
	return 0;
}
