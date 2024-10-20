
#include <stdio.h>


void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}



void quickSort(int* arr, int start, int end) {
	// Subarray size is <= 1, therefore sorted - base case
	if (start >= end) return;
	
	int pivot = arr[end];
	int nextLeasti = start;
	
	// Partion so elements smaller than the pivot are swapped to the left side
	for (int i = start; i < end; i++) {
		if (arr[i] < pivot) swap(arr, nextLeasti++, i); 
	}
	
	// Place the pivot between the 2 groups
	swap(arr, nextLeasti, end);
	
	// Recursively call, excluding pivot position
	quickSort(arr, start, nextLeasti - 1);
	quickSort(arr, nextLeasti + 1, end);
}




void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function to test merge sort
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    quickSort(arr, 0, arr_size - 1);

    printf("Sorted array is \n");
    printArray(arr, arr_size);
    return 0;
}