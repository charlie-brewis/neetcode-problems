#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_CAPACITY 1


typedef struct {
    int length;
    int capcaity;
    // Pointer to the start of the array
    int* arr;
} DynamicArray;

static void resize(DynamicArray* array) {
    array->capcaity *= 2;
    array->arr = (int*)realloc(array->arr, array->capcaity * sizeof(int)); 
}

DynamicArray* intialiseDynamicArray() {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray)); 
    array->arr = NULL;
    array->length = 0;
    array->capcaity = DEFAULT_CAPACITY;
    resize(array); // allocate memory for the array
    return array;
}


int getAt(DynamicArray* array, int i) {
    if (i > array->length || i < 0) {return -1;}
    return array->arr[i];
}

int popBack(DynamicArray* array) {
    if (array->length == 0) {return -1;}
    return array->arr[array->length--];
} 

int pushBack(DynamicArray* array, int value) {
    if (array->length == array->capcaity) {
        resize(array);
    }
    array->arr[array->length++] = value;
    return 0;
}

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

int removeAt(DynamicArray* array, int i) {
    if (i > array->length || i < 0) {return -1;}
    for (int curI = i + 1; curI < array->length; curI++) {
        array->arr[curI - 1] = array->arr[curI];
    }
    --array->length;
    return 0;
}

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
    DynamicArray* myDynamicArray = intialiseDynamicArray();
    pushBack(myDynamicArray, 1);
    displayDynamicArray(myDynamicArray);
    pushBack(myDynamicArray, 2);
    displayDynamicArray(myDynamicArray);
    pushBack(myDynamicArray, 3);
    displayDynamicArray(myDynamicArray);
    insertAt(myDynamicArray, 2, 4);
    displayDynamicArray(myDynamicArray);
    removeAt(myDynamicArray, 3);
    displayDynamicArray(myDynamicArray);
    return 0;
}