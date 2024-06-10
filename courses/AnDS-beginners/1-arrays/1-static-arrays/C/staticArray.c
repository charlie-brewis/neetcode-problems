
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

#include <stdio.h>

#define ARRAY_MAX_SIZE 10

// StaticArray datastructure holds the array of a defined size and it's current length (i.e., number of cells populated by non-null values)
typedef struct {
    int arr[ARRAY_MAX_SIZE];
    int currentLength;
} StaticArray;

void initialise(StaticArray* array) {
    // Initialise a static array by setting the length to 0 - i.e., empty
    array->currentLength = 0;
}

int accessLast(StaticArray* array) {
    if (array->currentLength == 0) {return -1;}
    return array->arr[array->currentLength - 1];
}

int accessAt(StaticArray* array, int i) {
    if (i > array->currentLength || i < 0 || array->currentLength == 0) {return -1;}
    return array->arr[i];
}

// This operation is O(1)
int removeLast(StaticArray* array) {
    if (array->currentLength > 0) {
        // Overwrite the last element to some null-type value - the memory is still owned but it is considered empty
        // note this assumes -1 is an invalid value in the array
        array->arr[--array->currentLength] = -1;
        // Error code of 0 means no error was encountered
        return 0;
    }
    // Error code of -1 means the array was already empty
    return -1;
}

// In the worst case, n-1 shifts may be required, therefore this operation is O(n)
int removeAtIndex(StaticArray* array, int i) {
    if (i >= array->currentLength || i < 0) {return -1;}
    // Assign a local pointer to make the code less verbose
    int* arr = array->arr;
    for (int currentIndex = i + 1; currentIndex < array->currentLength; currentIndex++) {
        // Shift every item from i + 1 down by one to ensure array is contiguous
        arr[currentIndex - 1] = arr[currentIndex];
    }
    // No need to manually remove arr[i] as the shifting would've overridden it with arr[i + 1]
    --array->currentLength;
    return 0;
}

// Since this is always at the end, O(1)
int append(StaticArray* array, int numToInsert) {
    // We can only append if the array isn't already full, since this is a static array
    if (array->currentLength < ARRAY_MAX_SIZE) {
        array->arr[array->currentLength++] = numToInsert;
        return 0;
    }
    return -1;
}

// In the worst case, n-1 shifts may be required, therefore this operation is O(n)
int insert(StaticArray* array, int i, int numToInsert) {
    int* arr = array->arr;
    // & means a reference to the variable - i.e., arrLength is a pointer to array->currentLength
    int* arrLength = &(array->currentLength);
    // *arrLength means the value pointed to by arrLength
    if (*arrLength == ARRAY_MAX_SIZE || i > *arrLength || i < 0) {return -1;}

    for (int currentIndex = *arrLength - 1; currentIndex >= i; currentIndex--) {
        // Shift every item from i up by one by iterating backwards until i
        arr[currentIndex + 1] = arr[currentIndex];
    }
    // Now insert since arr[i] is clear
    arr[i] = numToInsert;
    // Increment the value that arrLength is pointing to
    (*arrLength)++;
}


// Const since this method does not modify the internal state of the array object
void displayArray(const StaticArray* array) {
    printf("\nStaticArray: [");
    for (int i = 0; i < array->currentLength; i++) {
        printf("%d, ", array->arr[i]);
    }
    printf("] ; %d\n", array->currentLength);
}


int main() {
    StaticArray myArray;
    initialise(&myArray);
    displayArray(&myArray);
    append(&myArray, 1);
    append(&myArray, 2);
    append(&myArray, 5);
    displayArray(&myArray);
    insert(&myArray, 2, 3);
    displayArray(&myArray);
    removeLast(&myArray);
    displayArray(&myArray);
    removeAtIndex(&myArray, 0);
    displayArray(&myArray);
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