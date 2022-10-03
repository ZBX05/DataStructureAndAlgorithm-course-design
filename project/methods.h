#ifndef METHODS_H
#define METHODS_H
#include "arrlist.h"
#include "linkstack.h"
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include "dialog_arrlist_edit.h"
#include "dialog_arrlist_append.h"
#include "dialog_arrlist_insert.h"
#include "dialog_arrlist_delete.h"
#include "dialog_linkstack_push.h"
#include "widget_linkstack_matching.h"

//加载顺序表
int load_arrList(QWidget *parent,arrList *al){
    QString path=QFileDialog::getOpenFileName(parent,"选择载入的文件",QDir::currentPath(),"(*.txt)");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array=file.readAll();
    QString content=QString(array);
    content=content.remove('<');
    content=content.remove('>');
    QStringList content_list=content.split(',',Qt::SkipEmptyParts);
    if(!content_list.isEmpty()){
        if(content_list.length()>al->getMaxSize())
            return -2;
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
int edit_arrList(QWidget *parent,arrList *al){
    Dialog_arrlist_edit *dialog=new Dialog_arrlist_edit(parent);
    dialog->setBox(al->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        if(al->setValue(dialog->getPos(),dialog->getValue()))
            return 1;
        else return 0;
    }
    else return 2;
    delete dialog;
}

int append_arrList(QWidget *parent,arrList *al){
    Dialog_arrlist_append *dialog=new Dialog_arrlist_append(parent);
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        if(al->append(dialog->getValue()))
            return 1;
        else return 0;
    }
    else return 2;
    delete dialog;
}

int insert_arrList(QWidget *parent,QGraphicsScene *scene,arrList *al,QLabel *info){
    Dialog_arrlist_insert* dialog=new Dialog_arrlist_insert(parent);
    dialog->setBox(al->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        info->setText("正在插入元素......");
        if(al->insert(scene,dialog->getPos(),dialog->getValue()))
            return 1;
        else return 0;
    }
    else return 2;
    delete dialog;
}

int delete_arrList(QWidget *parent,QGraphicsScene *scene,arrList *al,QLabel *info){
    Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(parent);
    dialog->setBox(al->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        info->setText("正在插入元素......");
        if(al->delete_(scene,dialog->getPos()))
            return 1;
        else return 0;
    }
    else return 2;
}

//加载链式栈
int load_linkStack(QWidget *parent,linkStack *ls){
    QString path=QFileDialog::getOpenFileName(parent,"选择载入的文件",QDir::currentPath(),"(*.txt)");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array=file.readAll();
    QString content=QString(array);
    content=content.remove('<');
    content=content.remove('>');
    QStringList content_list=content.split(',',Qt::SkipEmptyParts);
    if(!content_list.isEmpty()){
        if(content_list.length()>ls->getSize())
            return -2;
        for(int i=0;i<content_list.length();i++){
            ls->push(content_list[i].toInt(nullptr,10));
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

//链式栈入栈
int push_linkStack(QWidget *parent,linkStack *ls){
    Dialog_linkstack_push *dialog=new Dialog_linkstack_push(parent);
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        if(ls->push(dialog->getValue()))
            return 1;
        else
            return 0;
    }
    return 2;
    delete dialog;
}

//链式栈修改数据
int edit_linkStack(QWidget *parent,linkStack *ls){
    Dialog_arrlist_edit *dialog=new Dialog_arrlist_edit(parent);//复用顺序表修改数据对话框
    dialog->setBox(ls->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        if(ls->setValue(dialog->getPos(),dialog->getValue()))
            return 1;
        else return 0;
    }
    else return 2;
    delete dialog;
}

//void matching_linkStack(QWidget *parent){
//    Widget_linkstack_matching *w=new Widget_linkstack_matching();
//    QThread *thread=new QThread(parent);
//    w->moveToThread(thread);
//    thread->start();
//}

#endif // METHODS_H
