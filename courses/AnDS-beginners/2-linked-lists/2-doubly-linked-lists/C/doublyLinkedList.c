/*
Much like singly linked lists, a doubly linked list is comprised of multiple ListNode objects.
Again, each ListNode object has a value and a pointer to the next node.
However, where doubly linked lists differ is that they also have a pointer to the previous node.
This allows for bidirectional traversal of the list, as well as simplifying the deletion logic.

Where we decide to use a singly or doubly linked list will depend on the specific use case, and we 
should consider how our linked list will be applied in our program.

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
    struct ListNode* next;
    // Doubly linked lists also store a pointer to the previous node
    struct ListNode* prev;
} ListNode;

ListNode* instantiateNode(int newVal) {
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->val = newVal;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void freeNode(ListNode* node) {
    free(node);
}



typedef struct DoublyLinkedList {
    ListNode* head;
    ListNode* tail;
} DoublyLinkedList;

DoublyLinkedList* instantiateDoublyLinkedList() {
    DoublyLinkedList* newList = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
    newList->head = instantiateNode(-1);
    newList->tail = newList->head;
    return newList;
}

void freeDoublyLinkedList(DoublyLinkedList* linkedList) {
    ListNode* currentNode = linkedList->head;
    ListNode* nextNode;
    while (currentNode) {
        nextNode = currentNode->next;
        freeNode(currentNode);
        currentNode = nextNode;
    }
}

static ListNode* accessNodeAt(const DoublyLinkedList* linkedList, const int index) {
    int i = 0;
    ListNode* currentNode = linkedList->head;
    while (i++ != index + 1 && currentNode) { currentNode = currentNode->next; }
    return currentNode;
}


int accessLast(const DoublyLinkedList* linkedList) { return linkedList->tail->val; }

int accessAt(const DoublyLinkedList* linkedList, const int index) { return accessNodeAt(linkedList, index)->val; }

void removeLast(DoublyLinkedList* linkedList) {
    if (linkedList->head == linkedList->tail) return;
    /*
    1. move tail to tail.prev
    2. free tail.next
    3. Set tail.next to null
    */
    linkedList->tail = linkedList->tail->prev;
    freeNode(linkedList->tail->next);
    linkedList->tail->next = NULL;
}

void removeAt(DoublyLinkedList* linkedList, const int index) {
    if (linkedList->head == linkedList->tail) return;
    ListNode* nodeToRemove = accessNodeAt(linkedList, index);
    // Check node and previous exist
    if (nodeToRemove && nodeToRemove->prev) {
        // If the node to remove is the tail, update the tail
        if (nodeToRemove == linkedList->tail) {
            linkedList->tail = nodeToRemove->prev;
        }
        nodeToRemove->next->prev = nodeToRemove->prev;
        nodeToRemove->prev->next = nodeToRemove->next;
        freeNode(nodeToRemove);
    }
}

void insertLast(DoublyLinkedList* linkedList, const int newValue) {
    linkedList->tail->next = instantiateNode(newValue);
    linkedList->tail->next->prev = linkedList->tail;
    linkedList->tail = linkedList->tail->next;
}

void insertAt(DoublyLinkedList* linkedList, const int index, const int newValue) {
    ListNode* prevNode = accessNodeAt(linkedList, index - 1);
    if (!prevNode) return;
    ListNode* oldPrevNodeNext = prevNode->next;
    prevNode->next = instantiateNode(newValue);
    prevNode->next->prev = prevNode;
    prevNode->next->next = oldPrevNodeNext;
}

void display(const DoublyLinkedList* linkedList) {
    ListNode* currentNode = linkedList->head->next;
    while (currentNode) {
        printf("%d -> ", currentNode->val);
        currentNode = currentNode->next;
    }
    printf("\n");
}


int main() {
    DoublyLinkedList* myLinkedList = instantiateDoublyLinkedList();
    insertLast(myLinkedList, 1);
    insertLast(myLinkedList, 2);
    insertLast(myLinkedList, 3);
    insertLast(myLinkedList, 4);
    insertLast(myLinkedList, 5);
    display(myLinkedList);
    removeAt(myLinkedList, 2);
    display(myLinkedList);
    printf("%d\n", accessAt(myLinkedList, 2));
    removeLast(myLinkedList);
    display(myLinkedList);
    insertAt(myLinkedList, 2, 3);
    display(myLinkedList);
}