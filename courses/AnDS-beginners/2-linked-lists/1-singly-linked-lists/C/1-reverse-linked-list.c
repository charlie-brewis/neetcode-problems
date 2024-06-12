/*
https://leetcode.com/problems/reverse-linked-list/description/

Given the beginning of a singly linked list head, reverse the list, and return the new beginning of the list.

Example 1:
    Input: head = [0,1,2,3]
    Output: [3,2,1,0]

Example 2:
    Input: head = []
    Output: []

Constraints:
    0 <= The length of the list <= 1000.
    -1000 <= Node.val <= 1000
*/


typedef struct ListNode {
    int val;
    ListNode *next;
} ListNode;

ListNode* reverseList(ListNode* head) {
    
}