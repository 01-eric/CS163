#include "cstringfunctions.h"
#include "LinkedList.h"
#include <cstdlib>
#include <climits>

int main() {
    LinkedList<char>* list = new LinkedList<char>();
    char* input = new char[SHRT_MAX];
    do {
        cout << "\033[1;32m> \033[0m" << flush;
        cin.getline(input, SHRT_MAX);
        vector<char*>* tokens = split(input, ' ');
        if (strcmp(tokens->front(), "print") == 0) list->print();
        else if (strcmp(tokens->front(), "rm") == 0) {
            if (tokens->size() == 1) list->remove();
            else list->remove(tokens->back()[0] - 48);
        } else if (tokens->size() == 2) list->add(tokens->back()[0] - 48, tokens->front()[0]);
        else list->add(tokens->front()[0]);
        delete tokens;
    } while (strcmp(input, "quit") != 0);
    delete[] input;
    delete list;
}
