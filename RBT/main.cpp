#include "RedBlackTree.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int indexOf(char c, char cstr[], int occurrence) {
    int count = 0;
    for (int i = 0; i < strlen(cstr); i++) if (cstr[i] == c && ++count == occurrence) return i;
    return -1;
}

int main() {
    RedBlackTree<int>* rbt = new RedBlackTree<int>();
    char input[SHRT_MAX + 1];
    cout << "Would you like to read in numbers from a file first? (yes/no): " << flush;
    cin.getline(input, sizeof(input) / sizeof(input[0]));
    if (strcmp(input, "yes") == 0) {
        ifstream fin;
        cout << "Enter the file name (e.g. example.txt): " << flush;
        cin.getline(input, sizeof(input) / sizeof(input[0]));
        fin.open(input);
        if (fin.is_open()) {
            int count = 0;
            int data;
            fin >> data;
            do {
                rbt->insert(data);
                count++;
                fin >> data;
            } while (!fin.eof());
            cout << "Created red black tree with " << count << " nodes." << endl;
        } else cout << "File not found." << endl;
    } 
    // four options: enter a number to insert, "print" to print tree, "rm" followed by a number to remove it, "quit" to exit
    cout << "Enter a number to insert it to the red black tree." << endl;
    cout << "Type \"print\" to list all element sin a tree format." << endl;
    // cout << "Type \"rm\" followed by a number to remove it from the tree, if present." << endl;
    cout << "Type \"quit\" to terminate the program." << endl;
    do {
        cout << "> " << flush;
        cin.getline(input, sizeof(input) / sizeof(input[0]));
        if (isdigit(input[0])) rbt->insert(atoi(input));
        else if (strcmp(input, "print") == 0) rbt->print();
    } while (strcmp(input, "quit") != 0);
}
