#include "RedBlackTree.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <iterator>
using namespace std;

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
        int endIndex = indexOf(delim, cstr, count + 1) == -1 ? strlen(cstr) : indexOf(delim, cstr, count + 1); // exclusive; end before next space, end of string if -1
        int startIndex = indexOf(delim, cstr, count) + 1; // inclusive, start after current space
        if (startIndex != endIndex) tokens->push_back(substr(cstr, startIndex, endIndex)); // prevent empty string
    } while (indexOf(delim, cstr, ++count) != -1); // while there are more tokens
    return tokens;
}

int main() {
    RedBlackTree<int>* rbt = new RedBlackTree<int>();
    char* input = new char[SHRT_MAX];
    // four options: enter a number to insert, "print" to print tree, "rm" followed by a number to remove it, "quit" to exit
    cout << "Enter a number to insert it to the red black tree." << endl;
    cout << "Type \"file\" followed by the file name to input numbers from a file." << endl;
    cout << "Type \"print\" to list all element sin a tree format." << endl;
    cout << "Type \"find\" followed by a number to search for an element." << endl;
    cout << "Type \"rm\" followed by a number to remove it from the tree, if present." << endl;
    cout << "Type \"quit\" to terminate the program." << endl;
    bool quit = false;
    do {
        cout << "> " << flush;
        cin.getline(input, SHRT_MAX);
        vector<char*>* tokens = split(input, ' ');
        delete[] input;
        if (isdigit(tokens->front()[0])) rbt->insert(atoi(tokens->front()));
        else if (strcmp(tokens->front(), "file") == 0) {
            ifstream fin;
            fin.open(tokens->back());
            if (fin.is_open()) {
                int count = 0;
                int data;
                fin >> data;
                do {
                    rbt->insert(data);
                    count++;
                    fin >> data;
                } while (!fin.eof());
                cout << "Inserted " << count << " nodes." << endl;
            } else cout << "File not found." << endl;
        } else if (strcmp(tokens->front(), "print") == 0) rbt->print();
        else if (strcmp(tokens->front(), "find") == 0) cout << (rbt->contains(atoi(tokens->back())) ? "found" : "not found") << endl;
        else if (strcmp(tokens->front(), "rm") == 0) cout << (rbt->remove(atoi(tokens->back())) ? "" : "not found\n") << flush;
        else if (strcmp(tokens->front(), "quit") == 0) quit = true;
        delete tokens;
        input = new char[SHRT_MAX];
    } while (!quit);
}
