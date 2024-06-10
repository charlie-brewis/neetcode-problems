/*
https://leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:
    MinStack() initializes the stack object.
    void push(int val) pushes the element val onto the stack.
    void pop() removes the element on the top of the stack.
    int top() gets the top element of the stack.
    int getMin() retrieves the minimum element in the stack.
    You must implement a solution with O(1) time complexity for each function.

 
Example 1:
    Input
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]

    Output
    [null,null,null,null,-3,null,0,-2]

    Explanation
    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin(); // return -3
    minStack.pop();
    minStack.top();    // return 0
    minStack.getMin(); // return -2
 

Constraints:
    - -231 <= val <= 231 - 1
    - Methods pop, top and getMin operations will always be called on non-empty stacks.
    - At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
*/
#include <stdlib.h>
#include <stdio.h>

// Taken from constraints
#define MAX_STACK_SIZE 30000


typedef struct {
    // Stack stores the stack of values, minIndicies stores the indicies of the minimum values in 
    // the smallest value index is at the back, the second smallest at the second back, and so on
    int* stack;
    int* minIndicies;
    int stackLength;
    int minIndiciesLength;
} MinStack;


MinStack* minStackCreate() {
    MinStack* minStack = (MinStack*) malloc(sizeof(MinStack));
    minStack->stack = (int*) malloc(MAX_STACK_SIZE * sizeof(int));
    minStack->minIndicies = (int*) malloc(MAX_STACK_SIZE * sizeof(int));
    minStack->stackLength = 0;
    minStack->minIndiciesLength = 0;
    return minStack;
}

void minStackPush(MinStack* obj, int val) {
    int minIndiciesBack = obj->minIndicies[obj->minIndiciesLength - 1];
    // If minIndicies is empty OR the val is less than the minimum value, push the current size of stack to the back of minIndicies
    if (
        obj->minIndiciesLength == 0 || 
        val < obj->stack[minIndiciesBack])
    {
        obj->minIndicies[obj->minIndiciesLength++] = obj->stackLength;
    }
    obj->stack[obj->stackLength++] = val;
}

void minStackPop(MinStack* obj) {
    --obj->stackLength;
    // If the value just popped was the smallest value (back of minIndicies), then pop minIndicies too
    if (obj->minIndicies[obj->minIndiciesLength - 1] == obj->stackLength) --obj->minIndiciesLength;
}

int minStackTop(MinStack* obj) { return obj->stack[obj->stackLength - 1]; }

int minStackGetMin(MinStack* obj) { return obj->stack[obj->minIndicies[obj->minIndiciesLength - 1]]; }

void minStackFree(MinStack* obj) { free(obj); }

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/


int main() {
    MinStack* obj = minStackCreate();
    minStackPush(obj, -2);
    minStackPush(obj, 0);
    minStackPush(obj, -3);
    printf("%d\n", minStackGetMin(obj));
    minStackPop(obj);
    printf("%d\n", minStackTop(obj));
    printf("%d\n", minStackGetMin(obj));
    return 0;
}

