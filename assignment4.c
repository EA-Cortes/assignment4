#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void createTask();
void getTask();

// AVL Tree node
struct Node{
	int key;
	char* taskName;

	struct Node *left;
	struct Node *right;
	int height;

}Node;

int max(int a, int b);
int height(struct Node *node);
int getBal(struct Node *node);
struct Node *newNode(int key);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
struct Node *insert(struct Node *node, int key);
void preOrder(struct Node *node);
void inOrder(struct Node *node);
struct Node * searchTree(struct Node *node, int key);

int main(){
	int n = 0;
	struct Node *root = NULL;
	root = insert(root, 10);
  // root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 25);

  

  searchTree(root, 40);
  
  printf("In order traversal of the tree above is\n");
  inOrder(root);
  printf("\n");
	// scanf("%d", n);
	// n will be the following number of lines in which the user will choose to either add/call tasks
		// Input format
		// int 1 (createTask) OR 2 (getTask)
			// 1 -- char[19] taskName -- int priority
			// 2 -- int
}

// Create new node, malloc its memory, init its values
struct Node *newNode(int key){
  struct Node *node = (struct Node*)malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

// Utility function that rotates to the right
struct Node *rightRotate(struct Node *y){
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  return x;
}

// Utility function that rotates to the left
struct Node *leftRotate(struct Node *x){
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  return y;
}

// Function that inserts and balances new nodes simultaneously
struct Node *insert(struct Node *node, int key){

  // BST Insertion
  if(node == NULL){
    return newNode(key);
  }

  if(key == node->key){
    printf("%d is REDUNDANT\n", node->key);
  }

  if(key < node->key){
    node->left = insert(node->left, key);
  }else if(key > node->key){
    node->right = insert(node->right, key);
  }else{
    return node;
  }

  // Update height
  node->height = 1 + max(height(node->left), height(node->right));

  // check if tree is balanced;
  int balance = getBal(node);

  // deal with unbalanced tree cases
  // Left Left Case
  if(balance > 1 && key < node->left->key){
    return rightRotate(node);
  }

  // Right Right case
  if(balance < -1 && key > node->right->key){
    return leftRotate(node);
  }
  
  // Left Right case
  if(balance > 1 && key > node->left->key){
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left case
  if(balance < -1 && key < node->right->key){
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // If tree is already balanced
  return node;
}

struct Node *searchTree(struct Node *node, int key){
  if(node == NULL){
    printf("Value not found.\n");
    return node;
  }else if(node->key == key){
    printf("%d found in tree!\n", key);
  }


  if(key < node->key){
      return searchTree(node->left, key);
  }else if(key > node->key){
     return searchTree(node->right, key);
  }
  return node;
}

// Utility function to see which of two values is greater
int max(int a, int b){
  return (a > b) ? a : b;
}

int height(struct Node *node){
  if (node == NULL){
    return 0;
  }
  return node->height;
}

// Utility function to get the balance favtor of a Node
int getBal(struct Node *node){
  if(node == NULL){
    return 0;
  }
  return height(node->left) - height(node->right);
}

// Utility function to print preorder traversal
void preOrder(struct Node *node){
  if(node !=NULL){
    printf("%d ", node->key);
    preOrder(node->left);
    preOrder(node->right);
  }
}

// Utility function to print in-order traversal
void inOrder(struct Node *node){
  if(node != NULL){
    inOrder(node->left);
    printf("%d ", node->key);
    inOrder(node->right);
  }
}

// Create Task and assign it a priority
void createTask(){

}

void getTask(){

}
