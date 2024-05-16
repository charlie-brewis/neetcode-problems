/*
https://leetcode.com/problems/remove-duplicates-from-sorted-array/

Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
Return k.


Example 1:
    Input: nums = [1,1,2]
    Output: 2, nums = [1,2,_]
    Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
    It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
    Input: nums = [0,0,1,1,1,2,2,3,3,4]
    Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
    Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
    It does not matter what you leave beyond the returned k (hence they are underscores).
 

Constraints:
    1 <= nums.length <= 3 * 104
    -100 <= nums[i] <= 100
    nums is sorted in non-decreasing order.
*/
#include <stdio.h>


//* This algorithm has a time complexity of O(n)

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) {return 0;}

    // The first value will always be unique, therefore initialise to 1
    int k = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[k - 1]) {
            // If we encounter a new unique value, override the value next to the previous unique value with said new value
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}



int main() {
    int numsSize = 10;
    int nums[10] = {0,0,1,1,1,2,2,3,3,4};
    printf("%d", removeDuplicates(nums, numsSize));
    return 0;
}
