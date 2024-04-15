'''
217. Contains Duplicate - https://leetcode.com/problems/contains-duplicate/
Easy

Given an integer array nums, return true if any value appears at least twice in the array, 
and return false if every element is distinct.

Constraints:
    - 1 <= nums.length <= 105
    - -109 <= nums[i] <= 109
'''

def containsDuplicate1(nums: list[int]) -> bool:
    '''
    Intuitive approach uses a second array with no duplicates and compares.
    Time frequency O(n) - not very efficient
    '''
    distinct_array = []
    for num in nums:
        if num not in distinct_array:
            distinct_array.append(num)
    return not (distinct_array == nums)


def containsDuplicate2(nums: list[int]) -> bool:
    '''
    Sorting Method

    This approach first sorts the array to make duplicates adjacent.
    Then it checks each adjacent pair.

    Time complexity: O(n log n)
    '''
    nums.sort()
    for i in range(1, len(nums)):
        if nums[i] == nums[i - 1]:
            return True 
        return False
    
def containsDuplicate3(nums: list[int]) -> bool:
    '''
    Hash Set Method

    This is essentially the same method as my intuitive method,
    however is more efficient as it uses a hash set and can quit on finding the first duplicate.

    Time complexity: O(n)
    '''
    seen = set()
    for num in nums:
        if num in seen:
            return True 
        seen.add(num)
    return False


def containsDuplicate4(nums: list[int]) -> bool:
    '''
    This approach takes the set idea further by simply comparing the length of the sets.
    Has the same average time complexity as the one before but a longer best.
    '''
    return len(set(nums)) != len(nums)
