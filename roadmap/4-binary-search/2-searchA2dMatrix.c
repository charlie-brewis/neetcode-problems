/*
Medium 

You are given an m x n integer matrix matrix with the following two properties:
    - Each row is sorted in non-decreasing order.
    - The first integer of each row is greater than the last integer of the previous row.
    - Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

 
Example 1:
    Input: matrix = [
        [1,3,5,7],
        [10,11,16,20],
        [23,30,34,60]
        ], target = 3
    Output: true

Example 2:
    Input: matrix = [
        [1,3,5,7],
        [10,11,16,20],
        [23,30,34,60]
        ], target = 13
    Output: false
 
Constraints:
    - m == matrix.length
    - n == matrix[i].length
    - 1 <= m, n <= 100
    - -104 <= matrix[i][j], target <= 104
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LENGTH 100

int binarySearch(int* arr, int start, int end, int target) {
    if (start >= end) return start;

    int mid_i = (start + end) / 2;
    int mid_val = arr[mid_i];
    
    if (mid_val > target)      return binarySearch(arr, start, mid_i - 1, target);
    else if (mid_val < target) return binarySearch(arr, mid_i + 1, end, target);
    else return mid_i;
}

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    /*
        Plan:
            1. Define array of first column
            2. Perform binary search on this array - modify binary search to return start in base case
            3. We now have which row the target is in
            4. Perform binary search on this row - return bool
    */  
    // 1. Define array of first column
    int* firstCol = (int*) malloc(sizeof(int*) * MAX_LENGTH);
    for (int i = 0; i < matrixSize; i++) {
        firstCol[i] = matrix[i][0];
    }

    // 2. Perform binary search on this array
    int row_i = binarySearch(firstCol, 0, matrixSize - 1, target);
    printf("row_i = %d\n", row_i);

    // 4. Perform binary search on this row
    int target_i = binarySearch(matrix[row_i], 0, *matrixColSize, target);

    return (matrix[row_i][target_i] == target);
}



int main() {
    /*
    Example 1:
    Input: matrix = [
        [1,3,5,7],
        [10,11,16,20],
        [23,30,34,60]
        ], target = 3
    Output: true
    */
   
    int m = 3; // Num rows
    int n = 4; // Num cols

    // Allocate memory for matrix
    int** matrix = (int**) malloc(sizeof(int*) * m);
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * n);
    }

    int values[3][4] = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    // Populate Matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = values[i][j];
        }
    }

    int matrixColSize = n;

    printf("%d", searchMatrix(matrix, 3, &matrixColSize, 3));

    // Free allocated memory
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}