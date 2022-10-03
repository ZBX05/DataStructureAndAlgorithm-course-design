#include "linkstack.h"
#include "qgraphicsscene.h"
#include <QStringList>
#include <QEventLoop>
#include <QTimer>
#include <QRegularExpression>

linkStack::linkStack(int size){
    this->size=size;
    top=NULL;
    len=0;
}

linkStack::~linkStack(){
    clear();
}

int linkStack::getSize(){
    return size;
}

int linkStack::length(){
    return len;
}

void linkStack::clear(){
    while(top!=NULL){
        Link* tmp=top;
        top=top->next;
        delete tmp;
    }
    len=0;
}

bool linkStack::push(const int value){
    if(len>=size) return false;
    Link* p=new Link(value,len,NULL);
    if(top!=NULL){
        p->line=new QGraphicsLineItem(top->unit3->boundingRect().x()+40,top->unit3->boundingRect().y()+10,
                                      p->unit3->boundingRect().x()+20,p->unit3->boundingRect().y()+10,p->unit3);
//        p->triangle=new QGraphicsPolygonItem(p->line);
//        QPolygon *polygon=new QPolygon();
//        polygon->setPoints(3,top->unit3->boundingRect().x()+40,top->unit3->boundingRect().y()+10,
//                          top->unit3->boundingRect().x()+44,top->unit3->boundingRect().y()+8,
//                          top->unit3->boundingRect().x()+44,top->unit3->boundingRect().y()+12);
//        p->triangle->setPolygon(QPolygonF(*polygon));
//        p->triangle->setBrush(QBrush(Qt::black));
//        delete polygon;
    }
    else{
        p->line=new QGraphicsLineItem(p->unit3);
        p->line->setVisible(false);
//        p->triangle=new QGraphicsPolygonItem(p->line);
//        p->triangle->setVisible(false);
//        p->point->setVisible(false);
    }
    p->next=top;
    top=p;
    len++;
    return true;
}

bool linkStack::pop(int& item){
    if(size==0||len==0) return false;
    item=top->value;
    Link* tmp=top->next;
    delete top;
    top=tmp;
    len--;
    return true;
}

bool linkStack::getTop(int& item){
    if(size==0) return false;
    item=top->value;
    return true;
}

bool linkStack::isEmpty(){
    if(top==NULL||len==0) return true;
    else return false;
}

bool linkStack::setValue(const int p,const int value){
    if(p>size-1) return false;
    Link* q=top;
    for(int i=0;i<len-p-1;i++){
        q=q->next;
    }
    q->value=value;
    q->text1->setPlainText(QString::number(value,10));
    q->text2->setPlainText(QString::number(value,10));
    return true;
}

bool linkStack::delete_(const int p){
    if(len==0) return false;
    if(p>len-1) return false;
    Link *a,*b;
    if(p==0){
        a=top->next;
        delete top;
        top=a;
        len--;
        return true;
    }
    a=top;
    b=top;
    for(int i=0;i<p;i++){
        b=a;
        a=a->next;
    }
    if(p!=len-1&&a->next!=NULL){
        b->next=a->next;
        delete a;
    }
    else if(p==len-1&&a->next==NULL){
        b->next=NULL;
        delete a;
    }
    return true;
}

bool linkStack::brackets_matching(QGraphicsScene *scene,QString *string){
    QStringList str;
    str=string->split("");
    QTimer *timer=new QTimer(nullptr);
    timer->setSingleShot(true);
    QEventLoop *loop=new QEventLoop(nullptr);
    QGraphicsRectItem *unit=new QGraphicsRectItem[str.length()];
    QGraphicsTextItem *text=new QGraphicsTextItem[str.length()];
    QPen pen;
    pen.setWidth(2);
    connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
    for(int i=1;i<str.length()-1;i++){
        unit[i].setRect(i*25,-200,25,25);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x(),unit[i].boundingRect().y());
        text[i].setPlainText(str[i]);
        unit[i].setPen(pen);
        scene->addItem(&unit[i]);
    }
    timer->start(1000);
    loop->exec();
    for(int i=1;i<str.length()-1;i++){
        pen.setColor(Qt::green);
        unit[i].setPen(pen);
        if(str[i]=="{"||str[i]=="["||str[i]=="("){
            if(str[i]=="{"){
                this->push(3);
                this->top->text1->setPlainText("{");
                this->top->text2->setPlainText("{");
            }
            else if(str[i]=="["){
                this->push(2);
                this->top->text1->setPlainText("[");
                this->top->text2->setPlainText("[");
            }
            else{
                this->push(1);
                this->top->text1->setPlainText("(");
                this->top->text2->setPlainText("(");
            }
            this->draw_linkStack(scene);
        }
        else if(str[i]=="}"||str[i]=="]"||str[i]==")"){
            if(this->len==0){
                pen.setColor(Qt::red);
                unit[i].setPen(pen);
                timer->start(2000);
                loop->exec();
                delete timer;
                delete loop;
                delete [] text;
                delete [] unit;
                return false;
            }
            int item;
            this->getTop(item);
            if(item==3&&str[i]!="}"){
                pen.setColor(Qt::red);
                unit[i].setPen(pen);
                timer->start(2000);
                loop->exec();
                delete timer;
                delete loop;
                delete [] text;
                delete [] unit;
                return false;
            }
            else if(item==2&&str[i]!="]"){
                pen.setColor(Qt::red);
                unit[i].setPen(pen);
                timer->start(2000);
                loop->exec();
                delete timer;
                delete loop;
                delete [] text;
                delete [] unit;
                return false;
            }
            else if(item==1&&str[i]!=")"){
                pen.setColor(Qt::red);
                unit[i].setPen(pen);
                timer->start(2000);
                loop->exec();
                delete timer;
                delete loop;
                delete [] text;
                delete [] unit;
                return false;
            }
            this->pop(item);
            this->draw_linkStack(scene);
        }
        timer->start(1000);
        loop->exec();
        pen.setColor(Qt::black);
        unit[i].setPen(pen);
    }
    if(this->len!=0){
        delete timer;
        delete loop;
        delete [] text;
        delete [] unit;
        return false;
    }
    delete timer;
    delete loop;
    delete [] text;
    delete [] unit;
    return true;
}

