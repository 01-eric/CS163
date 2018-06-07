#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph {

    public:
        ~Graph();
        void insertEdge(char node1, char node2, int weight);
        void insertNode(char name);
        void print();
        int size();
    
    private:
        vector<vector<int>*>* graph = new vector<vector<int>*>(); // graph is dynamic 2 dimensional adjacency list
        vector<char>* nodemap = new vector<char>(); // used to identify which index is which node
        bool contains(vector<char>* v, char key); 
        int indexOf(vector<char>* v, char key);
};

#endif

Graph::~Graph() {
    delete graph; // apparently all elements of vector are also destroyed
    delete nodemap;
}

bool Graph::contains(vector<char>* v, char key) {
    return indexOf(v, key) != -1;
}

int Graph::indexOf(vector<char>* v, char key) {
    for (int i = 0; i < v->size(); i++) if (v->at(i) == key) return i;
    return -1;
}

void Graph::insertEdge(char node1, char node2, int weight) {
    if (!contains(nodemap, node1) || !contains(nodemap, node2)) cout << "Some nodes were not found." << endl;
    else if (graph->at(indexOf(nodemap, node1))->at(indexOf(nodemap, node2)) == 0) {
        graph->at(indexOf(nodemap, node1))->at(indexOf(nodemap, node2)) = weight;
        graph->at(indexOf(nodemap, node2))->at(indexOf(nodemap, node1)) = weight;
    } else cout << "Cannot create double edges." << endl;
}

void Graph::insertNode(char name) {
    if (!contains(nodemap, name)) {
        graph->push_back(new vector<int>());
        for (int i = 0; i < size(); i++) {
            graph->back()->push_back(0);
            if (i != size() - 1) graph->at(i)->push_back(0);
        } nodemap->push_back(name);
    } else cout << "Cannot create duplicate node." << endl;
}

void Graph::print() {
    if (size() > 0) {
        int maxlength = 1;
        for (int i = 0; i < size(); i++) 
            for (int j = 0; j < size(); j++) 
                maxlength = max(maxlength, (int)log10(max(1, graph->at(i)->at(j))) + 1);
        cout << ' ';
        for (int i = 0; i < nodemap->size(); i++) {
            for (int j = 0; j < maxlength; j++) cout << ' ';
            cout << "\033[1;31m" << nodemap->at(i) << "\033[0m";
        } cout << endl;
        for (int i = 0; i < size(); i++) {
            cout << "\033[1;31m" << nodemap->at(i) << "\033[0m";
            for (int j = 0; j < size(); j++) {
                for (int k = 0; k < maxlength - (int)log10(max(1, graph->at(i)->at(j))); k++) cout << ' ';
                cout << graph->at(i)->at(j); 
            } cout << endl;
        }
    } else cout << "Graph is empty." << endl;
}

int Graph::size() {
    return graph->size();
}
