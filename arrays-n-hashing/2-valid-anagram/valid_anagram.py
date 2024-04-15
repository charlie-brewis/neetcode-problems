'''
242. Valid Anagram - https://leetcode.com/problems/valid-anagram/
Easy


Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, 
typically using all the original letters exactly once.


Constraints:
    - 1 <= s.length, t.length <= 5 * 104
    - s and t consist of lowercase English letters.
'''

def isAnagram(s: str, t: str) -> bool:
    # Edge Cases
    if len(t) != len(s): return False
    if t == s: return True

    anagram_letters = set()
    for char in t:
        if char not in anagram_letters:
            if t.count(char) != s.count(char):
                return False 
            anagram_letters.add(char)
    return True