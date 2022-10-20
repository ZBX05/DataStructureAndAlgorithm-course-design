#include "link.h"

Link::Link(const int info,int pos,Link* next){
    value=info;
    this->next=next;
    unit1=new QGraphicsRectItem(-300,-50-pos*20,60,20,nullptr);
    text1=new QGraphicsTextItem(QString::number(value,10),unit1);
    text1->setPos(unit1->boundingRect().x(),unit1->boundingRect().y());
    unit2=new QGraphicsRectItem(-300+pos*80,0,40,20,nullptr);
    text2=new QGraphicsTextItem(QString::number(value,10),unit2);
    text2->setPos(unit2->boundingRect().x(),unit2->boundingRect().y());
    unit3=new QGraphicsRectItem(-300+pos*80,20,40,20,unit2);
    point=new QGraphicsEllipseItem(-281+pos*80,28,2,2,unit3);
    point->setBrush(QBrush(Qt::black,Qt::SolidPattern));
}

Link::~Link(){
//    delete triangle;
    delete line;
    delete point;
    delete unit3;
    delete text2;
    delete unit2;
    delete text1;
    delete unit1;
}

Link::Link(Link* next){
    this->next=next;
}

Link* Link::getNext(){
    return this->next;
}

int Link::getValue(){
    return this->value;
}

void Link::setValue(int value){
    this->value=value;
}
