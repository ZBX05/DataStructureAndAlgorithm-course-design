#ifndef LINKSTACK_H
#define LINKSTACK_H
#include "link.h"
#include <iostream>
#include <QRectF>
#include <QPainter>
#include <QString>

class linkStack
{
private:
    Link* top;
    int size;
public:
    linkStack(int size);
    ~linkStack();
    void clear();
    bool push(const int value);
    bool pop(int& item);
    bool get_top(int& item);
    bool isEmpty();
};

#endif // LINKSTACK_H
