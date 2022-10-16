#ifndef GRAPH_H
#define GRAPH_H
#include "graphm.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
//#include "graph_methods.h"


class Graph:public Graphm
{
        Q_OBJECT
//    friend void DFS(QGraphicsScene *scene,Graph &G,int v,QStringList &str);
private:
    int **matrix;
    char *vertex;
    QGraphicsEllipseItem *unit;
    QGraphicsTextItem *text,**w;
    QGraphicsLineItem **line;
public:
    Graph(int numVertex);
    ~Graph();
    void clear();
    Edge* FirstEdge(int oneVertex);
    Edge* NextEdge(Edge preEdge);
    bool isEmpty();
    int getNumVertex();
    void setLen(int len);
    int getLen();
    void setEdge(int from, int to, int weight);
    bool delEdge(QGraphicsScene *scene,int from, int to);
    int ToVertex(Edge e);
    int FromVertex(Edge e);
    int EdgesNum();
    int weight(Edge e);
    bool setVertex(int p,int value);
    bool getVertex(int p,int &item);
    char* get_vertex();
    QGraphicsEllipseItem* get_unit();
    QGraphicsLineItem** get_line();
    bool addVertex();
    void delVertex(int p,QGraphicsScene *scene);
    void update_graph(QGraphicsScene *scene);
};

#endif // GRAPH_H
