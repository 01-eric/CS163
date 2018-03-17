#include "Heap.h"
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
using namespace std;

int main() {
    Heap* heap = new Heap();
    char input[SHRT_MAX + 1];
    // four options: enter a number to insert it, PRINT to print heap, EMPTY to remove all, QUIT to exit
    cout << "Enter a number to insert it to the heap." << endl;
    cout << "Type PRINT to list all elements in the heap in a tree format." << endl;
    cout << "Type EMPTY to list all elements in the heap linearly and remove all of them." << endl;
    cout << "Type POP to free the top element and output it." << endl;
    cout << "Type QUIT to exit the program." << endl;
    do {
        cin.getline(input, sizeof(input) / sizeof(input[0]));
        if (isdigit(input[0])) heap->insert(atoi(input));
        else if (strcmp(input, "PRINT") == 0) heap->print();
        else if (strcmp(input, "EMPTY") == 0) {
            if (heap->getSize() == 0) cout << "Heap is already empty.";
            else while (heap->getSize() > 0) cout << heap->deleteMax() << ' ';
            cout << endl;
        } else if (strcmp(input, "POP") == 0) {
            if (heap->getSize() == 0) cout << "Heap is empty." << endl;
            else cout << heap->deleteMax() << endl;
        }
    } while (strcmp(input, "QUIT") != 0);
    delete heap;

    // tester code
    /* cout << heap->getCapacity() << ' ' << heap->getSize() << endl;
    heap->print();
    int array[10] = {3, 7, 4, 7, 10, 8, 4, 9, 15, 24};
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) heap->insert(array[i]);
    cout << heap->getCapacity() << ' ' << heap->getSize() << endl;
    heap->print();
    while (heap->getSize() > 0) cout << heap->deleteMax() << endl;
    cout << heap->getCapacity() << ' ' << heap->getSize() << endl;
    heap->print();
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) heap->insert(array[i]);
    cout << heap->getCapacity() << ' ' << heap->getSize() << endl;
    heap->print();
    while (heap->getSize() > 0) cout << heap->deleteMax() << endl;
    cout << heap->getCapacity() << ' ' << heap->getSize() << endl;
    heap->print();
    delete heap; */
}   
