#include "graph.h"

Graph::Graph(int numVertex):Graphm(numVertex){
    matrix=(int**)new int* [numVertex];
    line=(QGraphicsLineItem**)new QGraphicsLineItem* [numVertex];
    vertex=new char[numVertex];
    unit=new QGraphicsEllipseItem[numVertex];
    matrix_unit=(QGraphicsRectItem**)new QGraphicsRectItem* [numVertex];
    text=new QGraphicsTextItem[numVertex];
    w=(QGraphicsTextItem**)new QGraphicsTextItem* [numVertex];
    matrix_text=(QGraphicsTextItem**)new QGraphicsTextItem* [numVertex];
    tag=new int[numVertex];
    for (int i = 0; i < numVertex; i++){
        if(i<26)
            vertex[i]=65+i;
        else
            vertex[i]=char(i-25);
        matrix[i]=new int[numVertex];
        line[i]=new QGraphicsLineItem[numVertex];
        matrix_unit[i]=new QGraphicsRectItem[numVertex];
        w[i]=new QGraphicsTextItem[numVertex];
        matrix_text[i]=new QGraphicsTextItem[numVertex];
        unit[i].setRect(-500+120*(i%5),-300+150*(i/5)+(i%5==1?(i%5)*(-30):i%5==3?(i%5)*30:0),40,40);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x()+10,unit[i].boundingRect().y()+10);
        tag[i]=0;
    }
    for (int i = 0; i < numVertex; i++)
        for (int j = 0; j < numVertex; j++){
            if(i==j)
                matrix[i][j]=INFINITY;
            else
                matrix[i][j]=0;
            matrix_unit[i][j].setRect(200+j*20,0+i*20,20,20);
            w[i][j].setParentItem(&line[i][j]);
            w[i][j].setPos((unit[i].boundingRect().x()+20+unit[j].boundingRect().x()+20)/2,
                           (unit[i].boundingRect().y()+20+unit[j].boundingRect().y()+20)/2);
            matrix_text[i][j].setParentItem(&matrix_unit[i][j]);
            if(i==j)
                matrix_text[i][j].setPlainText("∞");
            else
                matrix_text[i][j].setPlainText(QString::number(matrix[i][j],10));
            matrix_text[i][j].setPos(matrix_unit[i][j].boundingRect().x(),matrix_unit[i][j].boundingRect().y());
        }
}

Graph::~Graph(){
    for(int i=0;i<numVertex;i++){
        delete [] matrix[i];
        delete [] w[i];
        delete [] matrix_text[i];
        delete [] matrix_unit[i];
    }
    delete [] w;
    delete [] matrix;
    delete [] matrix_text;
    delete [] matrix_unit;
    for(int i=0;i<numVertex;i++)
        delete [] line[i];
    delete [] line;
    delete [] vertex;
    delete [] text;
    delete [] unit;
}

void Graph::clear(){
    for(int i=0;i<numVertex;i++){
        delete [] matrix[i];
        delete [] w[i];
        delete [] matrix_text[i];
        delete [] matrix_unit[i];
    }
    delete [] w;
    delete [] matrix;
    delete [] matrix_text;
    delete [] matrix_unit;
    for(int i=0;i<numVertex;i++)
        delete [] line[i];
    delete [] line;
    delete [] vertex;
    delete [] text;
    delete [] unit;
    matrix=(int**)new int* [numVertex];
    line=(QGraphicsLineItem**)new QGraphicsLineItem* [numVertex];
    vertex=new char[numVertex];
    unit=new QGraphicsEllipseItem[numVertex];
    matrix_unit=(QGraphicsRectItem**)new QGraphicsRectItem* [numVertex];
    text=new QGraphicsTextItem[numVertex];
    w=(QGraphicsTextItem**)new QGraphicsTextItem* [numVertex];
    matrix_text=(QGraphicsTextItem**)new QGraphicsTextItem* [numVertex];
    tag=new int[numVertex];
    for (int i = 0; i < numVertex; i++){
        if(i<26)
            vertex[i]=65+i;
        else
            vertex[i]=char(i-25);
        matrix[i]=new int[numVertex];
        line[i]=new QGraphicsLineItem[numVertex];
        matrix_unit[i]=new QGraphicsRectItem[numVertex];
        w[i]=new QGraphicsTextItem[numVertex];
        matrix_text[i]=new QGraphicsTextItem[numVertex];
        unit[i].setRect(-500+120*(i%5),-300+150*(i/5)+(i%5==1?(i%5)*(-30):i%5==3?(i%5)*30:0),40,40);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x()+10,unit[i].boundingRect().y()+10);
        tag[i]=0;
    }
    for (int i = 0; i < numVertex; i++)
        for (int j = 0; j < numVertex; j++){
            if(i==j)
                matrix[i][j]=INFINITY;
            else
                matrix[i][j]=0;
            matrix_unit[i][j].setRect(200+j*20,0+i*20,20,20);
            w[i][j].setParentItem(&line[i][j]);
            w[i][j].setPos((unit[i].boundingRect().x()+20+unit[j].boundingRect().x()+20)/2,
                           (unit[i].boundingRect().y()+20+unit[j].boundingRect().y()+20)/2);
            matrix_text[i][j].setParentItem(&matrix_unit[i][j]);
            if(i==j)
                matrix_text[i][j].setPlainText("∞");
            else
                matrix_text[i][j].setPlainText(QString::number(matrix[i][j],10));
            matrix_text[i][j].setPos(matrix_unit[i][j].boundingRect().x(),matrix_unit[i][j].boundingRect().y());
        }
    len=0;
}

