#include "Graph.h"
#include <iostream>

int main() {
    int numOfVertices;
    int numOfEdges;

    if (!std::cin.eof()) {
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    } else {
        std::cout << "Input not found!" << std::endl;
        return 0;
    }

    Graph g(numOfVertices, numOfEdges); 

    while (!std::cin.eof()) {
        int startVert, endVert, weight;
        if (!(std::cin >> startVert >> endVert >> weight)) break;

        Edge* newEdge = new Edge(startVert, endVert);
        newEdge->setWeight(weight);

        g.addEdge(startVert, endVert, weight);

        delete newEdge;
    }

    g.printAdjMatrix();
    g.printOddDegreeNodes();
    //kept mostly the same except for calling the graph creation and print
    return 0;
}
