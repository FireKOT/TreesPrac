#ifndef _SPLAY_HPP_
#define _SPLAY_HPP_


enum GC_Type {

    root    = 0,
    zig     = 1,
    zig_zig = 2,
    zig_zag = 3,
};


typedef struct node {

    int key;
    struct node *right, *left, *parent;

} Node;

typedef struct {

    Node *left, *right;
} nodePair;

 
Node     *NodeCtor  (int key, Node *left, Node *right);
void      NodeDtor  (Node *node);
Node     *Insert    (Node *root, int key);
Node     *Delete (Node *root, int key);
nodePair  Split     (Node *root, int key);
Node     *Splay     (Node *node);
void      rotate    (Node *child, Node *parent);
Node     *Find      (Node *node, int key);
int       detGCType (Node *node);
Node     *Merge      (Node *left, Node *right);
void      PrintTree (Node *root, int deepth = 0);


#endif