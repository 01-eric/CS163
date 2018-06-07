#include "Graph.h"
#include "cstringfunctions.h"
#include <climits>
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
        cin.getline(input, sizeof(input) / sizeof(input[0]));
        vector<char*>* tokens = split(input, ' ');
        if (strcmp(tokens->front(), "rm") == 0) {
            if (tokens->size() == 2); // remove node
            else if (tokens->size() == 3); // remove edge
        } else if (strcmp(tokens->front(), "path") == 0) { // shortest path`

        } else if (tokens->size() == 1) {
            if (strlen(tokens->front()) == 1) graph->insertNode(tokens->front()[0]);
            else if (strcmp(tokens->front(), "print") == 0) graph->print();
        } else graph->insertEdge(tokens->front()[0], tokens->at(1)[0], atoi(tokens->back()));
        delete tokens;       
    } while (strcmp(input, "quit") != 0);
    delete [] input;
    delete graph;
}
