
// If QUEUE_H is not already defined in the current file:
#ifndef QUEUE_H

// Define QUEUE_H
#define QUEUE_H

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* nodeCreate(int val, Node* next);


typedef struct Queue {
    Node* front;
    Node* back;
    int size;
} Queue;

Queue* queueCreate();
void queueFree(Queue* obj);
void enqueue(Queue* queue, int val);
int dequeue(Queue* queue);
void queueDisplay(Queue* queue);


// End QUEUE_H if
#endif