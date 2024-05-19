#include <iostream>


class DynamicArray {
    private:
        // The current capacity of our array
        int capacity = 3;
        // The current length of our array
        int length = 0;
        // A pointer, pointing to the first location of a new area of memory allocated for 3 integers on the heap
        // I.e., pointing to the first index in a new array with a capcity for 3 integers assigned on the heap
        int *arr = new int[capacity];

    public:
        // Deconstructor frees allocated heap memory to ensure no memory leaks
        ~DynamicArray() {
            delete[] arr;
        }

        int getAt(int i) {
            if (i > length || i < 0) {return -1;}
            return arr[i];
        }

        // Note: this is considered O(1), even though it is sometimes O(n). I'm not exactly sure why but it's called "amortised complexity".
        void pushBack(int numToPush) {
            if (length == capacity) {
                resize();
            }
            // Insert numToPush at the end of the array, then increment length
            arr[length++] = numToPush;
        }

        // O(1)
        int popBack() {
            if (length == 0) {return -1;}
            // By decrementing our length, we are now essentially disregaurding the old base value - we never consider a value past our length as non-null
            --length;
            return 0;
        }

        // O(n)
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

        // O(n)
        int removeAt(int i) {
            if (i >= length || i < 0) {return -1;}
            for (int currI = i + 1; currI < length; currI++) {
                arr[currI - 1] = arr[currI];
            }
            --length;
            return 0;
        }

        void display() {
            std::cout << "StaticArray[";
            for (int i = 0; i < length; i++) {
                std::cout << arr[i] << ", ";
            }
            std::cout << "] : " << length << " : " << capacity << "\n";
        }

    private:
        // Note this operation has an O(n) time complexity
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
};



int main() {
    // Note how dynamic array methods are the same as static arrays, with the added conditional resize
    DynamicArray myDynamicArray = DynamicArray();
    myDynamicArray.pushBack(1);
    myDynamicArray.pushBack(2);
    myDynamicArray.pushBack(3);
    myDynamicArray.display();
    myDynamicArray.pushBack(4);
    myDynamicArray.display();
    myDynamicArray.insert(2, 5);
    myDynamicArray.display();
    myDynamicArray.removeAt(3);
    myDynamicArray.display();
    return 0;
}