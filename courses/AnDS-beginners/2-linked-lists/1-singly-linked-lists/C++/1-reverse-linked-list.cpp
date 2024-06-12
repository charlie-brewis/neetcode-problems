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

class ListNode {
    public:
        int val;
        // Pointer to the next ListNode in the linked list
        ListNode* next;

        ListNode(int initialVal = 0, ListNode* nextNode = nullptr) {
            val = initialVal;
            next = nextNode;
        }
};

class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            if (!head || !head->next) { return head; }
            ListNode* nextNode;
            ListNode* prevNode = nullptr;
            // Iterate through the linked list, swapping the next pointer to point to the previous node
            while (head) {
                // Store the next node to iterate to
                nextNode = head->next;
                // Reverse the direction of the next pointer
                head->next = prevNode;
                // Store the prevNode for the next iteration
                prevNode = head;
                // Iterate to the stored next node
                head = nextNode;
            }
            return prevNode;
        }
};