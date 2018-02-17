#include <cstring>
#include <cstdio>
#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include "Node.h"
#include "Stack.h"
using std::vector;
using std::cout;
using std::cin;
using std::flush;
using std::map;

// 2 - 3 - 4 - 5
// 2 ^ 3 ^ 4 ^ 5
// a * x ^ 2 + b * x + c
// x ^ y ^ z / ( 5 * y * z ) + 10

int indexOf(char c, char* cstr, int occurence);
char* substr(char* cstr, int start, int end);
vector<char*>* split(char* cstr, char delim);

int main() {
    // keep levels of precedence in a map
    map<char, int> precedence;
    precedence['+'] = 0;
    precedence['-'] = 0;
    precedence['*'] = 1;
    precedence['/'] = 1;
    precedence['^'] = 2;

    cout << "Enter a mathematical expression with operators and operands separated by spaces: " << std::endl;
    char* input = new char[SHRT_MAX];
    cin.getline(input, SHRT_MAX);
    vector<char*>* elements = split(input, ' '); // note vector destructor deletes all elements
    // for (int i = 0; i < elements->size(); i++) cout << elements->at(i) << ' ' << flush;
    delete [] input;
    Stack* postfix = new Stack();
    Stack* operators = new Stack();

    // the shunting yard algorithm
    while (elements->size() > 0) { // while there are tokens to be read from elements
        char* element = elements->front();
        elements->erase(elements->begin());
        if (isalnum(element[0])) postfix->push(element);
        else if (strcmp(element, "(") == 0) operators->push(element);
        else if (strcmp(element, ")") == 0) {
            while (strcmp(operators->peek(), "(") == 0) postfix->push(operators->pop()); // pop all operators until (
            delete [] operators->pop(); // left bracket
            delete element; // right bracket
        } else { // is operator
            // if stack not empty pop all elements on stack with greater/equal precedence unless current element is power operator and element on stack is also power operator
            while (operators->peek() && strcmp(operators->peek(), "(") != 0 && precedence[operators->peek()[0]] >= precedence[element[0]] && strcmp(element, "^") != 0)
                postfix->push(operators->pop());
            operators->push(element); // push new operator onto stack
        }
    } delete elements; // empty vector
    while (operators->peek()) postfix->push(operators->pop());
    while (postfix->peek()) {
        char* c = postfix->pop();
        cout << c << ' ' << flush;
        delete [] c;
    }
}

// returns nth occurrence of c index in cstr
int indexOf(char c, char* cstr, int occurrence) {
    int count = 0;
    for (int i = 0; i < strlen(cstr); i++) if (cstr[i] == c && ++count == occurrence) return i;
    return -1;
}

// similar syntax as substring in java
char* substr(char* cstr, int start, int end) {
    char* substr = new char[end - start + 1]; // +1 for null char
    for (int i = 0; i < end - start; i++) substr[i] = cstr[start + i]; // making copy char by char
    substr[end - start] = '\0'; // why do i have to do this
    return substr;
}

// splits cstr by a delim character and returns vector of all tokens
vector<char*>* split(char* cstr, char delim) {
    vector<char*>* tokens = new vector<char*>();
    int count = 0; // keep track of which token we are on
    do { // 0th occurence in indexOf returns -1 so we use do while
        int endIndex = indexOf(delim, cstr, count + 1);
        tokens->push_back(substr(cstr, indexOf(delim, cstr, count) + 1, endIndex == -1 ? strlen(cstr) : endIndex));
    } while (indexOf(delim, cstr, ++count) != -1); // while there are more tokens
    return tokens;
}