bool linkStack::expression_calculate(QGraphicsScene *scene,QString *string,int &value){
    QStringList str,tmp,expression;
    tmp=string->split("");
    int i=1;
    while(i<tmp.length()-1){
        if(tmp[i]=="+"||tmp[i]=="-"||tmp[i]=="*"||tmp[i]=="/"||tmp[i]=="("||tmp[i]==")"){
            str.append(tmp[i]);
            i++;
        }
        else{
            int j=i;
            QString num;
            while(tmp[j]!="+"&&tmp[j]!="-"&&tmp[j]!="*"&&tmp[j]!="/"&&tmp[j]!="("&&tmp[j]!=")"){
                if(j>=tmp.length()-1)
                    break;
                num.append(tmp[j]);
                j++;
            }
            str.append(num);
            i=j;
        }
    }
    for(int i=0;i<str.length();i++){
        qDebug()<<i;
        qDebug()<<str[i];
        if(str[i]=="+"||str[i]=="-"||str[i]=="*"||str[i]=="/"||str[i]=="("||str[i]==")"){
            if(this->length()==0)
                this->push(str[i]=="+"?10:str[i]=="-"?11:str[i]=="*"?20:str[i]=="/"?21:str[i]=="("?30:0);
            else{
                int item;
                int op_code=str[i]=="+"?10:str[i]=="-"?11:str[i]=="*"?20:str[i]=="/"?21:str[i]=="("?30:0;
                this->getTop(item);
                if(op_code/10>item/10)
                    this->push(op_code);
                else{
                    int op;
                    if(op_code==0){
                        if(this->length()==0)
                            return false;
                        else{
                            this->pop(op);
                            while(op!=30){
                                expression.append(op==10?"+":op==11?"-":op==20?"*":"/");
                                if(this->length()==0)
                                    return false;
                                this->pop(op);
                            }
                        }
                    }
                    else{
                        if(this->length()!=0&&this->top->value!=30&&item/10>=op_code/10){
                            this->pop(op);
                            while(op/10>=op_code/10&&this->length()!=0&&this->top->value!=30){
                                expression.append(op==10?"+":op==11?"-":op==20?"*":"/");
                                this->pop(op);
                            }
                            expression.append(op==10?"+":op==11?"-":op==20?"*":"/");
                        }
                        this->push(op_code);
                    }
                }
            }
        }
        else
            expression.append(str[i]);
    }
    while(this->length()!=0){
        int item;
        this->pop(item);
        if(item==30)
            return false;
        expression.append(item==10?"+":item==11?"-":item==20?"*":"/");
    }
    this->clear();
    QTimer *timer=new QTimer(nullptr);
    timer->setSingleShot(true);
    QEventLoop *loop=new QEventLoop(nullptr);
    QGraphicsRectItem *unit=new QGraphicsRectItem[expression.length()];
    QGraphicsTextItem *text=new QGraphicsTextItem[expression.length()];
    QPen pen;
    pen.setWidth(2);
    connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
    for(int i=0;i<expression.length();i++){
        unit[i].setRect(i*25,-200,25,25);
        text[i].setParentItem(&unit[i]);
        text[i].setPos(unit[i].boundingRect().x(),unit[i].boundingRect().y());
        text[i].setPlainText(expression[i]);
        unit[i].setPen(pen);
        scene->addItem(&unit[i]);
    }
    timer->start(1000);
    loop->exec();
    for(int i=0;i<expression.length();i++){
        pen.setColor(Qt::green);
        unit[i].setPen(pen);
        if(expression[i]=="+"||expression[i]=="-"||expression[i]=="*"||expression[i]=="/"){
            int num1,num2;
            if(this->length()==0){
                pen.setColor(Qt::red);
                unit[i].setPen(pen);
                timer->start(2000);
                loop->exec();
                delete timer;
                delete loop;
                delete [] text;
                delete [] unit;
                return false;
            }
            this->pop(num2);
            this->pop(num1);
            this->push(expression[i]=="+"?(num1+num2):expression[i]=="-"?(num1-num2):expression[i]=="*"?(num1*num2):num1/num2);
        }
        else{
            this->push(expression[i].toInt(nullptr,10));
        }
        this->draw_linkStack(scene);
        timer->start(1000);
        loop->exec();
        pen.setColor(Qt::black);
        unit[i].setPen(pen);
    }
    timer->start(2000);
    loop->exec();
    this->getTop(value);
    delete timer;
    delete loop;
    delete [] text;
    delete [] unit;
    return true;
}

void linkStack::draw_linkStack(QGraphicsScene *scene){
    Link *p=top;
    QPen pen,pen_,pen__;
    pen.setWidth(2);
    pen_.setWidth(2);
    pen__.setWidth(4);
    while(p!=NULL){
        p->unit1->setPen(pen);
        p->unit2->setPen(pen);
        p->unit3->setPen(pen);
        scene->addItem(p->unit1);
        scene->addItem(p->unit2);
        p->point->setPen(pen__);
        scene->addItem(p->unit3);
        p->line->setPen(pen_);
        scene->addItem(p->line);
        p=p->next;
    }
}
