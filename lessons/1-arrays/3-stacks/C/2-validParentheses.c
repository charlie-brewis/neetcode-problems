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
#include <stdbool.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

bool isValid(char* s) {
    // The number of items in s = memSizeOfs / memSizeOfs[0]
    int sLength = strlen(s); 
    // Define the stack to be of capcacity sLength so we wont have to do any resizing
    char* stack = malloc(sizeof(char) * sLength);
    int stackTopIndex = -1;

    for (int i = 0; i < sLength; i++) {
        char c = s[i];

        // Push opening brackets
        if (c == '(' || c == '[' || c == '{') {
            stack[++stackTopIndex] = c;
            continue;
        }

        // If the stack is currently empty, return false
        if (stackTopIndex == -1) {
            free(stack);
            return false;
        }

        // If the top of the stack is not the corresponding opening bracket, the order is wrong, so invalid
        char top = stack[stackTopIndex];
        if (
            c == ')' && top != '(' ||
            c == ']' && top != '[' ||
            c == '}' && top != '{' 
            ) {
                free(stack);
                return false;
        }
        --stackTopIndex;
    }
    // If the stack is empty, all opening brackets have been paired, else there are unpaired opening brackets left
    free(stack);
    return stackTopIndex == -1;
}



int main() {
    printf("out: %d", isValid("]"));
    return 0;
}