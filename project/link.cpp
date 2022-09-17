#include "link.h"

Link::Link(const int info, Link* next){
    value=info;
    this->next=next;
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
