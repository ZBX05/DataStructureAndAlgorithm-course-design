#ifndef ARRLIST_H
#define ARRLIST_H
#include <iostream>
#include <QRectF>
#include <QPainter>
#include <QString>
class arrList
{
private:
    QRectF* unit;
    int* aList;
    int maxSize;
    int curLen;
    int pos;
public:
    arrList();
    arrList(const int size,int x,int y);
    ~arrList();
    void clear();
    int length();
    bool append(const int value);
    bool insert(const int p,const int value);
    bool delete_(const int p);
    bool setValue(const int p,const int value);
    bool getValue(const int p,int& value);
    bool getPos(int& p,const int value);
    void draw_arrList(QPainter &p);
};

#endif // ARRLIST_H
