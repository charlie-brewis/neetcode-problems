/*
A stack is a datastructure that contains a dynamic number of cells located contiguously in memory.
Stacks do not require index numbers as we only ever access the last item in the stack.
Like a dynamic, it can dynamically increase it's capacity.
Actually, stacks are implemented as literally just dynamic arrays but only with push, pop, and peak operations

Operations:
    -> peak (accessLast) - O(1)
    -> pop (removeLast)  - O(1)
    -> push (insertLast) - O(1)
*/

#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_CAPACITY 1

typedef struct {
    int length;
    int capacity;
    // Pointer to the start of the stack
    int* data;
} Stack;

// Double size of stack since they are built of dynamic arrays
static void resize(Stack* stack) {
    stack->capacity *= 2;
    stack->data = (int*) realloc(stack->data, stack->capacity * sizeof(int));
}

Stack* initialiseStack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->length = 0;
    stack->capacity = DEFAULT_CAPACITY;
    resize(stack);
    return stack;
}

int peak(Stack* stack) {
    if (stack->length == 0) {return -1;}
    return stack->data[stack->length - 1];
}

int pop(Stack* stack) {
    if (stack->length == 0) {return -1;}
    return stack->data[stack->length--];    
}

int push(Stack* stack, int value) {
    if (stack->length == stack->capacity) {
        resize(stack);
    }
    stack->data[stack->length++] = value;
    return 0;
}

void freeMemory(Stack* stack) {
    free(stack->data);
    free(stack);
}

/*
Conclusion - Stacks

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(1)       |Only possible on last item
Insertion |O(1)       |Only possible on last item, amortised
Deletion  |O(1)       |Only possible on last item
*/