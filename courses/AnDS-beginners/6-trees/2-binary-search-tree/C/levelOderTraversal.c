
#include <stdlib.h>
#include <stdio.h>
#define MAX_NODES 2000
#define MAX_LEVELS MAX_NODES / 2

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

struct TreeNode* initTreeNode(const int val) {
    struct TreeNode* node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    if (node == NULL) { printf("TreeNode allocation failed. Exiting.\n"); exit(1); }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
} 

struct TreeNode* treeInsert(struct TreeNode* root, const int val) {
    if (root == NULL) return initTreeNode(val);

    if (val <= root->val) root->left  = treeInsert(root->left, val);
    else                  root->right = treeInsert(root->right, val);

    return root;
}

typedef struct QueueNode {
    struct TreeNode* node;
    struct QueueNode* next;
} QueueNode;

QueueNode* initQueueNode(struct TreeNode* treeNode) {
    QueueNode* node = (QueueNode*) malloc(sizeof(QueueNode));
    if (node == NULL) { printf("QueueNode allocation failed. Exiting.\n"); exit(1); }
    node->node = treeNode;
    node->next = NULL;
    return node;
}

typedef struct Queue {
    QueueNode* front;
    QueueNode* back;
    int length;
} Queue;

Queue* initQueue() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) { printf("Queue allocation failed. Exiting.\n"); exit(1); }
    queue->front = queue->back = NULL;
    queue->length = 0;
    return queue;
}

void enqueue(Queue* queue, struct TreeNode* node) {
    if (node == NULL) return; // Skip NULL values
    // If the queue is empty, set front and back
    if (queue->length++ == 0) {
        queue->front = queue->back = initQueueNode(node);
        return;
    }
    // Otherwise, enqueue normally
    queue->back->next = initQueueNode(node);
    queue->back = queue->back->next;
}

struct TreeNode* dequeue(Queue* queue) {
    if (queue->length == 0) { printf("Cannot dequeue empty queue. Exiting."); exit(1); }
    QueueNode* frontNode = queue->front;
    struct TreeNode* treeNode = frontNode->node;
    queue->front = queue->front->next;
    free(frontNode);
    --(queue->length);
    return treeNode;
}   

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    } 

    // Allocate memory for all 3 result fields
    int** levels = (int**) malloc(MAX_LEVELS * sizeof(int*)); // Allocate space for max number of levels
    *returnColumnSizes = (int*) malloc(MAX_LEVELS * sizeof(int)); // Allocate space for column sizes
    *returnSize = 0;

    // Initialise a queue for Breadth-first traversal
    Queue* queue = initQueue();
    enqueue(queue, root);

    while (queue->length > 0) {
        // Define current level
        int levelSize = queue->length; // Nodes at the current level
        levels[*returnSize] = (int*) malloc(levelSize * sizeof(int)); // Allocate space for number of nodes on this level
        (*returnColumnSizes)[*returnSize] = levelSize; // Define this column size

        // Process level
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* currentNode = dequeue(queue);
            levels[*returnSize][i] = currentNode->val;

            if (currentNode->left != NULL)  enqueue(queue, currentNode->left);
            if (currentNode->right != NULL) enqueue(queue, currentNode->right);
        }
        ++(*returnSize);
    }
    free(queue);
    return levels;
}


int main() {
    // Define tree
    struct TreeNode* root = initTreeNode(3);
    root = treeInsert(root, 9);
    root = treeInsert(root, 20);
    root = treeInsert(root, 15);
    root = treeInsert(root, 7);

    // Run algorithm
    int returnSize;
    int* returnColumnSizes;
    int** result = levelOrder(root, &returnSize, &returnColumnSizes);

    // Print result
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d, ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}