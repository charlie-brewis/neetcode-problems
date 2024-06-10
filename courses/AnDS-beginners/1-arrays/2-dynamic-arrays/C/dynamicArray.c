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

#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_CAPACITY 1


typedef struct {
    int length;
    int capcaity;
    // Pointer to the start of the array
    int* arr;
} DynamicArray;

// When we resize a dynamic array, we actually double it's size - keeping the average time complexity of an insert or removal to O(n)
// Note: the reason this works is quite maths-y so i won't explain it here
static void resize(DynamicArray* array) {
    array->capcaity *= 2;
    array->arr = (int*)realloc(array->arr, array->capcaity * sizeof(int)); 
}

DynamicArray* intialiseDynamicArray() {
    // Define a pointer to allocated memory for the DynamicArray datastructure
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray)); 
    array->length = 0;
    array->capcaity = DEFAULT_CAPACITY;
    resize(array);
    return array;
}

int accessLast(DynamicArray* array) {
    if (array->length == 0) {return -1;}
    return array->arr[array->length - 1];
}

// Just like a static array, we can make use of indexes to get any item at a defined index in O(1) time
int accessAt(DynamicArray* array, int i) {
    if (i > array->length || i < 0 || array->length == 0) {return -1;}
    return array->arr[i];
}

// Since pop always targets the last item in the array, it is O(1)
int removeLast(DynamicArray* array) {
    if (array->length == 0) {return -1;}
    // By decrementing our length, we are now essentially disregaurding the old last value - we never consider a value past our length as non-null
    return array->arr[array->length--];
} 

// O(n) - same as static array
int removeAt(DynamicArray* array, int i) {
    if (i > array->length || i < 0) {return -1;}
    for (int curI = i + 1; curI < array->length; curI++) {
        array->arr[curI - 1] = array->arr[curI];
    }
    --array->length;
    return 0;
}

// Again for push, O(1); however, the possiblilty of resizing [O(n)] is the case we still define this as O(1) - "amortised complexity"
int append(DynamicArray* array, int value) {
    if (array->length == array->capcaity) {
        resize(array);
    }
    array->arr[array->length++] = value;
    return 0;
}

// O(n) - technically O(2n) but we simplify any multiplicative or additive constants in big-O
int insertAt(DynamicArray* array, int i, int value) {
    if (i > array->length || i < 0) {return -1;}
    if (array->length == array->capcaity) {
        resize(array);
    }
    for (int curI = array->length - 1; curI >= i; curI--) {
        array->arr[curI + 1] = array->arr[curI];
    }
    array->arr[i] = value;
    ++array->length;
    return 0;
}

// We need to make sure to free any memory we've allocated on the heap after we've finished using it
// This is to prevent memory leaks which can slow down and crash our program
void freeMemory(DynamicArray* array) {
    free(array->arr);
    free(array);
}

void displayDynamicArray(DynamicArray* array) {
    printf("DynamicArray[");
    for (int i = 0; i < array->length; i++) {
        printf("%d, ", array->arr[i]);
    }
    printf("] : %d : %d\n", array->length, array->capcaity);
}



int main() {
    // Note how dynamic array methods are the same as static arrays, with the added conditional resize
    DynamicArray* myDynamicArray = intialiseDynamicArray();
    append(myDynamicArray, 1);
    displayDynamicArray(myDynamicArray);
    append(myDynamicArray, 2);
    displayDynamicArray(myDynamicArray);
    append(myDynamicArray, 3);
    displayDynamicArray(myDynamicArray);
    insertAt(myDynamicArray, 2, 4);
    displayDynamicArray(myDynamicArray);
    removeAt(myDynamicArray, 3);
    displayDynamicArray(myDynamicArray);
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