#include "Node.h"
#include <cstddef>

Node::Node(char* value) {
    left = right = NULL;
    this->value = value;
}

Node::~Node() {
    delete value;
}

// setters
void Node::setValue(char* value) {
    this->value = value;
}

void Node::setLeft(Node* left) {
    this->left = left;
}

void Node::setRight(Node* right) {
    this->right = right;
}

// getters
char* Node::getValue() {
    return value;
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}

