
#include <stdlib.h>
#include <stdio.h>

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

struct TreeNode* insert(struct TreeNode* root, const int val) {
    if (root == NULL) return initNode(val);

    if (val <= root->val) root->left  = insert(root->left, val);
    else                  root->right = insert(root->right, val);

    return root;
}

typedef struct QueueNode {
    int val;
    struct QueueNode* next;
} QueueNode;

QueueNode* initQueueNode(const int val) {
    QueueNode* node = (QueueNode*) malloc(sizeof(QueueNode));
    if (node == NULL) { printf("QueueNode allocation failed. Exiting.\n"); exit(1); }
    node->val = val;
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

void enqueue(Queue* queue, const int val) {
    // If the queue is empty, set front and back
    if (queue->length++ == 0) {
        queue->front = queue->back = initQueueNode(val);
        return;
    }
    // Otherwise, enqueue normally
    queue->back->next = initQueueNode(val);
    queue->back = queue->back->next;
}

QueueNode* dequeue(Queue* queue) {
    if (queue->length++ == 0) { printf("Cannot dequeue empty queue. Exiting."); exit(1); }
    QueueNode* returnNode = queue->front;
    queue->front = queue->front->next;
    return returnNode;
}   

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    // Use a queue for Breadth-first traversal
    
}