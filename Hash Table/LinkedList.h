#include "Node.h"
#include <iostream>
#include <cstddef>
using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class LinkedList {

    public:
        ~LinkedList();
        void add(T value);
        void add(int index, T value);
        T get(int index);
        T getFirst();
        T getLast();
        int getSize();
        void print();
        void remove();
        void remove(int index);

    private:
        Node<T>* head;
        Node<T>* tail;
        int size = 0;

};

#endif

template <class T>
LinkedList<T>::~LinkedList() {
    while (size > 0) remove(); // remove deallocates everything
}

template <class T>
void LinkedList<T>::add(T value) { // append onto tail
    if (!head) { // if list is empty
        head = new Node<T>(value); // inserted node is now head
        tail = head; // inserted node is now also tail
    } else {
        tail->setNext(new Node<T>(value)); // insert new node at the end
        tail->getNext()->setPrevious(tail); // doubly link
        tail = tail->getNext(); // move tail to new node
    } size++;
}

template <class T>
void LinkedList<T>::add(int index, T value) {
    if (index < size) { // if index is in range
        Node<T>* node = head;
        Node<T>* newNode = new Node<T>(value);
        for (int i = index; i > 0; i--) node = node->getNext(); // move node pointer until reached index
        newNode->setNext(node); // node at current index is moved forward to make room for new node
        newNode->setPrevious(node->getPrevious()); // new node takes current node's previous node as its previous
        node->setPrevious(newNode); // doubly link with newNode's next node
        if (newNode->getPrevious()) newNode->getPrevious()->setNext(newNode); // doubly link with previous node
        else head = newNode; // otherwise the new node took the position of head
        size++;
    } else add(value); // if out of range, just append to end
}

template <class T>
T LinkedList<T>::get(int index) {
    Node<T>* node = head; // start at head
    for (int i = index; i > 0; i--) node = node->getNext();
    return node->getValue();
}

template <class T>
T LinkedList<T>::getFirst() {
    return head->getValue();
}

template <class T>
T LinkedList<T>::getLast() {
    return tail->getValue();
}

template <class T>
int LinkedList<T>::getSize() {
    return size;
}

template <class T>
void LinkedList<T>::print() {
    if (size > 0) {
        cout << "Head: " << head->getValue() << " Tail: " << tail->getValue() << " Size: " << getSize() << ' ';
        for (Node<T>* node = head; node; node = node->getNext()) cout << (node == head ? '[' : ' ') << node->getValue() << (node == tail ? ']' : ',');
    } else cout << "Size: " << getSize() << ' ' << "[]";
    cout << endl;
}

template <class T>
void LinkedList<T>::remove() { // removes last element (cannot call on empty list)
    if (!tail->getPrevious()) {
        delete tail;
        head = tail = NULL;
    } else {
        tail = tail->getPrevious();
        delete tail->getNext();
        tail->setNext(NULL);
    } size--;
}

template <class T>
void LinkedList<T>::remove(int index) {
    if (index < size - 1) {
        Node<T>* node = head;
        for (int i = index; i > 0; i--) node = node->getNext();
        node->getNext()->setPrevious(node->getPrevious()); // link next node to previous node
        if (node->getPrevious()) node->getPrevious()->setNext(node->getNext()); // link previous node to next node
        else head = node->getNext(); // otherwise we deleted head so we move it forward
        delete node;
        size--;
    } else remove(); // if not in range just remove tail
}
