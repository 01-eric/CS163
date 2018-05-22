#include <cstddef>

#ifndef NODE_H
#define NODE_H

template <class T>
class Node {

    public:
        Node(T value, bool red);
        Node() : Node(NULL, false) {};
        ~Node();
        // setters
        void setValue(T value);
        void setLeft(Node* left);
        void setRight(Node* right);
        void setParent(Node* parent);
        void setRed(bool red);
        // getters
        T getValue();
        Node<T>* getLeft();
        Node<T>* getRight();
        Node<T>* getParent();
        Node<T>* getGrandparent();
        Node<T>* getSibling();
        Node<T>* getUncle();
        bool isRed();
        bool isLeaf();

    private:
        T value;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
        bool red;

};

#endif

template <class T>
Node<T>::Node(T value, bool red) {
    left = right = parent = NULL;
    this->value = value;
    this->red = red;
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
void Node<T>::setRed(bool red) {
    this->red = red;
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

template <class T>
Node<T>* Node<T>::getGrandparent() {
    if (!getParent()) return NULL; // if no parent no grandparent
    else return getParent()->getParent(); // if no grandparent but has parent still returns null
}

template <class T>
Node<T>* Node<T>::getSibling() { // returns null if no parent or no sibling
    if (!getParent()) return NULL;
    else if (this == getParent()->getLeft()) return getParent()->getRight();
    else return getParent()->getLeft();
}

// returns null if no grandparent. if grandparent exists uncle must exist because tree is balanced
template <class T>
Node<T>* Node<T>::getUncle() {
    if (!getGrandparent()) return NULL;
    else return getParent()->getSibling();
}

template <class T>
bool Node<T>::isRed() {
    return red;
}

template <class T>
bool Node<T>::isLeaf() {
    return !getLeft() && !getRight();
}
