#ifndef __AVLTREE_H
# define __AVLTREE_H

#ifndef FALSE
# define FALSE 0
#endif // FALSE
#ifndef TRUE
# define TRUE 1
#endif // TRUE

#define MICROSECONDS_PER_SECOND (1000000.0D)

typedef struct node_s {
    int key; 
    int height;
    int count;

    struct node_s *left; 
    struct node_s *right; 
} node_t;

node_t *insertNode(node_t *, int);
node_t *deleteNode(node_t *, int);
node_t *findKey(node_t *, int);

void inOrder(node_t *);
void postOrder(node_t *);
void preOrder(node_t *);
void print2D(node_t *, int);
void freeTree(node_t *);


#endif // __AVLTREE_H
