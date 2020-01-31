#include<stdio.h> 
#include<stdlib.h>
#include "avlTree.h"

#define COUNT 10

int nodeCount = 0;
int isVerbose = FALSE;
// int* ptr;


int max(int a, int b);
int height( node_t *N);
node_t *newNode(int key);
node_t *rightRotate( node_t *y);
node_t *leftRotate( node_t *x);
int getBalanceFactor( node_t *N);
node_t *maxValueNode( node_t* node);


void print2D(node_t *node, int space)
{

    int i = 0;
    // Base case
    if (node == NULL) {
    return; 
    }
    
    space += COUNT;

    print2D(node->right, space);

    fprintf(stdout, "\n");
    for (i = COUNT; i < space; i++) {
        fprintf(stdout, " "); 
    }
    fprintf(stdout, "%7d\n", node->key);
    // Process left child
    print2D(node->left, space); 

}

node_t *maxValueNode(node_t* node) 
{ 
  node_t* current = node; 
  while (current->right != NULL) 
    current = current->right; 
  return current; 
}


node_t *findKey( node_t *t, int key)

{
    
    if( t == NULL )
        return NULL;
    else if( key < t->key )
        return findKey( t->left, key );
    else if( key > t->key )
        return findKey(  t->right, key);
    else
        return t;
}

void freeTree(node_t *root)
{
    if ( root != NULL ) return;
    {
        freeTree(root -> left);
        freeTree(root -> right);
        free(root);

    }    
}


int height( node_t *N) 
{ 
  if (N == NULL) 
    return 0; 
  return N->height; 
}


int max(int a, int b) 
{ 
  return (a > b)? a : b; 
} 

node_t *newNode(int key) 
{ 
    
  node_t *node = malloc(sizeof(node_t));
  
        // ptr=malloc(sizeof(node_t));
//   node_t *nNode =malloc(sizeof(node_t)); 
  node->key = key; 
  node->left = NULL; 
  node->right = NULL; 
  node->height = 1;
  node->count += 1;
  nodeCount ++;

  return(node); 
} 

node_t *rightRotate( node_t *y) 
{ 
  node_t *x = y->left; 
  node_t *T2 = x->right;

  x->right = y; 
  y->left = T2; 

  y->height = max(height(y->left), height(y->right))+1; 
  x->height = max(height(x->left), height(x->right))+1; 
  return x; 
} 

node_t *leftRotate( node_t *x) 
{ 
  node_t *y = x->right; 
  node_t *T2 = y->left; 
  y->left = x; 
  x->right = T2; 
  x->height = max(height(x->left), height(x->right))+1; 
  y->height = max(height(y->left), height(y->right))+1; 
  return y; 
} 

int getBalanceFactor( node_t *N) 
{ 
  if (N == NULL) 
    return 0; 
  return height(N->left) - height(N->right); 
} 

node_t *insertNode(node_t *node, int key) {
    int balanceFactor;

    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else {
        node->count++;
        // return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balanceFactor < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balanceFactor > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    
    }
    return node;
}

node_t *deleteNode(node_t* root, int key) {
    int balanceFactor;


    if (root == NULL)
        return root;
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else {
        if( (root->left == NULL) || (root->right == NULL) ) {
            node_t *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
        else {
            *root = *temp;
        }   
        free(temp); 
        nodeCount--;
        }   
        else { 
            node_t* temp = maxValueNode(root->left); 
            root->key = temp->key; 
            root->left = deleteNode(root->left, temp->key); 
        }   
    }   
    if (root == NULL) 
        return root; 

    root->height = 1 + max(height(root->left), height(root->right));

    balanceFactor = getBalanceFactor(root);           
  
    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void preOrder( node_t *root) 
{ 
  if(root != NULL) 
  { 
    printf("(%7d %3d) ", root->key, root->count); 
    preOrder(root->left); 
    preOrder(root->right); 
  } 
}





















