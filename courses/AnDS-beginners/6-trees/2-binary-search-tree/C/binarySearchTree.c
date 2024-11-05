
#include <stdlib.h>
#include <stdio.h>
#define COUNT 10


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


TreeNode* findMin(TreeNode* root) {
    TreeNode* currentNode = root;
    while (currentNode && currentNode->left) { currentNode = currentNode->left; }
    return currentNode;
}

TreeNode* findMax(TreeNode* root) {
    TreeNode* currentNode = root;
    while (currentNode && currentNode->right) { currentNode = currentNode->right; }
    return currentNode;
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
TreeNode* searchBST(TreeNode* root, int target) {
    if (!root)               return NULL;
    if (target == root->val) return root;

    if (target < root->val) return searchBST(root->left, target);
    else                    return searchBST(root->right, target);
}


/* == INSERTING == */

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
TreeNode* BSTInsert(TreeNode* root, int val) {
    if (!root) return initNode(val);

    if (val <= root->val) root->left  = BSTInsert(root->left, val);
    else                  root->right = BSTInsert(root->right, val);

    return root;
}


/* == DELETION == */


/*
Complexity:
    Time:
        Best Case: O(log n)
            - When node has 1 child
            - Traverse to find node O(log n)

        Average Case: O(log n)

        Worst Case: O(log n)
            - When node is root node
            - Traverse to find node             O(1)
            - Traverse to find max node         O(log n)
            - Traverse again to delete max node O(log n)
    
    Space is also always O(log n)
*/

TreeNode* BSTDelete(TreeNode* root, int val) {
/*
    When deleting a TreeNode there are 2 cases:
        Case 1: 0 or 1 child
        Case 2: 2 children 
*/
    if (!root) return NULL; // Edge case

    // Traverse until we find target node
    if (val > root->val)      root->right = BSTDelete(root->right, val);
    else if (val < root->val) root->left = BSTDelete(root->left, val);
    
    // Target Node found
    else {
        // Case 1: return the opposite side to the null side
        if (root->left == NULL)       return root->right;
        else if (root->right == NULL) return root->left;

        // Case 2: Find the maximum node from the left subtree replace target's value with it.
        //         - This ensures the tree remains ordered.
        //         - Now delete the old node where this value was found - always case 1.
        else {
            TreeNode* maxNodeLeftSubtree = findMax(root->left);
            root->val = maxNodeLeftSubtree->val;
            root->left = BSTDelete(root->left, root->val);
        }
    }

    return root;
}
// Note ive decided to find the maximum from the left subtree but this can also be done with the 
// minimum from the right subtree.



// Function to print binary tree in 2D
void print2DUtil(TreeNode* root, int space) {
    // Base case
    if (root == NULL) return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->val);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(TreeNode* root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}




int main() {
    BinarySearchTree* myTree = initTree();
    
    myTree->root = BSTInsert(myTree->root, 4);
    BSTInsert(myTree->root, 3);
    BSTInsert(myTree->root, 2);
    BSTInsert(myTree->root, 6);
    BSTInsert(myTree->root, 7);
    BSTInsert(myTree->root, 5);

    print2D(myTree->root);
    printf("\n");

    BSTDelete(myTree->root, 4);

    print2D(myTree->root);
    printf("\n");

    BSTDelete(myTree->root, 5);

    print2D(myTree->root);
    printf("\n");

    return 0;
}