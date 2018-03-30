#include "Node.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <class T>
class BinarySearchTree {
    
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        void insert(T element);
        void print();
        bool remove(T key);

    private:
        Node<T>* root;
        void rcDelete(Node<T>* node);
        Node<T>* rcInsert(Node<T>* node, T element);
        void rcPrint(Node<T>* node, string tabstop, bool branch);
        Node<T>* rcSearch(Node<T>* node, T key);
        void replaceNode(Node<T>* toReplace, Node<T>* newNode);
};

#endif

template <class T>
BinarySearchTree<T>::BinarySearchTree() { 
    root = NULL;
}

// destructor implements recursive node deletion
template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
    if (root) rcDelete(root);
}

template <class T>
void BinarySearchTree<T>::insert(T element) {
    root = rcInsert(root, element);
}

template <class T>
void BinarySearchTree<T>::print() {
    if (!root) cout << "Tree is empty." << endl;
    else rcPrint(root, "", false);
}

// calls delete on subtree with root node "node"
template<class T>
void BinarySearchTree<T>::rcDelete(Node<T>* node) {
    if (node->getLeft()) rcDelete(node->getLeft());
    if (node->getRight()) rcDelete(node->getRight());
    delete node;
}

template <class T> // node by reference because may need to set root
Node<T>* BinarySearchTree<T>::rcInsert(Node<T>* node, T element) {
    if (!node) node = new Node<T>(element);
    else if (element <= node->getValue()) { // assume overloaded <= operator
        node->setLeft(rcInsert(node->getLeft(), element));
        node->getLeft()->setParent(node);
    } else {
        node->setRight(rcInsert(node->getRight(), element));
        node->getRight()->setParent(node);
    } return node;
}

template <class T>
void BinarySearchTree<T>::rcPrint(Node<T>* node, string tabstop, bool branch) {
    if (!node) { // when printing out only left node
        cout << tabstop << "|   " << endl;
        return;
    } else cout << tabstop << (branch ? "├── " : "└── ") << node->getValue() << endl;
    if (!node->getLeft() && node->getRight()) rcPrint(node->getRight(), tabstop + (branch ? "|   " : "    "), false);
    else if (node->getLeft()) {
        rcPrint(node->getRight(), tabstop + (branch ? "|   " : "    "), true);
        rcPrint(node->getLeft(), tabstop + (branch ? "|   " : "    "), false);
    }
}

// search starting at root of subtree "node"
template <class T> // assume overloading of == and <
Node<T>* BinarySearchTree<T>::rcSearch(Node<T>* node, T key) {
    if (!node || key == node->getValue()) return node;
    else if (key < node->getValue()) return rcSearch(node->getLeft(), key);
    else return rcSearch(node->getRight(), key);
}

template <class T>
bool BinarySearchTree<T>::remove(T key) {
    Node<T>* toDelete = rcSearch(root, key);
    if (!toDelete) return false;
    if (toDelete->getLeft() && toDelete->getRight()) { // two children, find successor in right subtree
        // copy fields of successor into toDelete then delete successor with one or no child methods
        Node<T>* successor = toDelete->getRight();
        while (successor->getLeft()) successor = successor->getLeft(); // move to leftmost of subtree
        toDelete->setValue(successor->getValue()); // copy value of successor over
        toDelete = successor; // set successor to be deleted after values are copied
    } if (!toDelete->getLeft() && !toDelete->getRight()) replaceNode(toDelete, NULL); // no children to replace
    else if (toDelete->getLeft()) replaceNode(toDelete, toDelete->getLeft()); // replace with left child
    else if (toDelete->getRight()) replaceNode(toDelete, toDelete->getRight()); // replace with right child
    return true;
}

template <class T> // attach subtree of newNode in place of toReplace
void BinarySearchTree<T>::replaceNode(Node<T>* toReplace, Node<T>* newNode) {
    if (!toReplace->getParent()) root = newNode; // if no parent, replace the root with newNode
    else if (toReplace == toReplace->getParent()->getLeft()) toReplace->getParent()->setLeft(newNode); // if left child of parent, replace left child of parent with newNode
    else toReplace->getParent()->setRight(newNode); // if right child of parent, replace right child of parent with newNode
    if (newNode) newNode->setParent(toReplace->getParent()); // newNode's parent is now parent of replaced node
}
