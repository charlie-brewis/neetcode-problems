/*
Queues are First-In, First-Out (FIFO) data structures.
That is, items are removed from the queue exclusively in the order they were added.

Queues support 2 operations, enqueue, and dequeue - both O(1) time:
    Enqueue - placing an item at the end (tail) of a queue, similar to append or push
    Dequeue - removing an item at the start (head) of a queue

Dequeue is why we use a linked list instead of an array for queues, as removing from the head of a 
linked list is in O(1) time, but O(n) time for arrays.
*/


#include <iostream>

struct Node {
    int val;
    Node* next;
    Node(int val = -1, Node* next = nullptr) : val(val), next(next) {};
};


class Queue {
    private:
        Node* _head;
        Node* _tail;

    public:
        Queue() : _head(nullptr), _tail(nullptr) {};
        ~Queue() {
            Node* currentNode = _head;
            Node* nextNode;
            while (currentNode) {
                nextNode = currentNode->next;
                delete currentNode;
                currentNode = nextNode;
            }
        }

        void enqueue(int val) {
            Node* newNode = new Node(val);
            if (!_tail) {
                // If the queue is empty, set up queue
                _head = _tail = newNode;
                return;
            }
            // Append to tail
            _tail->next = newNode;
            _tail = _tail->next;
        }

        int dequeue() {
            // If queue is empty, return error code
            if (!_head) return -1;

            int val = _head->val;
            // Delete head node and update head pointer
            Node* newHead = _head->next;
            delete _head;
            _head = newHead;
            if (!_head) _tail = nullptr;

            return val;
        }

        void display() {
            Node* currentNode = _head;
            while (currentNode) {
                std::cout << currentNode->val << " -> ";
                currentNode = currentNode->next;
            }
            std::cout << "\n";
        }
};




int main() {
    Queue* myQueue = new Queue();
    myQueue->enqueue(1);
    myQueue->enqueue(2);
    myQueue->enqueue(3);
    myQueue->display();
    myQueue->dequeue();
    myQueue->display();
    myQueue->dequeue();
    myQueue->display();

    return 0;
}