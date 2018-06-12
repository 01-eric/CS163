#include <cstring>

#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable {

    public:
        HashTable();
        ~HashTable();
        void add(Student* student);
        void print();        
        void remove(int id);

    private:
        LinkedList<Student*>** data;
        int data_length; // acts as sizeof(data) / sizeof(data
        int size; // actual amount of data
        int hashFunction(Student* student);
        void rehash();

};

#endif

HashTable::HashTable() {
    data = new LinkedList<Student*>*[100]; // dynamically allocate array of 100 linkedlist pointers
    data_length = 100; // this value will change as data is resized
    for (int i = 0; i < data_length; i++) data[i] = new LinkedList<Student*>();
    size = 0; // will represent amount of students in the table
}

HashTable::~HashTable() {
    delete[] data; 
}

int HashTable::hashFunction(Student* student) {
    int index = 0;
    for (int i = 0; i < strlen(student->getName()); i++) index += student->getName()[i]; // add ascii of name
    index += student->getID() + (int)(student->getGPA() * 100); // add id and gpa * 100
    return index % data_length; // mod size of array
}

void HashTable::add(Student* student) {
    data[hashFunction(student)]->add(student); // insert into linkedlist at index given by hash function
    if (data[hashFunction(student)]->getSize() > 3) rehash(); // if greater than 3 chaining then resize table
    size++; // keep track of count of students
}

void HashTable::print() {
    cout << "Size: " << size << ", Capacity: " << data_length << endl;
    for (int i = 0; i < data_length; i++) { 
        if (data[i]->getSize() > 0) {
            cout << i << ": ";
            for (int j = 0; j < data[i]->getSize(); j++) {
                cout << (j == 0 ? '[' : ' ');
                data[i]->get(j)->print();
                cout << (j == data[i]->getSize() - 1 ? ']' : ',');
            } cout << endl;
        }
    }
}

void HashTable::rehash() {
    LinkedList<Student*>** oldArray = data;
    data = new LinkedList<Student*>*[(data_length *= 2)];
    for (int i = 0; i < data_length; i++) data[i] = new LinkedList<Student*>();
    bool recurse = false;
    for (int i = 0; i < data_length / 2; i++) {
        for (int j = 0; j < oldArray[i]->getSize(); j++) {
            data[hashFunction(oldArray[i]->get(j))]->add(oldArray[i]->get(j));
            if (data[hashFunction(oldArray[i]->get(j))]->getSize() > 3) recurse = true;
        }
    } delete[] oldArray; 
    if (recurse) rehash();
}

void HashTable::remove(int id) {
    for (int i = 0; i < data_length; i++) {
        for (int j = 0; j < data[i]->getSize(); j++) {
            if (id == data[i]->get(j)->getID()) {
                cout << "Removed " << data[i]->get(j)->getName() << endl;
                delete data[i]->get(j); // deallocate student first
                data[i]->remove(j);
                size--;
            }
        }
    }
}
