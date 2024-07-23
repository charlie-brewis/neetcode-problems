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

#include <iostream>

struct MyLinkedListNode {
    int val;
    MyLinkedListNode* next;
    MyLinkedListNode* prev;

    MyLinkedListNode(int initVal = 0, MyLinkedListNode* initNext = nullptr, MyLinkedListNode* initPrev = nullptr) {
        val = initVal;
        next = initNext;
        prev = initPrev;
    }
};


class MyLinkedList {
private:
    MyLinkedListNode* head;
    MyLinkedListNode* tail;
    int size;

    MyLinkedListNode* getNodeAtIndex(const int index) const {
        if (index < 0 || !size ) return nullptr;

        int i = 0;
        MyLinkedListNode* currentNode = head;
        while (i++ != index && currentNode) {
            currentNode = currentNode->next;
        }
        return currentNode;
    }

public:
    MyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    int get(const int index) const {
        MyLinkedListNode* nodeAtIndex = getNodeAtIndex(index);
        return nodeAtIndex ? nodeAtIndex->val : -1;
    }
    
    void addAtHead(const int val) {
        MyLinkedListNode* newNode = new MyLinkedListNode(val);
        if (!size++) {
            head = newNode;
            tail = head;
            return;
        } 
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    
    void addAtTail(const int val) {
        MyLinkedListNode* newNode = new MyLinkedListNode(val);
        if (!size++) {
            head = newNode;
            tail = head;
            return;
        } 
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    void addAtIndex(const int index, const int val) {
        if (index < 0 || index > size) return;
        // Note returning function calls as these are void vunctions - null
        if (index == 0) return addAtHead(val);
        if (index == size) return addAtTail(val);
        MyLinkedListNode* nodeAtIndex = getNodeAtIndex(index);
        nodeAtIndex->prev = new MyLinkedListNode(val, nodeAtIndex, nodeAtIndex->prev);
        nodeAtIndex->prev->prev->next = nodeAtIndex->prev;
        ++size;
    }
    
    void deleteAtIndex(const int index) {
        MyLinkedListNode* nodeAtIndex = getNodeAtIndex(index);
        if (!nodeAtIndex) return;

        // If the selected node is not the head, update the next pointer of the previous node
        if (nodeAtIndex != head) nodeAtIndex->prev->next = nodeAtIndex->next;
        else head = nodeAtIndex->next;

        // If the selected node is not the tail, update the prev pointer of the next node
        if (nodeAtIndex != tail) nodeAtIndex->next->prev = nodeAtIndex->prev;
        else tail = nodeAtIndex->prev;

        delete nodeAtIndex;
        --size;
    }


    void display() const {
        if (!head) std::cout << "null";
        MyLinkedListNode* currentNode = head;
        while (currentNode) {
            std::cout << currentNode->val << " -> ";
            currentNode = currentNode->next;
        }
        std::cout << "\n";
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */


int main() {
    MyLinkedList* myLinkedList = new MyLinkedList();
    myLinkedList->display();
    
    myLinkedList->addAtHead(1);
    myLinkedList->display();

    myLinkedList->addAtTail(3);
    myLinkedList->display();

    myLinkedList->addAtIndex(1, 2);
    myLinkedList->display();

    std::cout << myLinkedList->get(1) << "\n";

    myLinkedList->deleteAtIndex(1);
    myLinkedList->display();

    std:: cout << myLinkedList->get(1) << "\n";
}
