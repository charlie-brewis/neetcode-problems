
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

/* 
A binary search tree is a binary tree with one additional property:
    
    For every node, its left child has a value less than or equal to itself, and its right child has
    a value greater than itself.

    left <= parent < right

This property allows us to search the tree efficiently, similarly to how binary search is efficient.
*/
typedef struct BinarySearchTree {
    TreeNode* root;
} BinarySearchTree;


TreeNode* initNode(int val) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    if (!node) { printf("Node allocation failed\n"); exit(1); }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
} 

BinarySearchTree* initTree() {
    BinarySearchTree* tree = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));
    if (!tree) { printf("Tree allocation failed\n"); exit(1); }
    tree->root = NULL;
    return tree;
}

void freeTree(TreeNode* root) {
    if (!root) { free(root); return; }
    freeTree(root->left);
    freeTree(root->right);
}

/* == SEARCHING == */

/*
Complexity:
    Time:
        Best:    O(1)     - on root == target
        Average: O(log n) - on well balanced tree
        Worst:   O(n)     - on very unbalanced tree

        Technically, people sometimes say the time 
        complexity is O(h) where h is the height of
        the tree.
    
    Note all cases are the same for space.
*/
bool searchBST(TreeNode* root, int target) {
    if (!root) return false;
    if (target == root->val) return true;

    if (target < root->val) return searchBST(root->left, target);
    else                    return searchBST(root->right, target);
}