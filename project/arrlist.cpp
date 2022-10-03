#include "arrlist.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include <QEventLoop>

arrList::arrList(){
    aList=new int[0];
    unit=new QGraphicsRectItem[0];
    text=new QGraphicsTextItem[0];
    curLen=pos=0;
    //unit[0].setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    text[0].setParentItem(&unit[0]);
    text[0].setPos(unit[0].boundingRect().x(),unit[0].boundingRect().y());
    curLen=pos=0;
}

arrList::arrList(const int size)
{
    maxSize=size;
    aList=new int[size];
    unit=new QGraphicsRectItem[size];
    text=new QGraphicsTextItem[size];
    for(int i=0;i<size;i++){
        //unit[i].setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
        unit[i].setRect(-200+i*25,-200,25,25);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x(),unit[i].boundingRect().y());
    }
    curLen=pos=0;
}

arrList::~arrList(){
    delete [] aList;
    delete [] text;
    delete [] unit;
}

void arrList::clear(){
    int x,y;
    x=unit[0].x();
    y=unit[0].y();
    delete [] text;
    delete [] unit;
    delete [] aList;
    curLen=pos=0;
    aList=new int[maxSize];
    unit=new QGraphicsRectItem[maxSize];
    text=new QGraphicsTextItem[maxSize];
    for(int i=0;i<maxSize;i++){
        //unit[i].setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
        unit[i].setRect(x+i*25,y,25,25);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x(),unit[i].boundingRect().y());
    }
}

int arrList::length(){
    return curLen;
}

int arrList::getMaxSize(){
    return maxSize;
}

bool arrList::append(const int value){
    if(curLen<maxSize){
        aList[curLen]=value;
        text[curLen].setPlainText(QString::number(aList[curLen],10));
        text[curLen].setPos(unit[curLen].boundingRect().x(),unit[curLen].boundingRect().y());
        curLen++;
        return true;
    }
    return false;
}

bool arrList::insert(QGraphicsScene* scene,const int p,const int value){
    QTimer* timer=new QTimer(nullptr);
    timer->setSingleShot(true);
    QEventLoop* loop=new QEventLoop(nullptr);
    QPen pen;
    pen.setWidth(2);
    connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
    int i;
    if(curLen>=maxSize){
        delete timer;
        delete loop;
        return false;
    }
    if(p<0||p>curLen){
        delete timer;
        delete loop;
        return false;
    }
    else{
        unit[curLen].setPen(pen);
        scene->addItem(&unit[curLen]);
        for(i=curLen;i>p;i--){
            aList[i]=aList[i-1];
            timer->start(500);
            loop->exec();
            text[i].setPlainText(text[i-1].toPlainText());
        }
        aList[p]=value;
        timer->start(500);
        loop->exec();
        text[p].setPlainText(QString::number(value,10));
        curLen++;
    }
    delete timer;
    delete loop;
    return true;
}

bool arrList::delete_(QGraphicsScene* scene,const int p){
    QTimer* timer=new QTimer(nullptr);
    timer->setSingleShot(true);
    QEventLoop* loop=new QEventLoop(nullptr);
    QPen pen;
    pen.setWidth(2);
    connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
    int i;
    if(curLen<=1){
        delete timer;
        delete loop;
        return false;
    }
    if(p<0||p>curLen-1){
        delete timer;
        delete loop;
        return false;
    }
    for(i=p;i<curLen-1;i++){
        aList[i]=aList[i+1];
        timer->start(500);
        loop->exec();
        text[i].setPlainText(text[i+1].toPlainText());
    }
    curLen--;
    timer->start(500);
    loop->exec();
    scene->removeItem(&unit[curLen]);
    //text[curLen].setPlainText("");
    scene->update();

    delete timer;
    delete loop;
    return true;
}

bool arrList::setValue(const int p,const int value){
    if(curLen<=0) return false;
    if(p<0||p>curLen-1) return false;
    aList[p]=value;
    text[p].setPlainText(QString::number(value,10));
    //text[p].setPos(unit[p].boundingRect().x(),unit[p].boundingRect().y());
    return true;
}

bool arrList::getValue(const int p,int& value){
    if(curLen<=0) return false;
    if(p<0||p>curLen-1) return false;
    value=aList[p];
    return true;
}

bool arrList::getPos(int& p,const int value){
    for(int i=0;i<curLen;i++){
        if(value==aList[i]){
            pos=i;
            p=pos;
            return true;
        }
    }
    return false;
}

void arrList::bubbleSort(QLabel* info){
    bool NoSwap;
    int i,j,tmp;
    QPen pen,pen1,pen2;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    pen1.setWidth(2);
    pen1.setColor(Qt::yellow);
    pen2.setWidth(2);
    pen2.setColor(Qt::green);
    QString temp;
    QTimer* timer=new QTimer(nullptr);
    timer->setSingleShot(true);
    QEventLoop* loop=new QEventLoop(nullptr);
    connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
    info->setText("正在冒泡排序......");
    for(i=0;i<curLen;i++){
        NoSwap=true;
        unit[i].setPen(pen1);
        for(j=curLen-1;j>i;j--){
            unit[j].setPen(pen2);
            timer->start(500);
            loop->exec();
            if(aList[j]<aList[j-1]){
                tmp=aList[j];
                aList[j]=aList[j-1];
                aList[j-1]=tmp;
                NoSwap=false;
                timer->start(500);
                loop->exec();
                temp=text[j].toPlainText();
                text[j].setPlainText(text[j-1].toPlainText());
                text[j-1].setPlainText(temp);
            }
            unit[j].setPen(pen);
        }
        if(NoSwap){
            unit[i].setPen(pen);
            delete timer;
            delete loop;
            return;
        }
        unit[i].setPen(pen);
    }
    unit[curLen-1].setPen(pen);
    delete timer;
    delete loop;
}

//显示顺序表的图形化形式
void arrList::draw_arrList(QGraphicsScene* scene){
    int i=0;
    QPen pen;
    pen.setWidth(2);
    if(curLen==0)
        return;
    for(i=0;i<curLen;i++){
        unit[i].setPen(pen);
        scene->addItem(&unit[i]);
    }
}