bool Graph::isEmpty(){
    if(len<=0) return true;
    for(int i=0;i<len;i++){
        if(vertex[i]!=0)
            return false;
    }
    return true;
}

int Graph::getNumVertex(){
    return numVertex;
}

void Graph::setLen(int len){
    this->len=len;
    for(int i=0;i<len;i++)
        text[i].setPlainText(QString(vertex[i]));
}

int Graph::getLen(){
    return len;
}

Edge* Graph::FirstEdge(int oneVertex){
    Edge *myEdge=new Edge();
    myEdge->from = oneVertex;
    for (int i = 0; i < len; i++){
        if (matrix[oneVertex][i] != 0){
            myEdge->to = i;
            myEdge->weight = matrix[oneVertex][i];
            break;
        }
    }
    return myEdge;
}

Edge* Graph::NextEdge(Edge preEdge){
    Edge *myEdge=new Edge();
    myEdge->from = preEdge.from;
    if (preEdge.to < len){
        for (int i = preEdge.to + 1; i < len; i++){
            if (matrix[preEdge.from][i] != 0){
                myEdge->to = i;
                myEdge->weight = matrix[preEdge.from][i];
                break;
            }
        }
    }
    return myEdge;
}

void Graph::setEdge(int from, int to, int weight){
    if(matrix[from][to]<=0){
        numEdge++;
        Indegree[to]++;
        Indegree[from]++;
    }
    line[from][to].setLine(unit[from].boundingRect().x()+20,unit[from].boundingRect().y()+20,
                           unit[to].boundingRect().x()+20,unit[to].boundingRect().y()+20);
    line[to][from].setLine(unit[from].boundingRect().x()+20,unit[from].boundingRect().y()+20,
                           unit[to].boundingRect().x()+20,unit[to].boundingRect().y()+20);

    matrix[from][to]=weight;
    matrix[to][from]=weight;
    matrix_text[from][to].setPlainText(QString::number(weight,10));
    matrix_text[to][from].setPlainText(QString::number(weight,10));
    w[from][to].setPlainText(QString::number(weight,10));
    w[to][from].setPlainText(QString::number(weight,10));
}

bool Graph::delEdge(QGraphicsScene *scene,int from, int to){
    if(matrix[from][to]!=0){
        numEdge--;
        Indegree[to]--;
        Indegree[from]--;
        matrix[from][to]=0;
        matrix[to][from]=0;
        matrix_text[from][to].setPlainText("0");
        matrix_text[to][from].setPlainText("0");
        from>to?scene->removeItem(&line[from][to]):scene->removeItem(&line[to][from]);
    }
    else
        return false;
    return true;
}

int Graph::ToVertex(Edge e){
    return e.to;
}
int Graph::FromVertex(Edge e){
    return e.from;
}
int Graph::EdgesNum(){
    int e = 0;
    for (int i = 0; i < len; i++)
        for (int j = 0; j < i; j++)
                if (matrix[i][j] != 0)
                    e++;
    return e;
}
int Graph::weight(Edge e){
    return matrix[e.from][e.to];
}

bool Graph::setVertex(int p,int value){
    if(p<0||p>=numVertex) return false;
    vertex[p]=value;
    text[p].setPlainText(QString::number(vertex[p],10));
    return true;
}

bool Graph::getVertex(int p,int &item){
    if(p<0||p>=len) return false;
    item=vertex[p];
    return true;
}

char* Graph::get_vertex(){
    return vertex;
}

QGraphicsEllipseItem* Graph::get_unit(){
    return unit;
}

QGraphicsLineItem** Graph::get_line(){
    return line;
}

QGraphicsTextItem* Graph::get_text(){
    return text;
}

QGraphicsTextItem** Graph::get_w(){
    return w;
}

int** Graph::get_matrix(){
    return matrix;
}

bool Graph::addVertex(){
    if(len>=numVertex)
        return false;
    for(int i=0;i<len;i++){
        if(vertex[i]==0){
            if(i<26)
                vertex[i]=65+i;
            else
                vertex[i]=char(i-25);
            text[i].setPlainText(QString(vertex[i]));
            return true;
        }
    }
    text[len].setPlainText(QString(vertex[len]));
    len++;
    return true;
}

void Graph::delVertex(int p,QGraphicsScene *scene){
    Edge *e;
    for(int i=0;i<len;i++){
        if(i==p){
            vertex[p]=0;
            scene->removeItem(&unit[p]);
        }
    }
    for(e=this->FirstEdge(p);this->isEdge(*e);e=this->NextEdge(*e)){
        this->delEdge(scene,e->from,e->to);
    }
    for(int i=0;i<len;i++){
        if(matrix[i][p]!=0){
            this->delEdge(scene,i,p);
        }
    }
    (p==len-1)?len--:len-=0;
    delete e;
}

void Graph::update_graph(QGraphicsScene *scene){
    QPen pen;
    pen.setWidth(4);
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    for(int i=0;i<this->len;i++){
        for(int j=0;j<i;j++){
            if(matrix[i][j]!=0){
                line[i][j].setPen(pen);
                scene->addItem(&line[i][j]);
                scene->addItem(&w[i][j]);
            }
        }
    }
    for(int i=0;i<this->len;i++){
        if(vertex[i]!=0){
            unit[i].setPen(pen);
            unit[i].setBrush(brush);
            scene->addItem(&unit[i]);
            scene->addItem(&text[i]);
        }
    }
    for(int i=0;i<this->numVertex;i++)
        for(int j=0;j<this->numVertex;j++){
            matrix_unit[i][j].setPen(pen);
            scene->addItem(&matrix_unit[i][j]);
            scene->addItem(&matrix_text[i][j]);
        }
}
