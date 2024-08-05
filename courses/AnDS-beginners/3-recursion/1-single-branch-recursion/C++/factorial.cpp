/*
Recursion is the concept of a function calling itself.
Each recursive function can have 2 cases:
    1) The recursive case - when the function recurses (calls itself again)
    2) The base case - when the recursion ends and a value is returned

Note, recursive functions can have multiple recursive cases, e.g., given some condition the input variables change.

Single branch recursion is when each recursive case of the function only has one recursive call.
An example of this is the factorial equation:
    `n! = n * (n-1) * (n-2) * ... * 1`
In this equation, 1 is the base case and factorial(n - 1) is the recursive case.

This is single branch recursion because each call of factorial() only ever calls factorial() again once.
*/

#include <iostream>

int factorial(int n) {
    // Base case where n == 1
    if (n == 1) return n;
    // Recursive case any other time
    return n * factorial(n - 1);
}

int main() {
    std::cout << factorial(5);
}