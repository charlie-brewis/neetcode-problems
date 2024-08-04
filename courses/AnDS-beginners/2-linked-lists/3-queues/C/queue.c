/*
Queues are First-In, First-Out (FIFO) data structures.
That is, items are removed from the queue exclusively in the order they were added.

Queues support 2 operations, enqueue, and dequeue - both O(1) time:
    Enqueue - placing an item at the end (back) of a queue, similar to append or push
    Dequeue - removing an item at the start (head) of a queue

Dequeue is why we use a linked list instead of an array for queues, as removing from the head of a 
linked list is in O(1) time, but O(n) time for arrays.
*/


#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


// typedef struct Node {
//     int val;
//     struct Node* next;
// } Node;

Node* nodeCreate(int val, Node* next) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = next;
    return newNode;
}


// typedef struct Queue {
//     Node* front;
//     Node* back;
//     int size;
// } Queue;

Queue* queueCreate() { 
    Queue* newQueue = (Queue*) malloc(sizeof(Queue)); 
    newQueue->front = newQueue->back = NULL;
    newQueue->size = 0;
    return newQueue;
}

void queueFree(Queue* obj) {
    Node* currentNode = obj->front;
    Node* nextNode;
    while (currentNode) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(obj);
}


void enqueue(Queue* queue, int val) {
    Node* newNode = nodeCreate(val, NULL);
    // If queue is non-empty
    if (queue->size++) {
       queue->back->next = newNode;
       queue->back = queue->back->next; 
    } else {
        // If queue is empty, set up queue
        queue->front = queue->back = newNode;
    }
}

int dequeue(Queue* queue) {
    // If queue is empty, return error code
    if (!queue->size--) return -1;

    int val = queue->front->val;
    Node* newHead = queue->front->next;
    free(queue->front);
    queue->front = newHead;
    // if the queue is now empty, set the tail to null
    if (!queue->front) queue->back = NULL;
    return val;
}

void queueDisplay(Queue* queue) {
    Node* currentNode = queue->front;
    while (currentNode) {
        printf("%d -> ", currentNode->val);
        currentNode = currentNode->next;
    }
    printf("\n");
}



// int main() {
//     Queue* myQueue = queueCreate();
//     enqueue(myQueue, 1);
//     enqueue(myQueue, 2);
//     enqueue(myQueue, 3);
//     queueDisplay(myQueue);
//     dequeue(myQueue);
//     queueDisplay(myQueue);
//     dequeue(myQueue);
//     queueDisplay(myQueue);

//     return 0;
// }


/*
Conclusion - Queues

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(1)       |Only at front
Insertion |O(1)       |Only at end
Deletion  |O(1)       |Only at end

*/