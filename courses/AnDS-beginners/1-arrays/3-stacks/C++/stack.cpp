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

#include <iostream>

class Stack {
    private:
        int length;
        int capacity;
        int* data;

        void resize() {
            capacity *= 2;
            int* newArr = new int[capacity];
            for (int i = 0; i < length; i++) {
                newArr[i] = data[i];
            }
            delete[] data;
            data = newArr;
        }

    public:
        Stack() {
            length = 0;
            capacity = 3;
            data = new int[capacity];
        }

        ~Stack() {
            delete[] data;
        }

        int peak() {
            if (length == 0) {return -1;}
            return data[length - 1];
        }

        int pop() {
            if (length == 0) {return -1;}
            return data[length--];
        }

        void push(int numToPush) {
            if (length == capacity) {
                resize();
            }
            // Insert numToPush at the end of the array, then increment length
            data[length++] = numToPush;
        }
};

/*
Conclusion - Stacks

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(1)       |Only possible on last item
Insertion |O(1)       |Only possible on last item, amortised
Deletion  |O(1)       |Only possible on last item

* Note: in C++, like how we use `vector`s for dynamic arrays, we can use the `stack` type for stacks
*/