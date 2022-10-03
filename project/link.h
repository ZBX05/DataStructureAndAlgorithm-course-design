#ifndef LINK_H
#define LINK_H
#include <iostream>
#include <QObject>
#include <QRectF>
#include <QPainter>
#include <QString>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QEventLoop>

class Link:public QObject
{
        Q_OBJECT
    friend class linkStack;
private:
    int value;
    Link *next;
    QGraphicsRectItem *unit1,*unit2,*unit3;
    QGraphicsTextItem *text1,*text2;
    QGraphicsEllipseItem *point;
    QGraphicsLineItem *line;
    QGraphicsPolygonItem *triangle;
public:
    explicit Link(QObject *parent);
    Link(const int info,const int pos,Link *next=NULL);
    Link(Link *next=NULL);
    ~Link();
    Link *getNext();
    int getValue();
    void setValue(int value);
};

#endif // LINK_H
