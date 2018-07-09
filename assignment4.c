#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// AVL Tree node
typedef struct Node{
	int key;
	char* taskName;

	struct Node *left;
	struct Node *right;
	int height;

}Node;

int height(Node *node);
int getBal(Node *node);
int max(int a, int b);
Node *insert(Node *node, int key, char *string);
Node *newNode(int key, char *string);
Node * search(Node *node, int key);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
void getInputs(int n, Node *node);
void inOrder(Node *node);

int main(){
	int n = 0;
	Node *root = NULL;
	scanf("%d", &n);
  getInputs(n, root);

  printf("\nIn Order Traversal of values in tree:\n");
  inOrder(root);
}

// Create new node, malloc its memory, init its values
Node *newNode(int key, char *string){
  Node *node = (Node*)malloc(sizeof(Node));
  node->key = key;
  node->taskName = string;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}


// Function that inserts and balances new nodes simultaneously
// Node Parameters: 19 char string, int priority
Node *insert(Node *node, int key, char *string){
  // If node is empty, successfully add
  if(node == NULL){    
    printf("ADDED\n");
    return newNode(key, string);

  }
  // If node already exists
  if(key == node->key){
    printf("REDUNDANT\n");
  }

  if(key < node->key){
    node->left = insert(node->left, key, string);
  }else if(key > node->key){
    node->right = insert(node->right, key, string);
  }else{
    return node;
  }

  // Update height
    node->height = 1 + max(height(node->left), height(node->right));

  // deal with unbalanced tree cases
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


// Utility function that rotates to the right
Node *rightRotate(Node *y){
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  return x;
}

// Utility function that rotates to the left
Node *leftRotate(Node *x){
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  return y;
}

// Utility function to see which of two values is greater
int max(int a, int b){
  return (a > b) ? a : b;
}

int height(Node *node){
  return (node == NULL) ? 0 : node->height;
}

// Utility function to get the balance favtor of a Node
int getBal(Node *node){
  if(node == NULL){
    return 0;
  }
  return height(node->left) - height(node->right);
}

// Utility function to print in-order traversal
void inOrder(Node *node){
  if(node != NULL){
    inOrder(node->left);
    printf("%d ", node->key);
    inOrder(node->right);
  }
}


void getInputs(int n, Node *node){
  int i = 0, state = 0, tempKey = 0;
  if(n == 0){
    printf("No input\n");
  }else{
    for(i = 0; i < n; i++){
      scanf("%d", &state);

      if(state == 1){
        char *tempName = (char *)malloc(sizeof(char) * 20);
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
}