#include <cstring>
#include <cstdio>
#include <iostream>
#include <climits>
#include "Node.h"
#include "Stack.h"

int main() {
    std::cout << "Enter a mathematical expression with operators and operands separated by spaces:" << std::flush;
    char* input = new char[SHRT_MAX];
    std::cin.getline(input, SHRT_MAX);
    printf(input);
}
