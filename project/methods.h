#ifndef METHODS_H
#define METHODS_H
#include "arrlist.h"
#include "linkstack.h"
#include "graph.h"
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include <QRegularExpression>
#include "dialog_arrlist_edit.h"
#include "dialog_arrlist_append.h"
#include "dialog_arrlist_insert.h"
#include "dialog_arrlist_delete.h"
#include "dialog_linkstack_push.h"
#include "dialog_graph_editedge.h"
#include "dialog_graph_delete.h"


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

//加载图
int load_Graph(QWidget *parent,Graph *gh,int size){
    QString path=QFileDialog::getOpenFileName(parent,"选择载入的文件",QDir::currentPath(),"(*.txt)");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array=file.readAll();
    QString content=QString(array);
    if(content.isEmpty())
        return 0;
    content.remove('{');
    content.remove('}');
    content.remove('<');
    content.remove('>');
    QRegularExpression Separator = QRegularExpression("\r\n|,");
    QStringList content_list=content.split(Separator,Qt::SkipEmptyParts);
    int start_size=content_list[0].toInt(nullptr,10);
    if(start_size>size)
        return -2;
    content_list.removeFirst();
    if(!content_list.isEmpty()){
        gh->setLen(start_size);
        for(int i=0;i<content_list.length();i+=3){
            if(content_list[i].toInt(nullptr,10)>=start_size||content_list[i].toInt(nullptr,10)>=start_size)
                return -2;
            gh->setEdge(content_list[i].toInt(nullptr,10),content_list[i+1].toInt(nullptr,10),content_list[i+2].toInt(nullptr,10));
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

//删除节点
bool delVertex_Graph(QWidget *parent,QGraphicsScene *scene,Graph *gh){
    Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(parent);
    dialog->setBox(gh->get_vertex(),gh->getLen());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        char *c=gh->get_vertex();
        QString str=dialog->getVertexPos();
        for(int i=0;i<gh->getLen();i++){
            if(str[0]==(QChar)c[i]){
                gh->delVertex(i,scene);
                return true;
                break;
            }
        }
    }
    return false;
    delete dialog;
}

//添加/修改边
int editEdge_Graph(QWidget *parent,Graph *gh){
    Dialog_graph_editedge *dialog=new Dialog_graph_editedge(parent);
    dialog->setBox(gh->get_vertex(),gh->getLen());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        QString from,to;
        int weight,p1,p2;
        char *c=gh->get_vertex();
        dialog->getPos(from,to);
        if(from==to)
            return 0;
        for(int i=0;i<gh->getLen();i++){
            if(c[i]==from)
                p1=i;
            if(c[i]==to)
                p2=i;
        }
        weight=dialog->getValue();
        if(weight==0)
            return -1;
        gh->setEdge(p1,p2,weight);
        return 1;
    }
    else
        return 2;
    delete dialog;
}

//删除边
int delEdge_Graph(QWidget *parent,QGraphicsScene *scene,Graph *gh){
    Dialog_graph_delete *dialog=new Dialog_graph_delete(parent);
    dialog->setBox(gh->get_vertex(),gh->getLen());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        QString from,to;
        int p1,p2;
        char *c=gh->get_vertex();
        dialog->getPos(from,to);
        if(from==to)
            return 0;
        for(int i=0;i<gh->getLen();i++){
            if(c[i]==from)
                p1=i;
            if(c[i]==to)
                p2=i;
        }
        if(gh->delEdge(scene,p1,p2))
            return 1;
        else
            return -1;
    }
    else
        return 2;
}

#endif // METHODS_H
