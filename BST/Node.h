#include <cstddef>

#ifndef NODE_H
#define NODE_H

template <class T>
class Node {

    public:
        Node(T value);
        ~Node();
        // setters
        void setValue(T value);
        void setLeft(Node* left);
        void setRight(Node* right);
        void setParent(Node* parent);
        // getters
        T getValue();
        Node<T>* getLeft();
        Node<T>* getRight();
        Node<T>* getParent();

    private:
        T value;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;

};

#endif

template <class T>
Node<T>::Node(T value) {
    left = right = NULL;
    this->value = value;
}

template <class T>
Node<T>::~Node() {
    // if T is pointer?? how do I check?? delete value;
}

template <class T>
void Node<T>::setValue(T value) {
    this->value = value;
}

template <class T>
void Node<T>::setLeft(Node<T>* left) {
    this->left = left;
}

template <class T>
void Node<T>::setRight(Node<T>* right) {
    this->right = right;
}

template <class T>
void Node<T>::setParent(Node<T>* parent) {
    this->parent = parent;
}

template <class T>
T Node<T>::getValue() {
    return value;
}

template <class T>
Node<T>* Node<T>::getLeft() {
    return left;
}

template <class T>
Node<T>* Node<T>::getRight() {
    return right;
}

template <class T>
Node<T>* Node<T>::getParent() {
    return parent;
}
