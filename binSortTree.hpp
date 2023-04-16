#ifndef _BINSORTTREE_HPP_
#define _BINSORTTREE_HPP_


typedef struct node {

    int key;
    struct node *right, *left;
    int height;
} Node;


Node *NodeCtor ();
void  NodeDtor (Node *node);
void  treeDtor (Node *root);
Node *Insert   (Node *node, int key);
Node *Delete   (Node *node, int key);
Node *findMin  (Node *node);
Node *delMin   (Node *node);

void printTree (Node *root, int deepth = 0);


#endif