#ifndef _TREAP_HPP_
#define _TREAP_HPP_


const int INF_MIN = -1000000001;


typedef struct node {

    int key, weight, number;
    int children_count;
    struct node *right, *left;

} Node;

typedef struct {

    Node *left, *right;
} nodePair;


Node    *NodeCtor ();
void     NodeDtor (Node *node);
Node    *Insert   (Node *root, int key);
Node    *Delete   (Node *root, int key);
Node    *Merge    (Node *left, Node *right);
nodePair Split    (Node *root, int key);
int      Find     (Node *node, int key);
int      FindNext (Node *node, int key);
int      FindPrev (Node *node, int key);
int      FindMax  (Node *node);
int      FindMin  (Node *node);
int      FindKth  (Node *root, int key);

void     UpdateNode (Node *node);
int GetTreeSize (Node *node);


#endif