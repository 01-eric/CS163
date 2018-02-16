#include "Node.h"
#include <cstddef>
#ifndef STACK_H_
#define STACK_H_

class Stack {

public:
    ~Stack();
    void push(char* element); // top will have no left pointer
    char* pop();
    char* peek();
        

private:
    Node* top = NULL;

};

#endif
