#include <iostream>


int main() {
    int arrLength = 3;
    // elementType varName[arrLength] = {arrElements};
    int myArray[arrLength] = {1, 3, 5};

    // Accessing any element in an array is O(1) because of indexes
    std::cout << myArray[1];

    // We can traverse through arrays using for and while loops, since the memory is contiguous
    for (int i = 0; i < arrLength; i++) {
        std::cout << myArray[i];
    }
    int i = 0;
    while (i < arrLength) {
        std::cout << myArray[i];
        i++;
    }


    return 0;
}


// This operation is O(1)
void removeLast(int arr[], int length) {
    if (length > 0) {
        // Overwrite the last element to some null-type value - that memory is still reserved for this array
        arr[length - 1] = 0;
    }
}

// In the worst case, n-1 shifts may be required, therefore this operation is O(n)
void removeAtIndex(int arr[], int i, int length) {
    for (int curIndex = i + 1; curIndex < length; curIndex++) {
        // Shift every item from i + 1 down by one to ensure array is contiguous
        arr[curIndex - 1] = arr[curIndex];
    }
    // No need to manually remove arr[i] as the shifting would've overridden it with arr[i + 1]
}

// Since this is always at the end, O(1)
void append(int arr[], int numToInsert, int length, int arrCapacity) {
    // We can only append if the array isn't already full, since this is a static array
    if (length < arrCapacity) {
        arr[length] = numToInsert;
    }
}

void insert(int arr[], int i, int numToInsert, int length, int arrCapacity) {
    if (length == arrCapacity) return;
    for (int curIndex = length - 1; curIndex >= i; curIndex--) {
        // Shift every item from i up by one by iterating backwards until i
        arr[curIndex + 1] = arr[curIndex];
    }
    // Now insert since arr[i] is clear
    arr[i] = numToInsert;
}


/*
Conclusion - Static Arrays

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(1)       |
Insertion |O(n)       |O(1) at end - append
Deletion  |O(n)       |O(1) at end - pop?
*/
