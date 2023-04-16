#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#include "treap.hpp"


Node *NodeCtor () {

    Node *new_node = (Node*) calloc(1, sizeof(Node));

    new_node->key    = 0;
    new_node->weight = 0;
    new_node->number = 0;
    new_node->children_count = 1;
    new_node->left   = 0;
    new_node->right  = 0;

    return new_node;
}

void NodeDtor (Node *node) {

    node->key    = 0;
    node->weight = 0;
    node->number = 0;
    node->children_count = 0;
    node->left   = 0;
    node->right  = 0;

    free(node);
}

Node *Insert (Node *root, int key) {

    if (Find(root, key) != INF_MIN) return root;

    Node *new_node   = NodeCtor();
    new_node->key    = key;
    new_node->weight = rand();

    nodePair split = Split(root, key);

    root = Merge(split.left, new_node);
    return Merge(root, split.right);
}

Node *Delete (Node *root, int key) {

    if (!root || Find(root, key) == INF_MIN) return root;

    nodePair split_lower = Split(root, key);
    nodePair split_upper = Split(split_lower.right, key + 1);

    return Merge(split_lower.left, split_upper.right);
}

Node *Merge (Node *left, Node *right) {

    if (!left)  return right;
    if (!right) return left;

    if (left->weight > right->weight) {

        Node *new_left = left->right;
        left->right = Merge(new_left, right);
        UpdateNode(left);

        return left;
    }

    Node *new_right = right->left;
    right->left = Merge(left, new_right);
    UpdateNode(right);

    return right;
}

nodePair Split (Node *root, int key) {

    if (!root) {

        nodePair ret = {

            .left  = 0,
            .right = 0,
        };
        return ret;
    }

    if (root->key < key) {

        nodePair slice = Split(root->right, key);
        root->right = slice.left;
        
        UpdateNode(root);

        nodePair ret = {

            .left  = root,
            .right = slice.right,
        };
        return ret;
    }

    nodePair slice = Split(root->left, key);
    root->left = slice.right;

    UpdateNode(root);
    
    nodePair ret = {

        .left  = slice.left,
        .right = root,
    };
    return ret;
}

int Find (Node *node, int key) {

    if (!node) return INF_MIN;

    if (node->key == key) return key;

    if (node->key > key) return Find(node->left, key);
    return Find(node->right, key);
}

int FindNext (Node *node, int key) {

    if (!node) return INF_MIN;

    if (key >= node->key) {

        if (!node->right) return INF_MIN;
        
        int r_min = FindMin(node->right);
        if (key >= r_min) return FindNext(node->right, key);
        
        return r_min;
    }
    
    if (!node->left) return node->key;
    
    int l_max = FindMax(node->left);
    
    if (key < l_max) return FindNext(node->left, key);
    
    return node->key;
}

int FindPrev (Node *node, int key) {

    if (!node) return INF_MIN;
    
    if (key <= node->key) {
        
        if (!node->left) return INF_MIN;
        
        int l_max = FindMax(node->left);
        
        if (key <= l_max) return FindPrev(node->left, key);
        
        return l_max;
    }
    
    if (!node->right) return node->key;
    
    int r_min = FindMin(node->right);
    
    if (key > r_min) return FindPrev(node->right, key);
    
    return node->key;
}

int FindMax (Node *node) {

    if (!node) return INF_MIN;

    int max_key = 0;

    Node *cur_node = node;
    while (cur_node) {

        max_key  = cur_node->key;
        cur_node = cur_node->right;
    }

    return max_key;
}

int FindMin (Node *node) {

    if (!node) return INF_MIN;

    int min_key = 0;

    Node *cur_node = node;
    while (cur_node) {

        min_key  = cur_node->key;
        cur_node = cur_node->left;
    }

    return min_key;
}

void UpdateNode (Node *node) {

    if (!node) return;

    node->children_count = GetTreeSize(node->left) + GetTreeSize(node->right) + 1;
}

int FindKth (Node *root, int key) {

    if (!root) return INF_MIN;

    if (key > GetTreeSize(root)) return INF_MIN;

    int l_key = GetTreeSize(root->left);

    if (l_key == key) return root->key;

    if (l_key <  key) return FindKth(root->right, key - l_key - 1);

    return FindKth(root->left, key);
}

int GetTreeSize (Node *node) {

    if (!node) return 0;

    return node->children_count;
}