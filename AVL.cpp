#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#include "AVL.hpp"


Node *NodeCtor () {

    Node *node = (Node*) calloc(1, sizeof(Node));

    node->key    = 0;
    node->left   = 0;
    node->right  = 0;
    node->height = 0;

    return node;
}

void NodeDtor (Node *node) {

    node->key    = 0;
    node->left   = 0;
    node->right  = 0;
    node->height = 0;

    free(node);
}

void treeDtor (Node *root) {

    if (!root) return;

    treeDtor(root->left);
    treeDtor(root->right);

    NodeDtor(root);
}

Node *Insert (Node *node, int key) {

    if (!node) {

        Node *new_node   = NodeCtor();
        new_node->key    = key;
        new_node->height = 1;

        return new_node;
    }

    if (key < node->key) {

        node->left = Insert(node->left, key);
    }
    else if (key > node->key) {

        node->right = Insert(node->right, key);
    }

    return FixBalance(node);
}

Node *Delete (Node *node, int key) {

    if (!node) return nullptr;

    if (node->key < key) {

        node->right = Delete(node->right, key);
    }
    else if (node->key > key) {

        node->left = Delete(node->left, key);
    }
    else {

        Node *r = node->right, *l = node->left;
        NodeDtor(node);

        if (!r) return l;

        Node *r_min = findMin(r);
        r_min->right = delMin(r);

        return r_min;
        return FixBalance(r_min);
    }

    return FixBalance(node);
}

Node *findMin (Node *node) {

    if (!node) return nullptr;

    if (!node->left) return node;
    return findMin(node->left);
}

Node *delMin (Node *node) {

    if (!node) return nullptr;

    if (!node->left) return node->right;
    node->left = delMin(node->left);
    
    return FixBalance(node);
}

void printTree (Node *root, int deepth) {

    if (!root) {

        for (int i = 0; i < deepth; i++) {

            printf("  ");
        }
        printf("key: none\n");

        return;
    }

    printTree(root->left, deepth + 1);

    for (int i = 0; i < deepth; i++) {

        printf("  ");
    }
    printf("key: %d\n", root->key);

    printTree(root->right, deepth + 1);
}

Node *RotateRight (Node *node) {

    Node *new_root = node->left;

    node->left = new_root->right;
    new_root->right = node;

    FixHeight(node);
    FixHeight(new_root);

    return new_root;
}

Node *RotateLeft (Node *node) {

    Node *new_root = node->right;

    node->right = new_root->left;
    new_root->left = node;

    FixHeight(node);
    FixHeight(new_root);

    return new_root;
}

Node *FixBalance (Node *node) {

    FixHeight(node);

    if (Balance(node) == 2) {

        if (Balance(node->right) == -1) {

            node->right = RotateRight(node->right);
        }

        return RotateLeft(node);
    }

    if (Balance(node) == -2) {

        if (Balance(node->left) == 1) {

            node->left = RotateLeft(node->left);
        }

        return RotateRight(node);
    }

    return node;
}

void FixHeight (Node *node) {

    if (!node) return;

    if (Height(node->left) > Height(node->right)) {

        node->height = Height(node->left) + 1;
    }
    else {

        node->height = Height(node->right) + 1;
    }
}

int Balance (Node *node) {

    if (!node) return 0;

    return Height(node->right) - Height(node->left);
}

int Height (Node *node) {

    if (!node) {

        return 0;
    }

    return node->height;
}