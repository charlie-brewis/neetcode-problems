/*
217. Contains Duplicate - https://leetcode.com/problems/contains-duplicate/
Easy

Given an integer array nums, return true if any value appears at least twice in the array, 
and return false if every element is distinct.

Constraints:

- 1 <= nums.length <= 105
- -109 <= nums[i] <= 109
*/

bool containsDuplicate(List<int> nums) {
  Set<int> seen = Set();
  for (int i = 0; i < nums.length; i++) {
    int currNum = nums[i];
    if (seen.contains(currNum)) {
      return true;
    } else {
      seen.add(currNum);
    }
  }
  return false;
}

void main() {
  print(containsDuplicate([1, 2, 3, 1]));
}
