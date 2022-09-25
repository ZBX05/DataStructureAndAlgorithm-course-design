#include "linkstack.h"
#include "qgraphicsscene.h"

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

void linkStack::clear(){
    while(top!=NULL){
        Link* tmp=top;
        top=top->next;
        delete tmp;
    }
    size=0;
    len=0;
}

bool linkStack::push(const int value){
    Link* p=new Link(value,len,NULL);
    p->next=top;
    top=p;
    len++;
    return true;
}

bool linkStack::pop(int& item){
    if(size==0) return false;
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
    if(size==0) return false;
    if(p>size-1) return false;
    Link* q=top;
    for(int i=0;i<p;i++){
        q=q->next;
    }
    q->value=value;
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

void linkStack::draw_linkStack(QGraphicsScene *scene){
    Link *p=top;
    QPen pen;
    pen.setWidth(2);
    while(p!=NULL){
        p->unit1->setPen(pen);
        p->unit2->setPen(pen);
        p->unit3->setPen(pen);
        scene->addItem(p->unit1);
        scene->addItem(p->unit2);
//        scene->addItem(p->unit3);
        p=p->next;
    }
}
