#ifndef ARRLIST_H
#define ARRLIST_H
#include <iostream>
#include <QObject>
#include <QRectF>
#include <QPainter>
#include <QString>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QLabel>
class arrList:public QObject
{
        Q_OBJECT
private:
    QGraphicsRectItem *unit;
    QGraphicsTextItem *text;
    int *aList;
    int maxSize;
    int curLen;
    int pos;
public:
    explicit arrList(QObject *parent=0);
    arrList();
    arrList(const int size);
    ~arrList();
    void clear();
    int getMaxSize();
    int length();
    bool append(const int value);
    bool insert(QGraphicsScene *scene,const int p,const int value);
    bool delete_(QGraphicsScene *scene,const int p);
    bool setValue(const int p,const int value);
    bool getValue(const int p,int &value);
    bool getPos(int& p,const int value);
    void draw_arrList(QGraphicsScene *scene);
    void bubbleSort(QLabel *info);
};

#endif // ARRLIST_H
