#include "cstringfunctions.h"
#include "Student.h"
#include "LinkedList.h"
#include "HashTable.h"
#include <cstdlib>
#include <climits>
#include <fstream>
#include <ctime>

Student* getRandomStudent() {
    vector<char*>* first = new vector<char*>(); // read in all names into a vector
    vector<char*>* last = new vector<char*>();
    ifstream fin1; // file input from first file
    ifstream fin2; // file input from second file
    fin1.open("first.txt"); // file of first names
    char* input = new char[SHRT_MAX];
    fin1 >> input;
    while (!fin1.eof()) {
        first->push_back(input);
        input = new char[SHRT_MAX];
        fin1 >> input; // read right before condition check to prevent eof from getting missed
    } fin2.open("last.txt");
    input = new char[SHRT_MAX];
    fin2 >> input;
    while (!fin2.eof()) {
        last->push_back(input);
        input = new char[SHRT_MAX];
        fin2 >> input;
    } char* name = new char[SHRT_MAX]; // create new because all elements in vectors will be deallocated
    strcpy(name, first->at(rand() % first->size()));
    concat(name, " ");
    concat(name, last->at(rand() % last->size()));
    delete first; // deallocates all cstrings
    delete last; // deallocates all cstrings
    Student* newStudent = new Student(name, rand() % 900000 + 100000, (double)(rand() % 400) / 100 + 1);
    cout << "Added ";
    newStudent->print();
    cout << endl;
    return newStudent;
}

int main() {
    srand(time(NULL)); // no idea what this does lol
    HashTable* hash = new HashTable();
    char* input = new char[SHRT_MAX];
    cout << "Type \"add\" followed by a student name, ID, and GPA (e.g. Kevin Jin 100101 1.00) to add student." << endl;
    cout << "Type \"add rand\" and an optional number to specify how many random students to add." << endl;
    cout << "Type \"print\" to list all students in the hash table." << endl;
    cout << "Type \"rm\" followed by an ID number to remove a student from the list." << endl;
    cout << "Type \"quit\" to exit." << endl;
    do {
        cout << "\033[1;32m> \033[0m" << flush;
        cin.getline(input, SHRT_MAX);
        vector<char*>* tokens = split(input, ' ');
        if (strcmp(tokens->front(), "print") == 0) hash->print();
        else if (strcmp(tokens->front(), "add") == 0) {
            if (strcmp(tokens->at(1), "rand") == 0) {
                int count = (tokens->size() == 2 ? 1 : atoi(tokens->back()));
                while (count-- > 0) hash->add(getRandomStudent());
            } else {
                char* name = new char[strlen(tokens->at(1)) + 1];
                strcpy(name, tokens->at(1));
                concat(name, " ");
                concat(name, tokens->at(2));
                hash->add(new Student(name, atoi(tokens->at(3)), atof(tokens->back())));
            }
        } else if (strcmp(tokens->front(), "rm") == 0) hash->remove(atoi(tokens->back()));
        delete tokens;
    } while (strcmp(input, "quit") != 0);
    delete[] input;
    delete hash;
}
