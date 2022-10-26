#ifndef LINKSTACK_H
#define LINKSTACK_H
#include "link.h"
#include <iostream>
#include <QRectF>
#include <QPainter>
#include <QString>

class linkStack:public QObject
{
        Q_OBJECT
private:
    Link* top;
    int size;
    int len;
    QGraphicsLineItem *mid;
public:
    linkStack(int size);
    ~linkStack();
    Link* getTopPointer();
    int getSize();
    int length();
    void clear();
    bool push(const int value);
    bool pop(int& item);
    bool getTop(int& item);
    bool isEmpty();
    bool setValue(const int p,const int value);
    bool insert(const int p,const int value);
    bool delete_(const int p);
    bool brackets_matching(QGraphicsScene *scene,QString *string,int step);
    bool expression_calculate(QGraphicsScene *scene,QString *string,int &value,int step);
    void draw_linkStack(QGraphicsScene *scene);
};

#endif // LINKSTACK_H
