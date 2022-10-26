#ifndef GRAPH_METHODS_H
#define GRAPH_METHODS_H
#include "graph.h"
#include "arrqueue.h"
#include "dist.h"
#include <QTimer>
#include <QEventLoop>
#include <QPen>

void Visit(int v,QStringList &str){
    str.append(QString::number(v,10));
}

void DFS(Graph &G,int v,QStringList &str){
    Edge *e;
    G.Mark[v] = VISITED;
    Visit(v,str);
    for (e=G.FirstEdge(v); G.isEdge(*e); e=G.NextEdge(*e)){
        if (G.Mark[G.ToVertex(*e)] == UNVISITED)
            DFS(G,G.ToVertex(*e),str);
    }
    delete e;
}

void BFS(Graph &G,int v,QStringList &str){
    arrQueue Q(G.getNumVertex());
    Visit(v,str);
    G.Mark[v]=VISITED;
    Q.enqueue(v);
    int u;
    Edge *e;
    while (!Q.isempty()){
        Q.dequeue(u);
        for (e=G.FirstEdge(u); G.isEdge(*e); e=G.NextEdge(*e)){
            if (G.Mark[G.ToVertex(*e)] == UNVISITED){
                Visit(G.ToVertex(*e),str);
                G.Mark[G.ToVertex(*e)] = VISITED;
                Q.enqueue(G.ToVertex(*e));
            }
        }
    }
}

int minVertex(Graph &G, Dist* &D){
    int v, i;
    for (i=0; i<G.getLen(); i++)
        if (G.Mark[i]==UNVISITED&&G.get_vertex()[i]!=0) {
            v = i;
            break;
        }
    for (i = 0; i<G.getLen(); i++)
        if (G.Mark[i] == UNVISITED&&D[i].length<D[v].length&&G.get_vertex()[i]!=0)
            v = i;
    return v;
}

void AddEdgetoMST(Edge e, Edge *MST, int n){
    if (n < 0) return;
    MST[n] = e;
}

void Prim(Graph& G, int s, Edge* &MST,QStringList &str) {
    int MSTtag = 0;
    Edge *e;
    MST = new Edge[G.VerticesNum() - 1];
    Dist *D = new Dist[G.VerticesNum()];
    for (int i = 0; i < G.VerticesNum(); i++) {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = (int)INFINITY;
        D[i].pre = s;
    }
    D[s].length = 0;
    Visit(s,str);
    G.Mark[s] = VISITED;
    int v = s;
    for (int i = 0; i < G.getLen() - 1; i++) {
        if (D[v].length == INFINITY) return;
        for (e=G.FirstEdge(v); G.isEdge(*e); e=G.NextEdge(*e))
            if (G.Mark[G.ToVertex(*e)] != VISITED && (D[G.ToVertex(*e)].length > e->weight)) {
                D[G.ToVertex(*e)].length = e->weight;
                D[G.ToVertex(*e)].pre = v;
            }
        v=minVertex(G, D);
        Visit(v,str);
        G.Mark[v] = VISITED;
        Edge edge(D[v].pre, D[v].index, D[v].length);
        AddEdgetoMST(edge, MST, MSTtag++);
    }
    delete e;
}

//void Floyd(Graph& G, Dist**& D) {
//    int i, j, v;
//    Edge *e;
//    D = new Dist * [G.getLen()];
//    for (i = 0; i < G.getLen(); i++)
//        D[i] = new Dist[G.getLen()];
//    for (i = 0; i < G.getLen(); i++)
//        for (j = 0; j < G.getLen(); j++) {
//            if (i == j) {
//                D[i][j].length = 0;
//                D[i][j].pre = i;
//            }
//            else {
//                D[i][j].length = (int)INFINITY;
//                D[i][j].pre = -1;
//            }
//        }
//    for (v = 0; v < G.getLen(); v++)
//        if(G.get_vertex()[v]!=0)
//            for (e = G.FirstEdge(v); G.isEdge(*e); e = G.NextEdge(*e)) {
//                D[v][G.ToVertex(*e)].length = G.weight(*e);
//                D[v][G.ToVertex(*e)].pre = v;
//            }
//    for (v = 0; v < G.getLen(); v++)
//        for (i = 0; i < G.getLen(); i++)
//            for (j = 0; j < G.getLen(); j++)
//                if (D[i][j].length > (D[i][v].length + D[v][j].length)) {
//                    D[i][j].length = D[i][v].length + D[v][j].length;
//                    D[i][j].pre = D[v][j].pre;
//                }

//}

#endif // GRAPH_METHODS_H
