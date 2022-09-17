#ifndef LINK_H
#define LINK_H
#include <iostream>
#include <QRectF>
#include <QPainter>
#include <QString>

class Link
{
private:
    int value;
    Link* next;
public:
    Link(const int info,Link* next=NULL);
    Link(Link* next=NULL);
    Link* getNext();
    int getValue();
};

#endif // LINK_H
