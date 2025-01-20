/*
Given an integer array nums, return an array answer such that answer[i] is equal 
to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.


Example 1:
    Input: nums = [1,2,3,4]
    Output: [24,12,8,6]

Example 2:
    Input: nums = [-1,1,0,-3,3]
    Output: [0,0,9,0,0]
 

Constraints:
    - 2 <= nums.length <= 10^5
    - -30 <= nums[i] <= 30
    - The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.

*/
#include <stdlib.h>
#include <stdio.h>

#define MAX_LENGTH 100000


int productOfSubArr(int* arr, int start, int end) {
    // Edge cases
    if (start > end) return 1;  // For last item
    if (start == end) return arr[start]; // For second-last item

    // Calculate the product between the ranges
    int ans = arr[start];
    for (int i = start + 1; i <= end; i++) ans *= arr[i];
    return ans;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// O(n^2)
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    // Define return values
    *returnSize = numsSize;
    int* returnArr = (int*) malloc(sizeof(int) * *returnSize);

    // Sequentially calculate prefixProduct * suffixProduct
    for (int i = 0; i < numsSize; i++) {
        int prefixProduct = productOfSubArr(nums, 0, i - 1);
        int suffixProduct = productOfSubArr(nums, i + 1, numsSize - 1);
        printf("i: %d, prefix: %d, suffix: %d\n", i, prefixProduct, suffixProduct);

        returnArr[i] = prefixProduct * suffixProduct;
    }

    return returnArr;
}


int main () {

    int myArr[4] = {1, 2, 3, 4};
    int returnSize = 0;

    int* res = productExceptSelf(myArr, 4, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d, ", res[i]);
    }

    free(res);

    return 0;
}