#ifndef GRAPH_METHODS_H
#define GRAPH_METHODS_H
#include "graph.h"
#include "arrqueue.h"
#include "dist.h"
#include <QLabel>
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

class MinHeap {
private:
    Dist* heapArray;
    int CurrentSize;
    int MaxSize;
    void swap(int pos_x, int pos_y) {
        Dist temp = heapArray[pos_y];
        heapArray[pos_y] = heapArray[pos_x];
        heapArray[pos_x] = temp;
    }
    void BuildHeap() {
        for (int i = CurrentSize / 2 - 1; i >= 0; i--)
            Siftdown(i);
    }
public:
    MinHeap(int n) {
        if (n < 0)
            return;
        CurrentSize = 0;
        MaxSize = n;
        heapArray = new Dist[MaxSize];
        BuildHeap();
    }
    virtual ~MinHeap() { delete[]heapArray; }
    bool isEmpty() { return CurrentSize == 0 ? true : false; }
    bool isLeaf(int pos) const { return (pos >= CurrentSize / 2) && (pos < CurrentSize); }
    int Leftchild(int pos) const { return 2 * pos + 1; }
    int Rightchild(int pos) const { return 2 * pos + 2; }
    int Parent(int pos) const { return (pos - 1) / 2; }
    bool Remove(int pos, Dist& node) {
        if (pos < 0 || pos >= CurrentSize)
            return false;
        node = heapArray[pos];
        heapArray[pos] = heapArray[--CurrentSize];
        if (heapArray[Parent(pos)] > heapArray[pos])
            Siftup(pos);
        else Siftdown(pos);
        return true;
    }
    bool Insert(const Dist& newNode) {
        if (CurrentSize == MaxSize)
            return false;
        heapArray[CurrentSize++] = newNode;
        Siftup(CurrentSize - 1);
        return true;
    }
    Dist& RemoveMin() {
        if(CurrentSize!=0) {
            swap(0, --CurrentSize);
            if (CurrentSize > 1)
                Siftdown(0);
            return heapArray[CurrentSize];
        }
    }
    void Siftup(int pos) {
        Dist temp = heapArray[pos];
        while (pos > 0 && heapArray[Parent(pos)] > temp) {
            heapArray[pos] = heapArray[Parent(pos)];
            pos = Parent(pos);
        }
        heapArray[pos] = temp;
    }
    void Siftdown(int pos) {
        int i = pos;
        int j = Leftchild(i);
        Dist temp = heapArray[i];
        while (j < CurrentSize) {
            if ((j < CurrentSize - 1) && (heapArray[j] > heapArray[j + 1]))
                j++;
            if (temp > heapArray[j]) {
                heapArray[i] = heapArray[j];
                i = j;
                j = Leftchild(j);
            }
            else break;
        }
        heapArray[i] = temp;
    }
};

void Dijkstra(QGraphicsScene *scene,QLabel *info,int step,Graph& G, int s, Dist*& D){
    int *index=new int[G.getNumVertex()];
    int ptr=0;
    QTimer *timer=new QTimer(nullptr);
    timer->setSingleShot(true);
    QEventLoop *loop=new QEventLoop(nullptr);
    Graph::connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
    QPen *pen_0=new QPen();
    pen_0->setWidth(4);
    pen_0->setColor(Qt::black);
    QPen *pen_1=new QPen();
    pen_1->setWidth(4);
    pen_1->setColor(Qt::green);
    QPen *pen_2=new QPen();
    pen_2->setWidth(4);
    pen_2->setColor(Qt::blue);
    QString str="起点到各个点的最短路径：";
    Edge *e;
    D = new Dist[G.VerticesNum()];
    for (int i = 0; i < G.VerticesNum(); i++) {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = 9999;
        D[i].pre = s;
    }
    D[s].length = 0;
    G.get_unit()[s].setPen(*pen_2);
    MinHeap H(G.EdgesNum());
    H.Insert(D[s]);
    timer->start(step);
    loop->exec();
    for (int i = 0; i < G.VerticesNum(); i++){
        bool FOUND = false;
        Dist d;
        while (!H.isEmpty()) {
            d = H.RemoveMin();
            if (G.Mark[d.index] == UNVISITED) {
                FOUND = true;
                break;
            }
        }
        if (!FOUND)
            break;
        int v = d.index;
        G.Mark[v] = VISITED;
        G.get_unit()[v].setPen(*pen_2);
        scene->update();
        index[ptr]=v;
        ptr++;
        for (e = G.FirstEdge(v); G.isEdge(*e); e = G.NextEdge(*e)) {
            if (D[G.ToVertex(*e)].length > (D[v].length + G.weight(*e))) {
                D[G.ToVertex(*e)].length = D[v].length + G.weight(*e);
                D[G.ToVertex(*e)].pre = v;
                H.Insert(D[G.ToVertex(*e)]);
                G.get_line()[e->from][e->to].setPen(*pen_1);
                G.get_line()[e->to][e->from].setPen(*pen_1);
                scene->update();
                timer->start(step);
                loop->exec();
                G.get_unit()[G.ToVertex(*e)].setPen(*pen_1);
                scene->update();
                timer->start(step);
                loop->exec();
            }
        }
        str.append(G.get_vertex()[v]);
        str.append(":");
        str.append(QString::number(D[v].length,10));
        str.append(" ");
        info->setText(str);
        timer->start(step);
        loop->exec();
        G.update_graph(scene);
        for(int i=0;i<ptr;i++){
            G.get_unit()[index[i]].setPen(*pen_2);
//            if(i>0){
//                int tmp=index[i];
//                while(1){
//                    if(D[tmp].pre!=s){
//                        G.get_line()[D[tmp].pre][tmp].setPen(*pen_2);
//                        G.get_line()[tmp][D[tmp].pre].setPen(*pen_2);
//                        tmp=D[tmp].pre;
//                    }
//                    else{
//                        G.get_line()[D[tmp].pre][tmp].setPen(*pen_2);
//                        G.get_line()[tmp][D[tmp].pre].setPen(*pen_2);
//                        break;
//                    }
//                }
//            }
//            G.get_line()[D[i].pre][D[i].index].setPen(*pen_2);
//            G.get_line()[D[i].index][D[i].pre].setPen(*pen_2);
//            for(int j=0;j<i;i++){
//                if(D[j].pre==index[i]){
//                    G.get_line()[D[i].pre][D[i].index].setPen(*pen_2);
//                    G.get_line()[D[i].index][D[i].pre].setPen(*pen_2);
//                }
//            }
        }
        scene->update();
    }
    str.append(" 算法结束！");
    info->setText(str);
    delete [] index;
    delete pen_0;
    delete pen_1;
    delete pen_2;
    delete e;
    delete loop;
    delete timer;
}


#endif // GRAPH_METHODS_H
