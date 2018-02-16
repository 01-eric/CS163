#include "Node.h"
#include "Stack.h"
#include <cstddef>

Stack::~Stack() {
    while (peek()) delete pop(); // while not empty clear first element
}

void Stack::push(char* element) {
    Node* newElement = new Node(element);
    newElement->setRight(top); // no need to doubly link for stack
    top = newElement; // adjust top pointer
}

char* Stack::pop() {
    Node* popped = top; // popped element
    top = popped->getRight(); // set top to next element
    return popped->getValue(); // return char* in popped node
    // no need to delete popped node because the char* is returned
    // calling function must delete the char*
}

char* Stack::peek() {
    if (top) return top->getValue();
    else return NULL;
}
