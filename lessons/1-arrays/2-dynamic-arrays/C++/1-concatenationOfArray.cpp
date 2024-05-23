/*
https://leetcode.com/problems/concatenation-of-array/description/

Given an integer array nums of length n, you want to create an array ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).
Specifically, ans is the concatenation of two nums arrays.
Return the array ans.

 
Example 1:
    Input: nums = [1,2,1]
    Output: [1,2,1,1,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
    - ans = [1,2,1,1,2,1]
Example 2:
    Input: nums = [1,3,2,1]
    Output: [1,3,2,1,1,3,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
    - ans = [1,3,2,1,1,3,2,1]
 

Constraints:
    n == nums.length
    1 <= n <= 1000
    1 <= nums[i] <= 1000

*/
#include <vector>

// Intuitive solution iterates and pushes twice -> O(2n) = O(n)
std::vector<int> getConcatenation(std::vector<int>& nums) {
    std::vector<int> ans;
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < nums.size(); i++) {
            ans.push_back(nums[i]);
        }
    }
    return ans;
}

// Best approach instatiates ans with a size of 2n and uses indexing to override the null values -> O(n)
std::vector<int> getConcatenation2(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> ans(2 * n);
    for (int i = 0; i < n; i++) {
        ans[i] = nums[i];
        ans[i + n] = nums[i];
    }
}