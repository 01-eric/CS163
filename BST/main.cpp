#include "BinarySearchTree.h"
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
    BinarySearchTree<int>* bst = new BinarySearchTree<int>();
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
            do {
                int data;
                fin >> data;
                bst->insert(data);
                count++;
            } while (!fin.eof());
            cout << "Created binary search tree with " << count << " nodes." << endl;
        } else cout << "File not found." << endl;
    }

    // four options: enter a number to insert it, print to print heap, rm followed by a number to remove it, quit to exit
    cout << "Enter a number to insert it to the binary search tree." << endl;
    cout << "Type \"print\" to list all elements in a tree format." << endl;
    cout << "Type \"rm\" followed by a number to remove it from the tree, if present." << endl;
    cout << "Type \"quit\" to exit the program." << endl;
    do {
        cout << "> " << flush;
        cin.getline(input, sizeof(input) / sizeof(input[0]));
        if (isdigit(input[0])) bst->insert(atoi(input));
        else if (strcmp(input, "print") == 0) bst->print();
        else if (indexOf(' ', input, 1) != -1) { // assume keyword is rm
            char num[strlen(input) - indexOf(' ', input, 1)]; // extra space for '\0'
            // cout << strlen(input) << ' ' << indexOf(' ', input, 1) << endl;
            // cout << sizeof(num) / sizeof(num[0]) << ' ' << strlen(num) << endl;
            for (int i = 0; num[i] != '\0'; i++) num[i] = input[indexOf(' ', input, 1) + 1 + i];
            // cout << num << endl;
            if (!bst->remove(atoi(num))) cout << num << " is not in the tree." << endl;
        }
    } while (strcmp(input, "quit") != 0);

    delete bst;
}
