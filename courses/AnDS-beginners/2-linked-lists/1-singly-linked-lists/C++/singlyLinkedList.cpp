

/* Notes:
    - Linked lists are made up of objects called 'ListNodes'
    - Each ListNode stores 2 items - the value of the node; and a pointer to the m.addr. of the next node
    - The pointer allows us to connect multiple nodes together - forming a linked list 

    - In most languages the next pointer is actually implemented as a reference to the next node
    -  This allows us to do things like `node1.next = node2;`

    - Unlike arrays, linked list are not neccessarily stored contiguously in memory
*/

#include <iostream>


class ListNode {
    public:
        int val;
        // Pointer to the next ListNode in the linked list
        ListNode* next = nullptr;

        ListNode(int initialVal) {
            val = initialVal;
        }
};

class SinglyLinkedList {
    public:
        // Allows us to access the head and tail of the linked list in O(1) time
        ListNode* head;
        ListNode* tail;

        SinglyLinkedList() {
            // Init list with dummy first node - makes removing first node easier
            head = new ListNode(-1);
            tail = head;
        }

        // O(1) since we have the tail pointer
        void insertEnd(int newVal) {
            // Make the current tail node point to a new node and then update the tail pointer to point to this new node
            tail->next = new ListNode(newVal);
            tail = tail->next;
        }


        void remove(int index) {
            int i = 0;
            ListNode* curr = head;
            // Increment through the list until curr is the node before the index'th node
            while (i < index && curr) {
                i++;
                curr = curr->next;
            }

            // If curr and the next node exist
            if (curr && curr->next) {
                // If the index'th node is the tail, set the tail to curr
                if (curr->next == tail) {
                    tail = curr;
                }
                // Point curr.next to the index'th node's next - now the list simply skips over the index'th node
                curr->next = curr->next->next;
            }
        }

        void display() {
            ListNode* curr = head;
            while (curr) {
                std::cout << curr->val << " -> ";
                curr = curr->next;
            }
            std::cout << std::endl;
        }
};



// Generally, a linked list has access time of O(n) but insertion and removal time of O(1) - opposite to arrays
// Therefore, it is generally better to use linked list when needing a write-heavy data structure, and arrays for a read-heavy data structure