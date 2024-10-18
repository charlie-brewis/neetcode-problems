
#include <stdlib.h>
#include <stdio.h>


void merge(int* arr, int start, int mid, int end) {
	int sizeLeft  = mid - start + 1;
	int sizeRight = end - mid;
	
	// Temporary arrays to hold the 2 halves
	int* copyLeft = (int*) malloc(sizeLeft * sizeof(int));
	int* copyRight = (int*) malloc(sizeRight * sizeof(int));
	
	// Copy the data into the temporary arrays
	for (int i = 0; i < sizeLeft; i++) copyLeft[i] = arr[start + i];
	for (int j = 0; j < sizeRight; j++) copyRight[j] = arr[mid + 1 + j];
	
	// Merge the temporary arrays back into arr
	int pLeft = 0;
	int pRight = 0;
	int pMerged = start;
	while (pLeft < sizeLeft && pRight < sizeRight) {
		if (copyLeft[pLeft] <= copyRight[pRight]) {
			arr[pMerged++] = copyLeft[pLeft++];
		} else {
			arr[pMerged++] = copyRight[pRight++];
		}
	}
	
	// Copy the remaining elements of the left subarray, if any
	while (pLeft < sizeLeft) arr[pMerged++] = copyLeft[pLeft++];
	
	// Copy the remaining elements of the right subarray, if any
	while (pRight < sizeRight) arr[pMerged++] = copyRight[pRight++];
	
	// Free allocated memory for array copies
	free(copyLeft);
	free(copyRight);
}



void mergeSort(int* arr, int start, int end) {
	// Sub arr size is 1 -> base case
	if (start >= end) return;
	
	int mid = (start + end) / 2;
	
	// merge sort the first half
	mergeSort(arr, start, mid);
	// merge sort the second half
	mergeSort(arr, mid + 1, end);
		
	// merge to 2 sorted halves
	merge(arr, start, mid, end);
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

    mergeSort(arr, 0, arr_size - 1);

    printf("Sorted array is \n");
    printArray(arr, arr_size);
    return 0;
}