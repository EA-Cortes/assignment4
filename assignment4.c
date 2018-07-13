// UCF Summer 2018
// COP3502 - Professor Travis Meade
// Task Manager AVL Tree by Efrain Alejandro Cortes

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// AVL Tree Node struct
typedef struct Node{
	int key;
	char* taskName;
	struct Node* left;
	struct Node* right;
	int height;
}Node;

// ---------------------- Function declarations ----------------------
Node* getInputs(int n, Node *node);
Node* insert(Node *node, int key, char *string);
Node* newNode(int key, char *string);
Node* search(Node *node, int key);
Node* rightRotate(Node *y);
Node* leftRotate(Node *x);

int height(Node *node);
int getBal(Node *node);
int max(int a, int b);

// ---------------------- Main ----------------------
int main(){
	int n = 0;
	Node *root = NULL;
	scanf("%d", &n);
	root = getInputs(n, root);
}

// ---------------------- Function Definitions ----------------------

//	Creates a new node inside AVL tree, mallocs its memory, stores its values from user input 
Node* newNode(int key, char* string){
	Node *node = (Node*)malloc(sizeof(Node));
	node->taskName = (char *)malloc(sizeof(char) * 20);
	node->key = key;
	strcpy(node->taskName, string);
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

//	Inserts user input into AVL tree, simultaneously balancing it
Node *insert(Node *node, int key, char *string){
	if(node == NULL){
		printf("ADDED\n");
		return newNode(key, string);
	}

	if(key == node->key){
		printf("REDUNDANT\n");
	}

	if(key < node->key){
    	node->left = insert(node->left, key, string);
	}else if(key > node->key){
		node->right = insert(node->right, key, string);
	}else{
    // return node;
	}

	// Update height
	node->height = 1 + max(height(node->left), height(node->right));

	// Check the balance factor of the new node
	int balance = getBal(node);

	// LL Rotate
	if(balance > 1 && key < node->left->key) return rightRotate(node);
    
	// RR Rotate
	if(balance < -1 && key > node->right->key) return leftRotate(node);
    
	// LR Rotate
	if(balance > 1 && key > node->left->key){
    	node->left = leftRotate(node->left);
    	return rightRotate(node);
    }
    
	// RL Rotate
    if(balance < -1 && key < node->right->key){
    	node->right = rightRotate(node->right);
    	return leftRotate(node);
    }
	return node;
}

//	Function to search through the AVL tree by key, and output the taskName stored in node
Node *search(Node *node, int key){
	if(node == NULL){
    	printf("NON-EXISTANT\n");
    	return node;
	}else if(node->key == key){
		if(node->taskName != NULL){
			printf("%s\n", node->taskName);
    	}
  	}

	if(key < node->key){
		return search(node->left, key);
	}else if(key > node->key){
		return search(node->right, key);
	}
	return node;
}

//	Utility function that rotates node to the right
Node *rightRotate(Node *y){
	Node *x = y->left;
	Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	return x;
}

//	Utility function that rotates node to the left
Node *leftRotate(Node *x){
	Node *y = x->right;
	Node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	return y;
}

//	Utility function to see which of two values is greater
int max(int a, int b){
	return (a > b) ? a : b;
}

//	Utility function to get the height of a node
int height(Node *node){
	return (node == NULL) ? 0 : node->height;
}

//	Utility function to get the balance favtor of a Node
int getBal(Node *node){
	if(node == NULL){
		return 0;
	}
	return height(node->left) - height(node->right);
}

//	Function that gets inputs from the user
//	Determines whether to insert/search tasks into/from AVL tree
Node* getInputs(int n, Node *node){
	int i = 0, state = 0, tempKey = 0;
	char *tempName;
	if(n == 0){
		printf("No input\n");
	}else{
		for(i = 0; i < n; i++){
			state = 0;
			scanf("%d", &state);
	      
		//	Input sanitizer
			while(state != 1 && state != 2){
				scanf("%d", &state);
			}
	  
			if(state == 1){
				tempName = (char *)malloc(sizeof(char) * 20);
				scanf("%s %d", tempName, &tempKey);
				node = insert(node, tempKey, tempName);
				free(tempName);
				tempName = NULL;
			}else if(state == 2){
				scanf("%d", &tempKey);
				search(node, tempKey);        
			}
		}
	}
	return node;
}