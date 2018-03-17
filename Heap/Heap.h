#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

#ifndef HEAP_H
#define HEAP_H

class Heap {

    public:
        Heap() : Heap(100) {}; // default constructor allocates 100 capacity
        Heap(int capacity); // can specify capacity
        ~Heap(); // destructor will deallocate entire allocated capacity of heap
        int getCapacity(); // returns total capacity of heap
        int deleteMax(); // deletes the root node of the heap and rebalances the heap
        void insert(int element); // inserts element into heap at correct position
        void print(); // prints out binary tree form of heap
        int getSize(); // returns number of elements in the heap

    private:
        int* elements; // dynamically allocated array to hold elements in the heap
        int size = 0; // total number of elements currently stored in the array (usually less than capacity)
        int capacity; // the total allocated memory of the array
        int getParentIndex(int childIndex); // used in rcMoveUp to find index of parent to move to
        int getLeftChildIndex(int parentIndex); // used in rcMoveDown to find index of child to move to
        int getRightChildIndex(int parentIndex); // used in rcMoveDown to find index of child to move to
        void rcMoveDown(int currentIndex); // used in deleteMax to move the new root node down to correct place
        void rcMoveUp(int currentIndex); // used in insert to find correct place of inserted node

};

Heap::Heap(int capacity) {
    elements = new int[capacity];
    this->capacity = capacity;
}

Heap::~Heap() {
    delete[] elements;
}

int Heap::deleteMax() { // returns element removed from the heap, if unused in main then deallocate returned ptr
    if (size == 0) return INT_MIN;
    int toReturn = elements[0]; // pops root node
    elements[0] = elements[--size]; // moves last element to top of heap, no need to deallocate ptr is unchanged
    // no need to redefine last element because when size decreases it is treated as not part of heap
    rcMoveDown(0); // recursively move down the root node to correct position
    return toReturn;
} 

int Heap::getCapacity() {
    return capacity;
}

int Heap::getLeftChildIndex(int parentIndex) {
    return parentIndex * 2 + 1; // every level of tree increases by factor of 2
}

int Heap::getRightChildIndex(int parentIndex) {
    return getLeftChildIndex(parentIndex) + 1; // adjacent to left child in array
}

int Heap::getParentIndex(int childIndex) {
    return floor((double)(childIndex - 1) / 2); // flooring and casting is only needed for childIndex = 0
    // to return -1 since it has no parents
}

int Heap::getSize() {
    return size;
}

void Heap::insert(int element) {
    if (size < capacity) { // if heap capacity not exceeded
        elements[size++] = element; // append element to end of array, increasing size
        rcMoveUp(size - 1); // move the element to correct position in heap
    } else cout << "Heap capacity exceeded, value not inserted." << endl;
}

void Heap::print() {
    // depth of tree is base 2 logarithm of number of nodes rounded down
    int depth = (int)log2(size) + 1; // add 1 because root node is "level 0"
    int iterator = 0; // keeps index of array since loops are keeping track of levels instead
    for (int i = 0; i < depth; i++) { // insert new row between each level
        // there are 2^i elements in each level
        for (int j = 0; j < pow(2, i) && iterator < size; j++) cout << elements[iterator++] << ' ';
        cout << endl;
    }
}

void Heap::rcMoveDown(int currentIndex) {
    int childIndex = -1; // defaults to -1 if no children
    // first check to see if left child exists by comparing to array length
    // if it exists set it to left child index, then check to see if right child exists
    // if right child exists pick whichever one is greater to keep maximum at top
    if (getLeftChildIndex(currentIndex) < size) childIndex = getLeftChildIndex(currentIndex);
    if (getRightChildIndex(currentIndex) < size && elements[getRightChildIndex(currentIndex)] > elements[childIndex]) childIndex = getRightChildIndex(currentIndex); 
    if (childIndex != -1 && elements[currentIndex] < elements[childIndex]) { // if child exists and is greater than current value move current value down and recursively call on new position
        int temp = elements[childIndex];
        elements[childIndex] = elements[currentIndex];
        elements[currentIndex] = temp;
        rcMoveDown(childIndex);
    }
}

void Heap::rcMoveUp(int currentIndex) {
    // if parent exists and current value is greater than parent move it up and recursively call on parent
    if (getParentIndex(currentIndex) >= 0 && elements[currentIndex] > elements[getParentIndex(currentIndex)]) {
        int temp = elements[getParentIndex(currentIndex)];
        elements[getParentIndex(currentIndex)] = elements[currentIndex];
        elements[currentIndex] = temp;
        rcMoveUp(getParentIndex(currentIndex));
    }
}

#endif
