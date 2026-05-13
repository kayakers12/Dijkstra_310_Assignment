#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"
#include <climits>

const int MAXN = 1000; //large enough number to handle 

struct HeapNode {
    int dist; //distance 
    int node;
};
//use HeapNode since Dijkstra needs to visit next closest unvisited node 
struct MinHeap {
    HeapNode* data;
    int size;
    int capacity;

    MinHeap(int cap) : size(0), capacity(cap) {
        data = new HeapNode[cap];
    }

    ~MinHeap() { delete[] data; }
    // add node 
    void push(int d, int n) {   // pushes up node until its in correct position
        data[size].dist = d;
        data[size].node = n;
        int i = size++;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (data[parent].dist > data[i].dist) {
                HeapNode tmp = data[parent];
                data[parent] = data[i];
                data[i] = tmp;
                i = parent;
            } else break;
        }
    }
    // remove node with smallest distance 
    HeapNode pop() {  // pushes down replacement 
        HeapNode top = data[0];
        data[0] = data[--size];
        int i = 0;
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < size && data[left].dist < data[smallest].dist)
                smallest = left;
            if (right < size && data[right].dist < data[smallest].dist)
                smallest = right;
            if (smallest != i) {
                HeapNode tmp = data[i];
                data[i] = data[smallest];
                data[smallest] = tmp;
                i = smallest;
            } else break;
        }
        return top;
    }

    bool empty() { return size == 0; } //checks if empty 
};

class Graph {
    private:
        int adjMatrix[MAXN + 1][MAXN + 1];
        Vertex vertices[MAXN + 1];
        int numOfVertices;
        int numOfEdges;

    public:
        Graph(int n, int m);
        void addEdge(int u, int v, int weight);
        void printAdjMatrix();
        void printOddDegreeNodes();
        void dijkstra(int source);
};

#endif
