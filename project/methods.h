#ifndef METHODS_H
#define METHODS_H
#include "arrlist.h"
#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include "dialog_arrlist_edit.h"
#include "dialog_arrlist_append.h"

//加载顺序表
int load_arrList(QWidget* parent,arrList* al){
    QString path=QFileDialog::getOpenFileName(parent,"选择载入的文件",QDir::currentPath(),"(*.txt)");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array=file.readAll();
    QString content=QString(array);
    content=content.remove('<');
    content=content.remove('>');
    QStringList content_list=content.split(',',Qt::SkipEmptyParts);
    if(!content_list.isEmpty()){
        for(int i=0;i<content_list.length();i++){
            al->append(content_list[i].toInt(nullptr,10));
        }
        return 1;
    }
    else{
        if(path!="")
            return 0;
        if(path=="")
            return 2;//取消
    }
    return -1;
}

//顺序表修改数据
bool edit_arrList(QWidget* parent,arrList* al){
    Dialog_arrlist_edit* dialog=new Dialog_arrlist_edit(parent);
    dialog->setBox(al->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        al->setValue(dialog->getPos(),dialog->getValue());
        return true;
    }
    else return false;
    delete dialog;
}

bool append_arrList(QWidget* parent,arrList* al){
    Dialog_arrlist_append* dialog=new Dialog_arrlist_append(parent);
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        al->append(dialog->getValue());
        return true;
    }
    else return false;
    delete dialog;
}

#endif // METHODS_H
