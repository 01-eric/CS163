#include "Node.h"
#include <iostream>
#include <cstddef>
#include <string>
using namespace std;

void rcPrint(Node<int>* node, string tabstop, bool branch) {
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

int main() {
    Node<int>* root = new Node<int>(2);
    Node<int>* n11 = new Node<int>(7);
    Node<int>* n12 = new Node<int>(5);
    Node<int>* n21 = new Node<int>(2);
    Node<int>* n22 = new Node<int>(6);
    Node<int>* n23 = new Node<int>(3);
    Node<int>* n24 = new Node<int>(6);
    Node<int>* n31 = new Node<int>(5);
    Node<int>* n32 = new Node<int>(8);
    Node<int>* n33 = new Node<int>(4);
    Node<int>* n34 = new Node<int>(5);
    Node<int>* n36 = new Node<int>(4);
    Node<int>* n37 = new Node<int>(5);
    Node<int>* n38 = new Node<int>(8);
    root->setLeft(n11);
    root->setRight(n12);
    n11->setLeft(n21);
    n11->setRight(n22);
    n12->setLeft(n23);
    n12->setRight(n24);
    n21->setLeft(n31);
    n21->setRight(n32);
    n22->setLeft(n33);
    n22->setRight(n34);
    n23->setLeft(n36);
    n24->setLeft(n37);
    n24->setRight(n38);
    rcPrint(root, "", false);
}


