/*
Linked Lists are data structures comprised of smaller data structures called `List Nodes`
Each ListNode stores 2 items - the value stored in the node; and a pointer to the next node in the list
This pointer allows us to connect multiple nodes together - forming a linked list

In most languages, the next pointer is implemented as a reference to the next node
This allows us to simplify operations such as `node1.next = node2;`

Unlike arrays, linked lists are not neccessarily stored contiguously in memory (this is thanks to the next pointers)

The Linked List data structure simply stores pointers to the first and last ListNode objects in the list
These pointers are called the `head` and `tail` respectively.

Operations:
    -> accessLast - O(1)
    -> accessAt   - O(n)
    -> removeLast - O(n)
    -> removeAt   - O(n)
    -> insertLast - O(1)
    -> insertAt   - O(n)
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
    private:
        // Allows us to access the head and tail of the linked list in O(1) time
        ListNode* head;
        ListNode* tail;

        // Helper method traverses through the list to the index and returns a pointer to the node at said index
        ListNode* accessNodeAt(const int index) const {
            int i = 0;
            ListNode* currentNode = head;
            while (i++ <= index && currentNode) {
                currentNode = currentNode->next;
            }
            return currentNode;
        }

    public:
        SinglyLinkedList() {
            // Init list with dummy first node - makes removing first node easier
            head = new ListNode(-1);
            // Since the intial length is 1, the head and the tail are the same node
            tail = head;
        }

        ~SinglyLinkedList() {
            ListNode* currentNode = head;
            ListNode* nextNode;
            while (currentNode) {
                nextNode = currentNode->next;
                delete currentNode;
                currentNode = nextNode;
            }
        }

        // O(1) since we have the tail pointer
        int accessLast() const { 
            // If the list is empty, return error code
            if (head == tail) { return -1; }
            return tail->val; 
        }

        // O(n) since we don't have indexing
        int accessAt(const int index) const { return accessNodeAt(index)->val; }


        // Always O(n) because we have to traverse to the end of the list
        void removeLast() {
            // If the list is empty, do nothing
            if (head == tail) { return; }

            // Traverse through to the node before the tail
            ListNode* curr = head;
            while (curr->next != tail) { curr = curr->next; }

            // Set the tail to the node before it
            tail = curr;    
            // Free the memory of the old tail node
            delete curr->next;
            // Set the next pointer of the new tail node to null
            curr->next = nullptr;
        }

        // O(n) because we have to access at a specified index
        void removeAt(const int index) {
            if (head == tail) { return; }

            // Get node before the specified index
            ListNode* curr = accessNodeAt(index - 1);

            // If curr and the next node exist
            if (curr && curr->next) {
                // If the index'th node is the tail, set the tail to curr
                if (curr->next == tail) {
                    tail = curr;
                }
                // Point curr.next to the index'th node's next - now the list simply skips over the index'th node
                // Note, also freeing the memory of the old next node to avoid memory leaks
                ListNode* newNext = curr->next->next;
                delete curr->next;
                curr->next = newNext;
            }
        }


        // O(1) since we have the tail pointer
        void insertEnd(const int newVal) {
            // Make the current tail node point to a new node and then update the tail pointer to point to this new node
            tail->next = new ListNode(newVal);
            tail = tail->next;
        }

        // O(n) since we have to access at an index
        void insertAt(const int index, const int newVal) {
            ListNode* prevNode = accessNodeAt(index - 1);
            // Return if the previous node doesn't exist - i.e., the index was out of bounds
            if (!prevNode) { return; }

            ListNode* oldPrevNodeNext = prevNode->next;
            prevNode->next = new ListNode(newVal);
            prevNode->next->next = oldPrevNodeNext;
        }


        void display() {
            ListNode* curr = head->next;
            while (curr) {
                std::cout << curr->val << " -> ";
                curr = curr->next;
            }
            std::cout << std::endl;
        }
};


int main() {
    SinglyLinkedList mySinglyLinkedList = SinglyLinkedList();
    mySinglyLinkedList.insertEnd(1);
    mySinglyLinkedList.insertEnd(2);
    mySinglyLinkedList.insertEnd(3);
    mySinglyLinkedList.insertEnd(4);
    mySinglyLinkedList.insertEnd(5);
    mySinglyLinkedList.display();
    mySinglyLinkedList.removeAt(2);
    mySinglyLinkedList.display();
    printf("%d\n", mySinglyLinkedList.accessAt(2));
    mySinglyLinkedList.removeLast();
    mySinglyLinkedList.display();
    mySinglyLinkedList.insertAt(2, 3);
    mySinglyLinkedList.display();
}

/*
Conclusion - Singly Linked Lists

Operation |Big-O Time |Notes
----------+-----------+-----
Reading   |O(n)       |O(1) at end
Insertion |O(n)       |O(1) at end
Deletion  |O(n)       |

Generally, a linked list has access time of O(n) but much faster and simpler insertion and removal times than arrays
This is because the entire linked list doesn't have to be copied over if it needs to grow, like arrays do.
Therefore, it is generally better to use linked list when needing a write-heavy data structure, and arrays for a read-heavy data structure
*/
