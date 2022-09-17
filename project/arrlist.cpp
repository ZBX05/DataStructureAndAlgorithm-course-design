#include "arrlist.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QtGui>

arrList::arrList(){
    aList=new int[0];
    unit=new QGraphicsRectItem[0];
    text=new QGraphicsTextItem[0];
    curLen=pos=0;
    unit[0].setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    text[0].setParentItem(&unit[0]);
    text[0].setPos(unit[0].boundingRect().x(),unit[0].boundingRect().y());
}

arrList::arrList(const int size,int x,int y)
{
    maxSize=size;
    aList=new int[size];
    unit=new QGraphicsRectItem[size];
    text=new QGraphicsTextItem[size];
    for(int i=0;i<size;i++){
        unit[i].setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
        unit[i].setRect(x+i*20,y,20,20);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x(),unit[i].boundingRect().y());
    }
    curLen=pos=0;
}

arrList::~arrList(){
    delete [] aList;
    delete [] unit;
    delete [] text;
}

void arrList::clear(){
    int x,y;
    x=unit[0].x();
    y=unit[0].y();
    delete [] aList;
    delete [] unit;
    delete [] text;
    curLen=pos=0;
    aList=new int[maxSize];
    unit=new QGraphicsRectItem[maxSize];
    text=new QGraphicsTextItem[maxSize];
    for(int i=0;i<maxSize;i++){
        unit[i].setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
        unit[i].setRect(x*(i+1),y,20,20);
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

bool arrList::insert(const int p,const int value){
    if(curLen>=maxSize) return false;
    if(p<0||p>curLen) return false;
    else{
        for(int i=curLen;i>p;i--){
            aList[i]=aList[i-1];
        }
        aList[p]=value;
        curLen++;
        return true;
    }
}

bool arrList::delete_(const int p){
    if(curLen<=0) return false;
    if(p<0||p>curLen-1) return false;
    for(int i=p;i<curLen-1;i++){
        aList[i]=aList[i+1];
    }
    curLen--;
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


