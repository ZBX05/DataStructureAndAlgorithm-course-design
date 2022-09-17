#include "linkstack.h"

linkStack::linkStack(int size){
    this->size=0;
    top=NULL;
}

linkStack::~linkStack(){
    clear();
}

void linkStack::clear(){
    while(top!=NULL){
        Link* tmp=top;
        top=top->getNext();
        delete tmp;
    }
    size=0;
}

bool linkStack::pop(int& item){
    if(size==0) return false;
    item=top->getValue();
    Link* tmp=top->getNext();
    delete top;
    top=tmp;
    size--;
    return true;
}

bool linkStack::get_top(int& item){
    if(size==0) return false;
    item=top->getValue();
    return true;
}

bool linkStack::isEmpty(){
    if(size==0&&top==NULL) return true;
    else return false;
}
