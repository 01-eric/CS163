#include "Graph.h"
#include "cstringfunctions.h"
#include <cstdlib>

int main() {
    Graph* graph = new Graph();
    char* input = new char[SHRT_MAX];
    cout << "Enter a letter (a-z) to insert a node with that label." << endl;
    cout << "Enter two existing nodes and an integer to add an edge between those nodes." << endl;
    cout << "Type \"rm\" followed by an existing node to remove it." << endl;
    cout << "Type \"rm\" followed by two existing nodes to remove an edge between those nodes." << endl;
    cout << "Type \"path\" followed by two existing nodes to find the shortest path between those nodes." << endl;
    cout << "Type \"print\" to output an adjacency matrix of the graph." << endl;
    do {
        cout << "\033[1;32m> \033[0m" << flush;
        cin.getline(input, SHRT_MAX);
        vector<char*>* tokens = split(input, ' ');
        if (strcmp(tokens->front(), "rm") == 0) {
            if (tokens->size() == 2) graph->removeNode(tokens->back()[0]); // remove node
            else if (tokens->size() == 3) graph->removeEdge(tokens->at(1)[0], tokens->back()[0]); // remove edge
        } else if (strcmp(tokens->front(), "path") == 0) { // shortest path
            vector<char>* path = graph->findShortestPath(tokens->at(1)[0], tokens->back()[0]);            
            for (int i = 0; i < path->size(); i++) cout << (i == 0 ? '[' : ' ') << path->at(i) << (i == path->size() - 1 ? ']' : ',');
            if (path->size() > 0) cout << endl;
            delete path;
        } else if (tokens->size() == 1) {
            if (strlen(tokens->front()) == 1) graph->insertNode(tokens->front()[0]); // insert node
            else if (strcmp(tokens->front(), "print") == 0) graph->print(); // print
        } else graph->insertEdge(tokens->front()[0], tokens->at(1)[0], atoi(tokens->back())); // insert edge
        delete tokens;       
    } while (strcmp(input, "quit") != 0);
    delete [] input;
    delete graph;
}
