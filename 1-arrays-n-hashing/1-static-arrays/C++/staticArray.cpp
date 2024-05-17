#include <iostream>

#define ARRAY_MAX_SIZE 10

class StaticArray {
    public:
        // StaticArray datastructure holds the array and it's current size
        int arr[ARRAY_MAX_SIZE];
        int currentSize;

        StaticArray() {
            // Initialise a static array by setting the size to 0 - i.e., empty
            currentSize = 0;
        }

        // This operation is O(1)
        int removeLast() {
            // Error code of -1 means the array was already empty
            if (currentSize == 0) {return -1;}
            // Overwrite the last element to some null-type value - the memory is still owned but it is considered empty
            // note this assumes -1 is an invalid value in the array
            arr[currentSize - 1] = -1;
            currentSize--;
            // Error code of 0 means no error was encountered
            return 0;
        }

        // In the worst case, n-1 shifts may be required, therefore this operation is O(n)
        int removeAtIndex(int i) {
            if (i >= currentSize || i < 0) {return -1;}
            for (int currentIndex = i + 1; currentIndex < currentSize; currentIndex++) {
                // Shift every item from i + 1 down by one to ensure array is contiguous
                arr[currentIndex - 1] = arr[currentIndex];
            }
            // No need to manually remove arr[i] as the shifting would've overridden it with arr[i + 1]
            currentSize--;
            return 0;
        }

        // Since this is always at the end, O(1)
        int append(int numToInsert) {
            // We can only append if the array isn't already full, since this is a static array
            if (currentSize == ARRAY_MAX_SIZE) {return -1;}
            arr[currentSize] = numToInsert;
            currentSize++;
            return 0;
        }

        // In the worst case, n-1 shifts may be required, therefore this operation is O(n)
        int insert(int i, int numToInsert) {
            if (currentSize == ARRAY_MAX_SIZE || i > currentSize || i < 0) {return -1;}
            for (int currentIndex = currentSize - 1; currentIndex >= i; currentIndex--) {
                // Shift every item from i up by one by iterating backwards until i
                arr[currentIndex + 1] = arr[currentIndex];
            }
            // Now insert since arr[i] is clear
            arr[i] = numToInsert;
            currentSize++;
            return 0;
        }


        // Const since this method does not modify the internal state of the array
        void display() const {
            std::cout << "\nStaticArray: [";
            for (int i = 0; i < currentSize; i++) {
                std::cout << arr[i] << ", ";
            }
            std::cout << "] ; " << currentSize;
        }
};

int main() {
    StaticArray myArray;
    myArray.display();
    myArray.append(1);
    myArray.append(2);
    myArray.append(5);
    myArray.display();
    myArray.insert(2, 3);
    myArray.display();
    myArray.removeLast();
    myArray.display();
    myArray.removeAtIndex(0);
    myArray.display();
    return 0;
}



/*
Conclusion - Static Arrays

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(1)       |
Insertion |O(n)       |O(1) at end - append
Deletion  |O(n)       |O(1) at end - pop?
*/