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

int insert_arrList(QWidget *parent,QGraphicsScene *scene,arrList *al,QLabel *info,int step){
    Dialog_arrlist_insert* dialog=new Dialog_arrlist_insert(parent);
    dialog->setBox(al->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        info->setText("正在插入元素......");
        if(al->insert(scene,dialog->getPos(),dialog->getValue(),step))
            return 1;
        else return 0;
    }
    else return 2;
    delete dialog;
}

int delete_arrList(QWidget *parent,QGraphicsScene *scene,arrList *al,QLabel *info,int step){
    Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(parent);
    dialog->setBox(al->length());
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        info->setText("正在插入元素......");
        if(al->delete_(scene,dialog->getPos(),step))
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
int load_Graph(QWidget *parent,QGraphicsScene *scene,Graph *gh,int size){
    QString path=QFileDialog::getOpenFileName(parent,"选择载入的文件",QDir::currentPath(),"(*.txt)");
    if(path=="")
        return 2;//取消
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
    QRegularExpression Separator = QRegularExpression("\r\n");
    QStringList content_list=content.split(Separator,Qt::SkipEmptyParts);
    int start_size=content_list[0].toInt(nullptr,10);
    if(start_size>size)
        return -2;
    content_list.removeFirst();
    if(!content_list.isEmpty()){
        gh->setLen(start_size);
        QStringList list_1=content_list[0].split(',');
        goto next;
back:
        for(int i=0;i<list_1.length();i+=3){
            if(list_1[i].toInt(nullptr,10)>=start_size||list_1[i+1].toInt(nullptr,10)>=start_size)
                return -2;
            gh->setEdge(list_1[i].toInt(nullptr,10),list_1[i+1].toInt(nullptr,10),list_1[i+2].toInt(nullptr,10));
        }
        goto end;
next:
        content_list.removeFirst();
        content_list[0].remove('[');
        content_list[0].remove(']');
        if(!content_list[0].isEmpty()){
            QStringList list_2=content_list[0].split(',');
            for(int i=0;i<list_2.length();i++){
                if(list_2[i].toInt(nullptr,10)>=start_size)
                    return -2;
                gh->delVertex(list_2[i].toInt(nullptr,10),scene);
            }
        }
        content_list.removeFirst();
        if(!content_list.isEmpty()){
            content_list[0].remove('(');
            content_list[0].remove(')');
            QStringList list_3=content_list[0].split(',');
            for(int i=0;i<list_3.length();i+=3){
                if(list_3[i].toInt(nullptr,10)>=start_size||gh->get_vertex()[list_3[i].toInt(nullptr,10)]==0||list_3[i+1].toInt(nullptr,10)<=-600||
                        list_3[i+1].toInt(nullptr,10)>=140||list_3[i+2].toInt(nullptr,10)<=-330||list_3[i+2].toInt(nullptr,10)>=310)
                    return -1;
                gh->get_unit()[list_3[i].toInt(nullptr,10)].setRect(list_3[i+1].toFloat(nullptr),list_3[i+2].toFloat(nullptr),40,40);
                gh->get_text()[list_3[i].toInt(nullptr,10)].setPos(list_3[i+1].toFloat(nullptr)+10,list_3[i+2].toFloat(nullptr)+10);
            }
        }
        goto back;
end:
        return 1;
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

//保存顺序表
bool save_arrList(QWidget *parent,arrList *al){
    QString name=QFileDialog::getSaveFileName(parent,"选择保存文件的位置",QDir::currentPath(),"(*.txt)");
    QFile file(name);
    if(!file.open((QIODevice::WriteOnly|QIODevice::Text))){
        return false;
    }
    QTextStream textStream(&file);
    QString content="<";
    int value;
    for(int i=0;i<al->length();i++){
        al->getValue(i,value);
        content.append(QString::number(value));
        if(i!=al->length()-1)
            content.append(',');
        else
            content.append('>');
    }
    textStream<<content;
    file.close();
    return true;
}

//保存链式栈
bool save_linkStack(QWidget *parent,linkStack *ls){
    QString name=QFileDialog::getSaveFileName(parent,"选择保存文件的位置",QDir::currentPath(),"(*.txt)");
    QFile file(name);
    if(!file.open((QIODevice::WriteOnly|QIODevice::Text))){
        return false;
    }
    QTextStream textStream(&file);
    QStringList content;
    content.append(">");
    int item;
    Link *p=ls->getTopPointer();
    for(int i=0;i<ls->length();i++){
        item=p->getValue();
        content.append(QString::number(item,10));
        if(i!=ls->length()-1)
            content.append(",");
        else
            content.append("<");
        p=p->getNext();
    }
    QString content_str="";
    for(int i=content.length()-1;i>=0;i--)
        content_str.append(content[i]);
    textStream<<content_str;
    file.close();
    return true;
}

//保存图
bool save_Graph(QWidget *parent,Graph *gh){
    QString name=QFileDialog::getSaveFileName(parent,"选择保存文件的位置",QDir::currentPath(),"(*.txt)");
    QFile file(name);
    if(!file.open((QIODevice::WriteOnly|QIODevice::Text))){
        return false;
    }
    QTextStream textStream(&file);
    QString content="";
    QString str_0="{";
    QString str_1="[";
    QString str_2="";
    content.append(QString::number(gh->getLen(),10));
    content.append("\n");
    for(int i=0;i<gh->getLen();i++){
        if(gh->get_vertex()[i]!=0){
            for(int j=0;j<i;j++){
                if(gh->get_matrix()[i][j]!=0){
                    if(str_0!="{")
                        str_0.append(',');
                    str_0.append('<');
                    str_0.append(QString::number(i,10));
                    str_0.append(',');
                    str_0.append(QString::number(j,10));
                    str_0.append(',');
                    str_0.append(QString::number(gh->get_matrix()[i][j],10));
                    str_0.append('>');
                }
            }
            if(str_2!="")
                str_2.append(",");
            str_2.append('(');
            str_2.append(QString::number(i,10));
            str_2.append(',');
            str_2.append(QString::number(gh->get_unit()[i].boundingRect().x(),'f',2));
            str_2.append(',');
            str_2.append(QString::number(gh->get_unit()[i].boundingRect().y(),'f',2));
            str_2.append(')');
        }
        else{
            if(str_1!="[")
                str_1.append(',');
            str_1.append(QString::number(i,10));
        }
    }
    str_0.append("}\n");
    str_1.append("]\n");
    content.append(str_0);
    content.append(str_1);
    content.append(str_2);
    textStream<<content;
    file.close();
    return true;
}
#endif // METHODS_H
