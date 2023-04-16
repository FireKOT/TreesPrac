#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#include "splay.hpp"


Node *NodeCtor (int key, Node *left, Node *right) {

    Node *new_node = (Node*) calloc(1, sizeof(Node));
    if (!new_node) return 0;
    
    new_node->key   = key;
    new_node->left  = left;
    new_node->right = right;

    return new_node;
}

void NodeDtor (Node *node) {

    free(node);
}

Node *Insert (Node *root, int key) {

    nodePair split = Split(root, key);
    root = NodeCtor(key, split.left, split.right);
    if (split.left)  split.left ->parent = root;
    if (split.right) split.right->parent = root;

    return root;
}

Node *Delete (Node *root, int key) {

    root = Find(root, key);

    if (root->left)  root->left ->parent = nullptr;
    if (root->right) root->right->parent = nullptr;

    Node *ret = Merge(root->left, root->right);

    NodeDtor(root);

    return ret;
}

nodePair Split (Node *root, int key) {

    if (!root) {

        nodePair ret = {

            .left  = 0,
            .right = 0,
        };
        return ret;
    }

    root = Find(root, key);
    if (!root) {

        nodePair ret = {

            .left  = 0,
            .right = 0,
        };
        return ret;
    }
 
    if (key <= root->key) {

        nodePair ret = {

            .left  = root->left,
            .right = root,
        };

        if (root->left) root->left->parent = 0;
        root->left = 0;

        return ret;
    }
    else {

        nodePair ret = {

            .left  = root,
            .right = root->right,
        };

        if (root->right) root->right->parent = 0;
        root->right = 0;

        return ret;
    }
}

Node *Splay (Node *node) {

    if (!node) return 0;

    int type = detGCType(node);
    if (type == -1) return 0;

    if (type == root) return node;

    Node *parent = node->parent, *gparent = node->parent->parent;

    if (type == zig) {

        rotate(node, parent);
    }
    else if (type == zig_zig) {

        rotate(parent, gparent);
        rotate(node,    parent);
    }
    else if (type == zig_zag) {

        rotate(node,  parent);
        rotate(node, gparent);
    }

    return Splay(node);
}

void rotate (Node *child, Node *parent) {

    if (!child || !child->parent || !parent) {

        printf("Inval rotate args\n");
        return;
    }

    Node *gparent = parent->parent;
    if (gparent) {

        if (gparent->left == parent) {

            gparent->left = child;
        }
        else if (gparent->right == parent) {

            gparent->right = child;
        }
        else {

            printf("Rotate gparent error!\n");
            return;
        }
    }

    if (parent->left == child) {

        parent->left  = child->right;
        child ->right = parent;
    }
    else if (parent->right == child) {

        parent->right = child->left;
        child ->left  = parent;
    }
    else {

        printf("Rotate parent error!\n");
        return;
    }

    parent->parent = child;
    if (parent->left)  parent->left ->parent = parent;
    if (parent->right) parent->right->parent = parent;

    child->parent = gparent;
    if (child->left)  child->left ->parent = child;
    if (child->right) child->right->parent = child;
}

Node *Find (Node *node, int key) {

    if (!node) return nullptr;

    if (key == node->key) return Splay(node);
    if (key > node->key && node->right) return Find(node->right, key);
    if (key < node->key && node->left ) return Find(node->left,  key);

    return Splay(node);
}

int detGCType (Node *node) {

    if (!node) return -1;
    if (!node->parent) return root;
    if (!node->parent->parent) return zig;

    if ((node == node->parent->left && node->parent == node->parent->parent->left) ||\
        (node == node->parent->right && node->parent == node->parent->parent->right)) {

        return zig_zig;
    }
    if ((node == node->parent->left && node->parent == node->parent->parent->right) ||\
        (node == node->parent->right && node->parent == node->parent->parent->left)) {

        return zig_zag;
    }

    printf("Error!\n");
    return -1;
}

Node *Merge (Node *left, Node *right) {

    if (!left)  return right;
    if (!right) return left;

    right = Find(right, left->key);

    right->left = left;
    left->parent = right;

    return right;
}

void PrintTree (Node *root, int deepth) {

    if (!root) {

        for (int i = 0; i < deepth; i++) {

            printf("\t");
        }

        printf("key: none\n");
        return;
    }

    PrintTree(root->left, deepth + 1);

    for (int i = 0; i < deepth; i++) {

        printf("\t");
    }

    printf("key: %d\n", root->key);

    PrintTree(root->right, deepth + 1);
}
