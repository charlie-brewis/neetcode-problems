/*
Multi-branch recursion is when there is multiple recursive calls in a single recursive case.
Take the fibonacci sequence as an example:
        f(n) = f(n - 1) + f(n - 2); f(0) = 0; f(1) = 1
As you can see, in the general (recursive) case, the function calls itself twice, therefore it is a
multi-branch recursion.


Say we want to calculate f(5):
        f(5) = f(4) + f(3)
               f(4) = f(3) + f(2)
                      f(3) = f(2) + f(1)
                             f(2) = f(1) + f(0) = 1 + 0
        Note: this is only the left recursive branch starting from f(4), f(3) would also have its own
              recursive branch (unless memoisation is used). The full branch-trace looks like this:
                `courses/AnDS-beginners/3-recursion/2-multi-branch-recursion/fib5.PNG`

These multi-branch recursive solutions are often quite inefficient and so should be avoided wherever possible.
For example, this has an average time complexity of O(2^n), where the iterative approach is O(n)
*/


#include <stdlib.h>

/*
Time complexity:  O(2^n)
Space complexity: O(n)
*/
int fib(int n) {
    // Base cases
    if (n <= 1) return n;
    // Recursive cases
    return fib(n - 1) + fib(n - 2);
}


/*
Time complexity:  O(n)
Space complexity: O(1)
*/
int fibIterative(int n) {
        if (n <= 1) return n;
        //              f(0)       f(1)
        int fibNum = 0, prev1 = 0, prev2 = 1;
        for (int i = 2; i <= n; i++) {
                fibNum = prev1 + prev2;
                prev1 = prev2;
                prev2 = fibNum; 
        }
        return fibNum;
}


// Therefore, here it would be better to use the iterative approach as it has a lower time and space complexity.