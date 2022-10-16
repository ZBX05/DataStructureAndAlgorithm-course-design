#include "graphm.h"

Graphm::Graphm(int numVert) {
    numVertex = numVert;
    len=0;
    numEdge = 0;
    Indegree = new int[numVertex];
    Mark = new int[numVertex];
    for (int i = 0; i < numVertex; i++) {
        Mark[i] = UNVISITED;
        Indegree[i] = 0;
    }
}
Graphm::~Graphm() {
    delete[]Mark;
    delete[]Indegree;
}
int Graphm::VerticesNum() {
    return numVertex;
}
bool Graphm::isEdge(Edge oneEdge) {
    if (oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.to >= 0)
        return true;
    else
        return false;
}
