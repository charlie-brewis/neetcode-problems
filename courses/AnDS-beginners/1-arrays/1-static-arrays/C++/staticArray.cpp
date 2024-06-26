/*
A static array is a datastructure that contains a set number of cells located contiguously in memory.
It cannot grow or shrink, and each cell has a corresponding index number - the number of steps it is from the first cell.

Operations:
    -> accessLast - O(1)
    -> accessAt   - O(1)
    -> removeLast - O(1)
    -> removeAt   - O(n)
    -> insertLast - O(1)
    -> insertAt   - O(n)
*/

#include <iostream>

#define ARRAY_MAX_SIZE 10

class StaticArray {
    private:
        // StaticArray datastructure holds the array of a defined size and it's current length (i.e., number of cells populated by non-null values)
        int arr[ARRAY_MAX_SIZE];
        // Initialise a static array by setting the length to 0 - i.e., empty
        int currentLength = 0;

    public:
        int accessLast() {
            if (currentLength == 0) {return -1;}
            return arr[currentLength - 1];
        }
        
        // Finding an item in an array is always O(1) because arrays use indexing
        int accessAt(int i) {
            if (i > currentLength || i < 0 || currentLength == 0) {return -1;}
            return arr[i];
        }

        // This operation is O(1)
        int removeLast() {
            // Error code of -1 means the array was already empty
            if (currentLength == 0) {return -1;}
            // Overwrite the last element to some null-type value - the memory is still owned but it is considered empty
            // note this assumes -1 is an invalid value in the array
            arr[--currentLength] = -1;
            // Error code of 0 means no error was encountered
            return 0;
        }

        // In the worst case, n-1 shifts may be required, therefore this operation is O(n)
        int removeAtIndex(int i) {
            if (i >= currentLength || i < 0) {return -1;}
            for (int currentIndex = i + 1; currentIndex < currentLength; currentIndex++) {
                // Shift every item from i + 1 down by one to ensure array is contiguous
                arr[currentIndex - 1] = arr[currentIndex];
            }
            // No need to manually remove arr[i] as the shifting would've overridden it with arr[i + 1]
            --currentLength;
            return 0;
        }

        // Since this is always at the end, O(1)
        int append(int numToInsert) {
            // We can only append if the array isn't already full, since this is a static array
            if (currentLength == ARRAY_MAX_SIZE) {return -1;}
            arr[currentLength++] = numToInsert;
            return 0;
        }

        // In the worst case, n-1 shifts may be required, therefore this operation is O(n)
        int insert(int i, int numToInsert) {
            if (currentLength == ARRAY_MAX_SIZE || i > currentLength || i < 0) {return -1;}
            for (int currentIndex = currentLength - 1; currentIndex >= i; currentIndex--) {
                // Shift every item from i up by one by iterating backwards until i
                arr[currentIndex + 1] = arr[currentIndex];
            }
            // Now insert since arr[i] is clear
            arr[i] = numToInsert;
            ++currentLength;
            return 0;
        }



        // Const since this method does not modify the internal state of the array
        void display() const {
            std::cout << "\nStaticArray: [";
            for (int i = 0; i < currentLength; i++) {
                std::cout << arr[i] << ", ";
            }
            std::cout << "] ; " << currentLength;
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