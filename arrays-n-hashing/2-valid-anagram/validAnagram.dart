/*
242. Valid Anagram - https://leetcode.com/problems/valid-anagram/
Easy


Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, 
typically using all the original letters exactly once.


Constraints:
    - 1 <= s.length, t.length <= 5 * 104
    - s and t consist of lowercase English letters.
*/

bool isAnagram(String s, String t) {
  if (t.length != s.length) {
    return false;
  }
  if (t == s) {
    return true;
  }

  Set<String?> anagramLetters = Set();
  for (int i = 0; i < t.length; i++) {
    String currChar = t[i];
    if (!anagramLetters.contains(currChar)) {
      if (t.split(currChar).length != s.split(currChar).length) {
        return false;
      }
      anagramLetters.add(currChar);
    }
  }
  return true;
}
