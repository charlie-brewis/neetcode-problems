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

#include <stdlib.h>
#include <stdio.h>



typedef struct ListNode {
    int val;
    // Pointer to the next ListNode in the linked list
    struct ListNode* next;
} ListNode;

ListNode* instantiateNode(int newVal) {
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->val = newVal;
    newNode->next = NULL;
    return newNode;
}

void freeListNode(ListNode* node) {
    free(node);
} 



typedef struct SinglyLinkedList {
    // Allows us to access the head and tail of the linked list in O(1) time
    ListNode* head;
    ListNode* tail;
} SinglyLinkedList;

SinglyLinkedList* instantiateSinglyLinkedList() {
    SinglyLinkedList* newList = (SinglyLinkedList*) malloc(sizeof(SinglyLinkedList));
    // Init list with dummy first node - makes removing first node easier
    newList->head = instantiateNode(-1);
    // Since the intial length is 1, the head and the tail are the same node
    newList->tail = newList->head;
    return newList;
}

// Frees memory of linked list and all remaining nodes
void freeSinglyLinkedList(SinglyLinkedList* linkedList) {
    ListNode* currentNode = linkedList->head;
    while (currentNode) { 
        ListNode* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
}

// Helper method traverses through the list to the index and returns a pointer to the node at said index
static ListNode* accessNodeAt(const SinglyLinkedList* linkedList, const int index) {
    int i = 0;
    ListNode* currentNode = linkedList->head;
    // index + 1 because of dummy first node
    while (i++ != index + 1 && currentNode) { currentNode = currentNode->next; }
    return currentNode;
}

// O(1) since we have the tail pointer
int accessLast(const SinglyLinkedList* linkedList) {
    // If the list is empty, return error code
    if (linkedList->head == linkedList->tail) { return -1; }
    return linkedList->tail->val;
}

// O(n) since we don't have indexing
int accessAt(const SinglyLinkedList* linkedList, const int index) { return accessNodeAt(linkedList, index)->val; }


// Always O(n) because we have to traverse to the end of the list
void removeLast(SinglyLinkedList* linkedList) {
    // If the list is empty, do nothing
    if (linkedList->head == linkedList->tail) { return; }

    // Traverse through list to the node before the tail
    ListNode* currentNode = linkedList->head;
    while (currentNode->next != linkedList->tail) { currentNode = currentNode->next; }

    // Set the tail to the node before it
    linkedList->tail = currentNode;
    // Free the memory of the old tail node
    freeListNode(currentNode->next);
    // Set the next pointer of the new tail node to null
    currentNode->next = NULL;
}

// O(n) because we have to access at a specified index
void removeAt(SinglyLinkedList* linkedList, const int index) {
    if (linkedList->head == linkedList->tail) { return; }

    // Get node before the specified index
    ListNode* currentNode = accessNodeAt(linkedList, index - 1);

    // If currentNode and the next node exist
    if (currentNode && currentNode->next) {
        // If the index'th node is the tail, set the tail to curr
        if (currentNode->next == linkedList->tail) {
            linkedList->tail = currentNode;
        }
        // Point curr.next to the index'th node's next - now the list simply skips over the index'th node
        // Note, also freeing the memory of the old next node to avoid memory leaks
        ListNode* newNext = currentNode->next->next;
        freeListNode(currentNode->next);
        currentNode->next = newNext;
    }
}

// O(1) since we have the tail pointer
void insertEnd(SinglyLinkedList* linkedList, const int newVal) {
    // Make the current tail node point to a new node and then update the tail pointer to point to this new node
    linkedList->tail->next = instantiateNode(newVal);
    linkedList->tail = linkedList->tail->next;
}

// O(n) since we have to access at an index
void insertAt(SinglyLinkedList* linkedList, const int index, const int newVal) {
    ListNode* prevNode = accessNodeAt(linkedList, index - 1);
    // Return if the previous node doesn't exist - i.e., the index was out of bounds due to dummy
    if (!prevNode) { return; }

    ListNode* oldPrevNodeNext = prevNode->next;
    prevNode->next = instantiateNode(newVal);
    prevNode->next->next = oldPrevNodeNext;
}


void display(const SinglyLinkedList* linkedList) {
    ListNode* currentNode = linkedList->head->next;
    while (currentNode) {
        printf("%d -> ", currentNode->val);
        currentNode = currentNode->next;
    }
    printf("\n");
}




int main() {
    SinglyLinkedList* myLinkedList = instantiateSinglyLinkedList();
    insertEnd(myLinkedList, 1);
    insertEnd(myLinkedList, 2);
    insertEnd(myLinkedList, 3);
    insertEnd(myLinkedList, 4);
    insertEnd(myLinkedList, 5);
    display(myLinkedList);
    removeAt(myLinkedList, 2);
    display(myLinkedList);
    printf("%d\n", accessAt(myLinkedList, 2));
    removeLast(myLinkedList);
    display(myLinkedList);
    insertAt(myLinkedList, 2, 3);
    display(myLinkedList);
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