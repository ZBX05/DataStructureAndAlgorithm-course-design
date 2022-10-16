#ifndef GRAPHM_H
#define GRAPHM_H

#define UNVISITED -2
#define VISITED -3
#define INFINITY 9999
#include "edge.h"
#include <QObject>


class Graphm:public QObject
{
        Q_OBJECT
public:
//    explicit Graphm(QObject *parent=0);
    int numVertex;
    int len;
    int numEdge;
    int* Mark;
    int* Indegree;
    Graphm(int numVert);
    ~Graphm();
    int VerticesNum();
    bool isEdge(Edge oneEdge);
};

#endif // GRAPHM_H
