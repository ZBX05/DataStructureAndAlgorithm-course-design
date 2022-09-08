#ifndef METHODS_H
#define METHODS_H
#include "arrlist.h"
#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

bool load_arrList(QWidget* parent,arrList* al){
    QString path=QFileDialog::getOpenFileName(parent,"选择载入的文件",QDir::currentPath(),"(*.txt)");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array=file.readAll();
    QString content=QString(array);
    content=content.remove('<');
    content=content.remove('>');
    QStringList content_list=content.split(',',Qt::SkipEmptyParts);
//    int v;
    if(!content_list.isEmpty()){
        for(int i=0;i<content_list.length();i++){
            al->append(content_list[i].toInt(nullptr,10));
//            al->getValue(i,v);
//            qDebug()<<al->length();
        }
        return true;
    }
    return false;
}

#endif // METHODS_H
