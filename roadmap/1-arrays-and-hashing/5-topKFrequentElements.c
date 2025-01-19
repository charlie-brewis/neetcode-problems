/* 
Medium

Given an integer array nums and an integer k, return the k most frequent elements. 
You may return the answer in any order.

Example 1:
    Input: nums = [1,1,1,2,2,3], k = 2
    Output: [1,2]

Example 2:
    Input: nums = [1], k = 1
    Output: [1]
 
Constraints:
    - 1 <= nums.length <= 10^5
    - -10^4 <= nums[i] <= 10^4
    - k is in the range [1, the number of unique elements in the array].
    - It is guaranteed that the answer is unique.
 
Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define OFFSET 10000
#define NUMS_MAX_LENGTH (2 * OFFSET + 1)  // Ensure the counter is large enough to handle the entire range

void displayArr(int* arr, int arrSize) {
    printf("[");
    for(int i = 0; i < arrSize; i++) printf("%d, ", arr[i]);
    printf("]\n");
}

int getTopIndex(int* arr, int arrSize) {
    int topVal = -1;
    int topIndex = -1;
    for (size_t i = 0; i < arrSize; i++) {
        int currentVal = arr[i];
        if (currentVal > topVal) {
            topVal = currentVal;
            topIndex = i;
        }
    }
    return topIndex;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = k;
    if (numsSize == 1) return nums; // Edge Case

    int* counter = (int*) malloc(sizeof(int) * NUMS_MAX_LENGTH);
    memset(counter, 0, sizeof(int) * NUMS_MAX_LENGTH);
    // Populate counter
    for (size_t i = 0; i < numsSize; i++) {
        int num = nums[i];
        counter[num + OFFSET]++;
    }

    // Populate topVals
    int* topVals = (int*) malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        int topNum = getTopIndex(counter, NUMS_MAX_LENGTH) - OFFSET;
        topVals[i] = topNum;
        counter[topNum + OFFSET] = 0; // Clear this num from the counter
    }

    return topVals;
}


int main() {
    int k = 2;
    int returnSize = k;
    int nums[6] = {1,1,1,2,2,3};
    int* returnArr = topKFrequent(nums, 6, k, &returnSize);
    displayArr(returnArr, returnSize);
}