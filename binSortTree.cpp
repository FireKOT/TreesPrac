#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#include "binSortTree.hpp"


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

    return node;
    //return FixBalance(node);
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
        //return FixBAlance(r_min);
    }

    return node;
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
    
    return node;
    //return FixBAlance(node);
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
