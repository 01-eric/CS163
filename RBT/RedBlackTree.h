#include "Node.h"
#include <iostream>
#include <cstddef>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

template <class T>
class RedBlackTree {
    
    public:
        RedBlackTree();
        ~RedBlackTree();
        bool contains(T key);
        Node<T>* insert(T element);
        void print();
        bool remove(T key);

    private:
        char* concat(char* &destination, const char* source);
        Node<T>* root;
        void rcDelete(Node<T>* node);
        Node<T>* rcInsert(Node<T>* node, Node<T>* newNode);
        void rcPrint(Node<T>* node, char* tabstop, bool branch);
        Node<T>* rcSearch(Node<T>* node, T key);
        void repairTreeInsert(Node<T>* node);
        void repairTreeRemove(Node<T>* node);
        void replaceNode(Node<T>* toReplace, Node<T>* newNode);
        void rotateLeft(Node<T>* node);
        void rotateRight(Node<T>* node);
};

#endif

template <class T>
RedBlackTree<T>::RedBlackTree() { 
    root = NULL;
}

// destructor implements recursive node deletion
template <class T>
RedBlackTree<T>::~RedBlackTree() {
    if (root) rcDelete(root);
}

template <class T> // same idea as strtok from cstring library
char* RedBlackTree<T>::concat(char* &destination, const char* source) {
    char* toReturn = new char[strlen(destination) + strlen(source) + 1];
    toReturn[strlen(destination) + strlen(source)] = '\0';
    strcpy(toReturn, destination);
    for (int i = 0; i < strlen(source); i++) toReturn[strlen(destination) + i] = source[i];
    // delete[] destination;
    destination = toReturn;
    return destination;
}

template <class T>
bool RedBlackTree<T>::contains(T key) {
    return !rcSearch(root, key)->isLeaf();
}

template <class T> 
Node<T>* RedBlackTree<T>::insert(T element) {
    Node<T>* newNode = new Node<T>(element, true); // new nodes are always red
    root = rcInsert(root, newNode); 
    newNode->setLeft(new Node<T>()); // leaf nodes
    newNode->getLeft()->setParent(newNode);
    newNode->setRight(new Node<T>());
    newNode->getRight()->setParent(newNode);
    repairTreeInsert(newNode);
    return newNode;
}

template <class T>
void RedBlackTree<T>::print() {
    if (!root) cout << "Tree is empty." << endl;
    else rcPrint(root, new char[1] {'\0'}, false);
}

// deallocates subtree with root node "node"
template<class T>
void RedBlackTree<T>::rcDelete(Node<T>* node) {
    if (node->getLeft()) rcDelete(node->getLeft());
    if (node->getRight()) rcDelete(node->getRight());
    delete node;
}

template <class T>
Node<T>* RedBlackTree<T>::rcInsert(Node<T>* node, Node<T>* newNode) {
    if (node && node->isLeaf()) { // delete pointer so it can be replaced with non-leaf node inserted
        delete node;
        node = newNode;
    } else if (!node) node = newNode;
    else if (newNode->getValue() <= node->getValue()) { // assume overloaded <= operator
        node->setLeft(rcInsert(node->getLeft(), newNode));
        node->getLeft()->setParent(node);
    } else {
        node->setRight(rcInsert(node->getRight(), newNode));
        node->getRight()->setParent(node);
    } return node;
}

template <class T>
void RedBlackTree<T>::rcPrint(Node<T>* node, char* tabstop, bool branch) {
    if (node->isLeaf()) { // when printing out only left node and right node is leaf node
        cout << tabstop << "|   " << endl;
        return;
    } else {
        cout << tabstop << (branch ? "├── " : "└── ") << flush;
        if (node->isRed()) cout << "\033[1;41m" << node->getValue() << "\033[0m" << endl; 
        else cout << "\033[7m" << node->getValue() << "\033[0m" << endl;
    } concat(tabstop, (branch ? "|   " : "    "));
    if (node->getLeft()->isLeaf() && !node->getRight()->isLeaf()) rcPrint(node->getRight(), tabstop, false);
    else if (!node->getLeft()->isLeaf()) {
        rcPrint(node->getRight(), tabstop, true);
	    char* copyOfTabstop = new char[strlen(tabstop) + 1];
	    strcpy(copyOfTabstop, tabstop); // create copies when branching so each remembers how far to indent
        rcPrint(node->getLeft(), copyOfTabstop, false);
    } else delete[] tabstop; // if node has no children it will no longer use tabstop
}

// search starting at root of subtree "node"
template <class T> // assume overloading of == and <
Node<T>* RedBlackTree<T>::rcSearch(Node<T>* node, T key) {
    if (node->isLeaf() || key == node->getValue()) return node;
    else if (key < node->getValue()) return rcSearch(node->getLeft(), key);
    else return rcSearch(node->getRight(), key);
}

