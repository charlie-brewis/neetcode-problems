/*
https://leetcode.com/problems/reverse-linked-list/description/


Given the head of a singly linked list, reverse the list, and return the reversed list.

 
Example 1:
    Input: head = [1,2,3,4,5]
    Output: [5,4,3,2,1]

Example 2:
    Input: head = [1,2]
    Output: [2,1]

Example 3:
    Input: head = []
    Output: []


Constraints:
    - The number of nodes in the list is the range [0, 5000].
    - -5000 <= Node.val <= 5000
 

Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
*/



typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;


/*
Time Complexity:  O(n)
Space Complexity: O(1)
*/
ListNode* reverseListIterative(ListNode* head) {
    ListNode* currentNode = head;
    ListNode* prevNode = NULL;
    ListNode* nextNode;
    while (currentNode) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    return prevNode;
}


/*
Time Complexity:  O(n)
Space Complexity: O(n)
*/
ListNode* reverseListRecursive(ListNode *head) {
    // We have reached the last node, our result, therefore return it
    if (head == NULL || head->next == NULL) return head;
    ListNode* result = reverseListRecursive(head->next);
    // Point the next node to head (current node)
    head->next->next = head;
    // Remove the head's next pointer
    head->next = NULL;
    // Keep returning the same result (old last node)
    return result;
}