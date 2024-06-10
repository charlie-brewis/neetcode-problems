/*
A dynamic array is a datastructure that contains a dynamic number of cells located contiguously in memory.
Each cell has a corresponding index number - the number of steps it is from the first cell.
Unlike a static array, it can dynamically increase it's capacity.

Operations:
    -> accessLast - O(1)
    -> accessAt   - O(1)
    -> removeLast - O(1)
    -> removeAt   - O(n)
    -> insertLast - O(1)
    -> insertAt   - O(n)
*/

#include <iostream>


class DynamicArray {
    private:
        // The current capacity of our array
        int capacity;
        // The current length of our array
        int length;
        // A pointer, pointing to the first location of a new area of memory allocated for 3 integers on the heap
        // I.e., pointing to the first index in a new array with a capcity for 3 integers assigned on the heap
        int* arr;

        // When we resize a dynamic array, we actually double it's size - keeping the average time complexity of insertion and removal to O(n)
        // Note: the reason this works is quite maths-y so i won't explain it here
        void resize() {
            // Create a new array of double capacity
            capacity *= 2;
            int* newArr = new int[capacity];
            // Copy current elements over to the new array
            for (int i = 0; i < length; i++) {
                newArr[i] = arr[i];
            }
            // Free memory of old array and reassign pointer to new array
            delete[] arr;
            arr = newArr;
        }

    public:
        DynamicArray() {
            capacity = 3;
            length = 0;
            arr = new int[capacity];
        }

        // We need to make sure to free any memory we've allocated on the heap after we've finished using it
        // This is to prevent memory leaks which can slow down and crash our program
        ~DynamicArray() {
            delete[] arr;
        }

        int accessLast() {
            if (length == 0) {return -1;}
            return arr[length - 1];
        }

        // Just like a static array, we can make use of indexes to get any item at a defined index in O(1) time
        int accessAt(int i) {
            if (i > length || i < 0 || length == 0) {return -1;}
            return arr[i];
        }

        // Since pop always targets the last item in the array, it is O(1)
        int removeLast() {
            if (length == 0) {return -1;}
            // By decrementing our length, we are now essentially disregaurding the old last value - we never consider a value past our length as non-null
            return arr[length--];
        }

        // O(n) - same as static array
        int removeAt(int i) {
            if (i >= length || i < 0) {return -1;}
            for (int currI = i + 1; currI < length; currI++) {
                arr[currI - 1] = arr[currI];
            }
            --length;
            return 0;
        }

        // Again for push, O(1); however, the possiblilty of resizing [O(n)] is the case we still define this as O(1) - "amortised complexity"
        void append(int numToPush) {
            if (length == capacity) {
                resize();
            }
            // Insert numToPush at the end of the array, then increment length
            arr[length++] = numToPush;
        }

        // O(n) - technically O(2n) but we simplify any multiplicative or additive constants in big-O
        int insert(int i, int numToInsert) {
            if (i >= length || i < 0) {return -1;}
            if (length == capacity) {
                resize();
            }
            for (int currentIndex = length - 1; currentIndex >= i; currentIndex--) {
                arr[currentIndex + 1] = arr[currentIndex];
            }
            arr[i] = numToInsert;
            ++length;
            return 0;
        }

        void display() {
            std::cout << "StaticArray[";
            for (int i = 0; i < length; i++) {
                std::cout << arr[i] << ", ";
            }
            std::cout << "] : " << length << " : " << capacity << "\n";
        }
};



int main() {
    // Note how dynamic array methods are the same as static arrays, with the added conditional resize
    DynamicArray myDynamicArray = DynamicArray();
    myDynamicArray.append(1);
    myDynamicArray.append(2);
    myDynamicArray.append(3);
    myDynamicArray.display();
    myDynamicArray.append(4);
    myDynamicArray.display();
    myDynamicArray.insert(2, 5);
    myDynamicArray.display();
    myDynamicArray.removeAt(3);
    myDynamicArray.display();
    return 0;
}


/*
Conclusion - Dynamic Arrays

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(1)       |
Insertion |O(n)       |O(1) at end - append
Deletion  |O(n)       |O(1) at end - pop?
*/


//* Note: 
//*     C++ has an inbuilt dynamic array type (vector) which we can use in the future when working with dynamic arrays.
//*     We only implemented it here to understand how it works.