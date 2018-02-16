#ifndef NODE_H_
#define NODE_H_

class Node {

public:
    Node(char* value); // enables setting value when created
    ~Node();
    // setters
    void setValue(char* value);
    void setLeft(Node* left);
    void setRight(Node* right);
    // getters
    char* getValue();
    Node* getLeft();
    Node* getRight();

private:
    char* value;
    Node* left;
    Node* right;

};

#endif
