#include "arrlist.h"
#include "windows.h"

arrList::arrList(){
    aList=new int[0];
    unit=new QRectF[0];
    curLen=pos=0;
}

arrList::arrList(const int size,int x,int y)
{
    maxSize=size;
    aList=new int[size];
    unit=new QRectF[size];
    for(int i=0;i<size;i++)
        unit[i].setRect(x*(i+1),y,20,20);
    curLen=pos=0;
}

arrList::~arrList(){
    delete [] aList;
    delete [] unit;
}

void arrList::clear(){
    int x,y;
    x=unit[0].x();
    y=unit[0].y();
    delete [] aList;
    delete [] unit;
    curLen=pos=0;
    aList=new int[maxSize];
    unit=new QRectF[maxSize];
    for(int i=0;i<maxSize;i++)
        unit[i].setRect(x*(i+1),y,20,20);
}

int arrList::length(){return curLen;}

bool arrList::append(const int value){
    if(curLen<maxSize){
        aList[curLen]=value;
        curLen++;
        return true;
    }
    return false;
}

bool arrList::insert(const int p,const int value){
    if(curLen>=maxSize) return false;
    if(p<0||p>curLen) return false;
    else{
        for(int i=curLen;i>p;i--){
            aList[i]=aList[i-1];
        }
        aList[p]=value;
        curLen++;
        return true;
    }
}

bool arrList::delete_(const int p){
    if(curLen<=0) return false;
    if(p<0||p>curLen-1) return false;
    for(int i=p;i<curLen-1;i++){
        aList[i]=aList[i+1];
    }
    curLen--;
    return true;
}

bool arrList::setValue(const int p,const int value){
    if(curLen<=0) return false;
    if(p<0||p>curLen-1) return false;
    aList[p]=value;
    return true;
}

bool arrList::getValue(const int p,int& value){
    if(curLen<=0) return false;
    if(p<0||p>curLen-1) return false;
    value=aList[p];
    return true;
}

bool arrList::getPos(int& p,const int value){
    for(int i=0;i<curLen;i++){
        if(value==aList[i]){
            pos=i;
            p=pos;
            return true;
        }
    }
    return false;
}

//显示顺序表的图形化形式
void arrList::draw_arrList(QPainter &p){
    int i;
    if(curLen==0)
        return;
    for(i=0;i<curLen;i++){
        p.drawRect(unit[i]);
        p.drawText(unit[i],Qt::AlignCenter,QString::number(aList[i],10),nullptr);
    }
}
