#include <cstddef>

#ifndef NODE_H
#define NODE_H

template <class T>
class Node {

    public:
        Node(T value);
        void setValue(T value);
        void setNext(Node* next);
        void setPrevious(Node* previous);
        T getValue();
        Node<T>* getNext();
        Node<T>* getPrevious();

    private:
        T value;
        Node<T>* next;
        Node<T>* previous;

};

#endif

template <class T>
Node<T>::Node(T value) {
    next = previous = NULL;
    setValue(value);
}

template <class T>
void Node<T>::setValue(T value) {
    this->value = value;
}

template <class T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}

template <class T>
void Node<T>::setPrevious(Node<T>* previous) {
    this->previous = previous;
}

template <class T>
T Node<T>::getValue() {
    return value;
}

template <class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <class T>
Node<T>* Node<T>::getPrevious() {
    return previous;
}
