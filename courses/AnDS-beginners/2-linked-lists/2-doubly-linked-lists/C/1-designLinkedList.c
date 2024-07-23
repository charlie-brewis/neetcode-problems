/*
https://leetcode.com/problems/design-linked-list/description/

Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement the MyLinkedList class:
    - MyLinkedList() Initializes the MyLinkedList object.
    - int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
    - void addAtHead(int val) Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
    - void addAtTail(int val) Append a node of value val as the last element of the linked list.
    - void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
    - void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.
    

Example 1:
    Input
    ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
    [[], [1], [3], [1, 2], [1], [1], [1]]
    Output
    [null, null, null, null, 2, null, 3]

Explanation
    MyLinkedList myLinkedList = new MyLinkedList();
    myLinkedList.addAtHead(1);
    myLinkedList.addAtTail(3);
    myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
    myLinkedList.get(1);              // return 2
    myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
    myLinkedList.get(1);              // return 3
 

Constraints:
    - 0 <= index, val <= 1000
    - Please do not use the built-in LinkedList library.
    - At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and deleteAtIndex.
*/


#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    int val;
    struct Node* next;
    struct Node* prev;
} Node;

Node* instantiateNode (int val, Node* next, Node* prev) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = next;
    newNode->prev = prev;
    return newNode;
}

void freeNode(Node* node) { free(node); }



typedef struct MyLinkedList {
    Node* head;
    Node* tail;
    int size;
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* newList = (MyLinkedList*) malloc(sizeof(MyLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

Node* myLinkedlistGetNode(const MyLinkedList* obj, const int index) {
    if (index < 0 || !obj->size) return NULL;
    int i = 0;
    Node* currentNode = obj->head;
    while (i++ != index && currentNode) currentNode = currentNode->next;
    return currentNode;
}

int myLinkedListGet(const MyLinkedList* obj, const int index) {
    Node* nodeAtIndex = myLinkedlistGetNode(obj, index);
    return nodeAtIndex ? nodeAtIndex->val : -1;
}

void myLinkedListAddAtHead(MyLinkedList* obj, const int val) {
    Node* newNode = instantiateNode(val, NULL, NULL);
    if (!obj->size++) {
        obj->head = newNode;
        obj->tail = obj->head;
        return;
    }
    newNode->next = obj->head;
    obj->head->prev = newNode;
    obj->head = newNode;
}

void myLinkedListAddAtTail(MyLinkedList* obj, const int val) {
    Node* newNode = instantiateNode(val, NULL, NULL);
    if (!obj->size++) {
        obj->head = newNode;
        obj->tail = obj->head;
        return;
    }
    newNode->prev = obj->tail;
    obj->tail->next = newNode;
    obj->tail = newNode;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, const int index, const int val) {
    if (index < 0 || index > obj->size) return;
    if (index == 0) return myLinkedListAddAtHead(obj, val);
    if (index == obj->size) return myLinkedListAddAtTail(obj, val);

    Node* nodeAtIndex = myLinkedlistGetNode(obj, index);
    nodeAtIndex->prev = instantiateNode(val, nodeAtIndex, nodeAtIndex->prev);
    nodeAtIndex->prev->prev->next = nodeAtIndex->prev;
    ++obj->size;
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, const int index) {
    Node* nodeAtIndex = myLinkedlistGetNode(obj, index);
    if (!nodeAtIndex) return;

    // If the selected node is not the head, update the next pointer of the previous node
    if (nodeAtIndex != obj->head) nodeAtIndex->prev->next = nodeAtIndex->next;
    else obj->head = nodeAtIndex->next;

    // If the selected node is not the tail, update the prev pointer of the next node
    if (nodeAtIndex != obj->tail) nodeAtIndex->next->prev = nodeAtIndex->prev;
    else obj->tail = nodeAtIndex->prev;

    free(nodeAtIndex);
    --obj->size;
}

void myLinkedListFree(MyLinkedList* obj) {
    Node* currentNode = obj->head;
    Node* nextNode;
    while (currentNode) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(obj);
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/