#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph {

    public:
        ~Graph();
        vector<char>* findShortestPath(char node1, char node2);
        void insertEdge(char node1, char node2, int weight);
        void insertNode(char name);
        void removeEdge(char node1, char node2);
        void removeNode(char name);
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

vector<char>* Graph::findShortestPath(char node1, char node2) {
    vector<char>* path = new vector<char>();
    if (!contains(nodemap, node1) || !contains(nodemap, node2)) cout << "Some nodes were not found." << endl;
    else {
        // we build an SPT, but if no SPT output is required, we do not need to keep track of SPT
        // simply backtrace shortestPathProvider array to find path.
        // backtrace is always correct, there only exists one path between node1 and node2 since it is a tree
        int distanceFromSource[size() + 1]; // cumulative length of shortest path from source to node of index i
        int shortestPathProvider[size() + 1]; // the node in the SPT which provides that path to node of index i. if no adjacent nodes, it is -1
        bool visited[size() + 1]; // size() + 1 extra spot so when all nodes are selected, the extra spot terminates the function.
        for (int i = 0; i < size() + 1; i++) {
            distanceFromSource[i] = INT_MAX; // nodes that are not adjacent to current SPT are infinite length away and never selected
            shortestPathProvider[i] = -1; // nodes that are not adjacent to current SPT do not have an adjacent node, so initialize to -1
            visited[i] = false;
        } distanceFromSource[indexOf(nodemap, node1)] = 0; // source node (start of path; node1) is always selected first
        while (true) {
            int selectedNode = size();
            for (int i = selectedNode; i >= 0; i--) if (!visited[i] && distanceFromSource[i] < distanceFromSource[selectedNode]) selectedNode = i;
            if (shortestPathProvider[selectedNode] == -1 && selectedNode != indexOf(nodemap, node1)) break; // found all paths to nodes connected to source
            visited[selectedNode] = true;
            for (int i = 0; i < size(); i++) { // nodes adjacent to new visited node have distances updated
                if (!visited[i] && graph->at(selectedNode)->at(i) != 0 && graph->at(selectedNode)->at(i) + distanceFromSource[selectedNode] < distanceFromSource[i]) {
                    distanceFromSource[i] = graph->at(selectedNode)->at(i) + distanceFromSource[selectedNode]; // new distance = current distance + new edge
                    shortestPathProvider[i] = selectedNode; // new edge comes from current node
               }
           }
        } if (distanceFromSource[indexOf(nodemap, node2)] == INT_MAX) cout << "Path does not exist." << endl;
        else {
            int currentNode = indexOf(nodemap, node2);
            cout << "Length: " << distanceFromSource[currentNode] << endl;
            while (currentNode != -1) {
                path->insert(path->begin(), nodemap->at(currentNode));
                currentNode = shortestPathProvider[currentNode];
            }
        }
    } return path;
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

void Graph::removeEdge(char node1, char node2) {
    if (!contains(nodemap, node1) || !contains(nodemap, node2)) cout << "Some nodes were not found." << endl;
    else if (graph->at(indexOf(nodemap, node1))->at(indexOf(nodemap, node2)) != 0) {
        graph->at(indexOf(nodemap, node1))->at(indexOf(nodemap, node2)) = 0;
        graph->at(indexOf(nodemap, node2))->at(indexOf(nodemap, node1)) = 0;
    } else cout << "Edge does not exist." << endl;
}

void Graph::removeNode(char name) {
    if (contains(nodemap, name)) {
        for (int i = 0; i < size(); i++) graph->at(i)->erase(graph->at(i)->begin() + indexOf(nodemap, name));
        delete graph->at(indexOf(nodemap, name));
        graph->erase(graph->begin() + indexOf(nodemap, name));
        nodemap->erase(nodemap->begin() + indexOf(nodemap, name));
    } else cout << "Node does not exist." << endl;
}

int Graph::size() {
    return graph->size();
}