template <class T>
bool RedBlackTree<T>::remove(T key) {
    Node<T>* toDelete = rcSearch(root, key);
    if (toDelete->isLeaf()) return false; // key not in tree
    if (!toDelete->getLeft()->isLeaf() && !toDelete->getRight()->isLeaf()) { // node to delete has two children
        // use one or no child deletion on successor after value of successor copied into node to delete
        Node<T>* successor = toDelete->getRight(); // find successor as leftmost node of right subtree
        while (!successor->getLeft()->isLeaf()) successor = successor->getLeft(); 
        toDelete->setValue(successor->getValue()); // copy just the value of the successor
        toDelete = successor; // set successor to be deleted with one or no child methods that follow
    } if (toDelete->isRed()) { // must have no children besides null leaves
        delete toDelete->getRight(); // since moving left leaf node into position this is no longer used
        replaceNode(toDelete, toDelete->getLeft());
    } else if (!toDelete->getLeft()->isLeaf()) { // black node with red left child
        toDelete->getLeft()->setRed(false); // red child turns black and takes node to delete's position
        replaceNode(toDelete, toDelete->getLeft());
    } else if (!toDelete->getRight()->isLeaf()) { // black node with red right child
        toDelete->getRight()->setRed(false);
        replaceNode(toDelete, toDelete->getRight());
    } else { // black node with no children
        Node<T>* child = toDelete->getLeft();
        delete toDelete->getRight(); // since moving left leaf node into position this is no longer used
        replaceNode(toDelete, child);
        repairTreeRemove(child); // child has reduced black depth, call repair
        if (root->isLeaf()) { // if deleted root remove leaf node in root
            delete root;
            root = NULL;
        }
    } return true;
}

template <class T>
void RedBlackTree<T>::repairTreeInsert(Node<T>* node) {
    if (!node->getParent()) node->setRed(false); // root always black
    else if (node->getParent()->isRed()) { // if parent not black then repair tree, uncle must exist because parent is not root
        if (node->getUncle()->isRed()) {
            node->getParent()->setRed(false);
            node->getUncle()->setRed(false);
            node->getGrandparent()->setRed(true);
            repairTreeInsert(node->getGrandparent());
        } else { // uncle is black
            if (node == node->getGrandparent()->getLeft()->getRight()) { // rotate into left left case
                rotateLeft(node->getParent()); // node takes parent position, parent becomes left child
                node = node->getLeft(); // left left case on old parent (now left child)
            } else if (node == node->getGrandparent()->getRight()->getLeft()) { // rotate into right right
                rotateRight(node->getParent()); // node takes parent position, parent becomes right child
                node = node->getRight(); // right right case on old parent (now right child)
            } Node<T>* grandparent = node->getGrandparent(); // save pointer for recoloring
            if (node == node->getParent()->getLeft()) rotateRight(grandparent); // step 2: left left case
            else rotateLeft(grandparent); // step 2: right right case
            node->getParent()->setRed(false); // parent takes grandparent position, recolor as black
            grandparent->setRed(true); // grandparent takes uncle position, recolor as red
            // no need to recursively move upward because root of rotation is black
            // and, black length is maintained because previously to get to node and parent (red)
            // you must pass through grandparent(black)
            // now to get to grandparent or node(red) must pass through parent (black)
        }
    }
}

template <class T>
void RedBlackTree<T>::repairTreeRemove(Node<T>* node) { // subtree of "node" has reduced black length. goal is to balance the reduction
    if (node->getParent() == null) return; // case 1: node to repair is root, no need to do so because we can reduce entire tree's black depth
    // case 2: sibling is red (thus parent is black)
    if (node->getSibling()->isRed()) { // transfer red from sibling to parent, rotate parent towards node's side
        // node still has reduced black height but now sibling is black, can be solved with upcoming black sibling cases
        node->getParent()->setRed(true);
        node->getSibling()->setRed(false);
        if (node == node->getParent()->getLeft()) rotateLeft(node->getParent());
        else rotateRight(node->getParent());
    }
}

template <class T> // attach subtree of newNode in place of toReplace
void RedBlackTree<T>::replaceNode(Node<T>* toReplace, Node<T>* newNode) {
    if (!toReplace->getParent()) root = newNode; // if no parent, replace the root with newNode
    else if (toReplace == toReplace->getParent()->getLeft()) toReplace->getParent()->setLeft(newNode); // if left child of parent, replace left child of parent with newNode
    else toReplace->getParent()->setRight(newNode); // if right child of parent, replace right child of parent with newNode
    if (newNode) newNode->setParent(toReplace->getParent()); // newNode's parent is now parent of replaced node
    delete toReplace; // now that node to replace is out of tree, deallocate it
}

// node->right takes node's position, node moves left to become left child of node->right
// node-right's left child becomes node's right child
template <class T>
void RedBlackTree<T>::rotateLeft(Node<T>* node) {
    Node<T>* rightNode = node->getRight();
    node->setRight(rightNode->getLeft()); // node no longer points to rightNode
    node->getRight()->setParent(node);
    rightNode->setLeft(node); // node is now left child of rightNode
    rightNode->setParent(node->getParent()); // rightNode takes node's position
    node->setParent(rightNode);
    if (rightNode->getParent()) { // if rightNode did not take root's position
        if (node == rightNode->getParent()->getLeft()) rightNode->getParent()->setLeft(rightNode);
        else rightNode->getParent()->setRight(rightNode); // update parent to child relationship
    } else root = rightNode; // otherwise rightNode moved into root position
}

template <class T>
void RedBlackTree<T>::rotateRight(Node<T>* node) {
    Node<T>* leftNode = node->getLeft();
    node->setLeft(leftNode->getRight());
    node->getLeft()->setParent(node);
    leftNode->setRight(node);
    leftNode->setParent(node->getParent());
    node->setParent(leftNode);
    if (leftNode->getParent()) {
        if (node == leftNode->getParent()->getLeft()) leftNode->getParent()->setLeft(leftNode);
        else leftNode->getParent()->setRight(leftNode);
    } else root = leftNode;
}


