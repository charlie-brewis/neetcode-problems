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
    - At most 3 * 104 calls will be made to push, pop, top, and getMin.
*/
#include <iostream>
#include <vector>

class MinStack {
    private:
        // Stack stores the stack of values, minIndicies stores the indicies of the minimum values in stack
        // the smallest value index is at the back, the second smallest at the second back, and so on
        std::vector<int> stack, minIndicies;

    public:
        void push(int val) 
        {
            // If minIndicies is empty OR the val is less than the minimum value, push the current size of stack to the back of minIndicies
            if (minIndicies.empty() || val < stack[minIndicies.back()]) 
            {
                minIndicies.push_back(stack.size());
            }
            stack.push_back(val);
        }
        
        void pop() 
        {
            stack.pop_back();
            // If the value just popped was the smallest value (back of minIndicies), then pop minIndicies too
            if (minIndicies.back() == stack.size()) minIndicies.pop_back();
        }
        
        int top() { return stack.back(); }
        
        int getMin() { return stack[minIndicies.back()]; }
};


int main() {
    MinStack minStack = MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    std::cout << minStack.getMin() << "\n"; // return -3
    minStack.pop();
    std::cout << minStack.top() << "\n";    // return 0
    std::cout << minStack.getMin() << "\n"; // return -2
    
}