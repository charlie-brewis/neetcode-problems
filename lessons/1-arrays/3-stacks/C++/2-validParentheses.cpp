/*
https://leetcode.com/problems/valid-parentheses/description/


Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:
    Input: s = "()"
    Output: true

Example 2:
    Input: s = "()[]{}"
    Output: true

Example 3:
    Input: s = "(]"
    Output: false
 

Constraints:
    1 <= s.length <= 104
    s consists of parentheses only '()[]{}'.
*/
#include <iostream>

#include <string>
#include <stack>


bool isValid(std::string s) {
    std::stack<char> stack;
    
    for (char c : s) {
        // Push opening brackets
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else {
            // If the top of the stack is not the corresponding opening bracket, the order is wrong, so invalid
            if (stack.empty() ||
                c == ')' && stack.top() != '(' ||
                c == ']' && stack.top() != '[' ||
                c == '}' && stack.top() != '{' ){
                return false;
            }
            stack.pop();
        }
    }
    // If the stack is empty, all opening brackets have been paired, else there are unpaired opening brackets left
    return stack.empty();
}


int main() {
    std::cout << isValid("]"); 
    return 0;
}