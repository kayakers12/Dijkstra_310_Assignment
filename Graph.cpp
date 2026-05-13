#include "Graph.h"
#include <iostream>
#include <climits>

Graph::Graph(int n, int m) { //creates 2d array w vertices and edges
    numOfVertices = n;
    numOfEdges = m;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            adjMatrix[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        vertices[i].setIndex(i);
        vertices[i].setDegree(0);
    }
}

void Graph::addEdge(int u, int v, int weight) {  // deals with weigth of edge/ degree 
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
    vertices[u].setDegree(vertices[u].getDegree() + 1);
    vertices[v].setDegree(vertices[v].getDegree() + 1);
}

void Graph::printAdjMatrix() {  //prints the 2d array of graph
    std::cout << "The adjacency matrix of G is:" << std::endl;
    for (int i = 1; i <= numOfVertices; i++) {
        for (int j = 1; j <= numOfVertices; j++) {
            if (j > 1) std::cout << " ";
            std::cout << adjMatrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::printOddDegreeNodes() { // for the second task 
    int oddNodes[MAXN];
    int oddCount = 0;

    for (int i = 1; i <= numOfVertices; i++) {
        if (vertices[i].getDegree() % 2 != 0) {
            oddNodes[oddCount++] = i;
        }
    }

    std::cout << "The nodes with odd degrees in G are:" << std::endl;
    std::cout << "O = { ";
    for (int i = 0; i < oddCount; i++) {
        std::cout << oddNodes[i] << " ";
    }
    std::cout << "}" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < oddCount; i++) {
        dijkstra(oddNodes[i]);
        std::cout << std::endl;
    }
}

void Graph::dijkstra(int source) { //to find shortest path make use of Heap node and 2d array of graph
    int dist[MAXN + 1];
    bool visited[MAXN + 1];

    for (int i = 1; i <= numOfVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[source] = 0;
    MinHeap pq(numOfVertices * numOfVertices);
    pq.push(0, source);

    while (!pq.empty()) {
        HeapNode curr = pq.pop();
        int d = curr.dist;
        int u = curr.node;

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 1; v <= numOfVertices; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                int newDist = d + adjMatrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.push(newDist, v);
                }
            }
        }
    }

    std::cout << "The shortest path lengths from Node " << source //printing out shortest path
              << " to all other nodes are:" << std::endl;
    for (int i = 1; i <= numOfVertices; i++) {
        std::cout << "  " << i << ": " << dist[i] << std::endl;
    }
}
