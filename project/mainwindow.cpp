#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrlist.h"
#include "methods.h"
#include "dialog_arrlist_load.h"
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setFixedSize(1200,700);

    scene=new QGraphicsScene(this);
    //scene->setSceneRect(-300,-250,300,250);
    scene->setSceneRect(-600,-350,1190,650);
    view=new QGraphicsView(this);
    view->resize(1200,700);
    view->setScene(scene);
    view->setAlignment(Qt::AlignCenter);
//    QPen pen;
//    pen.setWidth(2);
//    pen.setColor(QColorConstants::Black);
//    QGraphicsRectItem *rect1=new QGraphicsRectItem(-200,-200,20,20,nullptr);
//    rect1->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
//    rect1->setPen(pen);
//    scene->addItem(rect1);
//    QGraphicsRectItem *rect2=new QGraphicsRectItem(-160,-200,20,20,nullptr);
//    rect2->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
//    rect2->setPen(pen);
//    scene->addItem(rect2);
//    QGraphicsLineItem *line=new QGraphicsLineItem(nullptr);


    //复选框1
    QCheckBox *chb=new QCheckBox("轻量模式",this);
    chb->setChecked(true);
    chb->move(1100,25);

    //单选按钮1
    QRadioButton *rab1=new QRadioButton("顺序表",this);
    rab1->setChecked(true);
    rab1->move(1100,45);

    //单选按钮2
    QRadioButton *rab2=new QRadioButton("链式栈",this);
    rab2->move(1100,65);

    //单选按钮3
    QRadioButton *rab3=new QRadioButton("图",this);
    rab3->move(1100,85);

    //按钮1
    QPushButton *btn1=new QPushButton("载入",this);
    btn1->move(1080,125);

    //按钮2
    QPushButton *btn2=new QPushButton("清除",this);
    btn2->move(1080,165);


    //顶部菜单栏
    QMenuBar *meb=new QMenuBar(this);
    setMenuBar(meb);
    //菜单
    QMenu *meu1=new QMenu("操作");
    meb->addMenu(meu1);
    QMenu *arrlist_meu=new QMenu("顺序表");
    meu1->addMenu(arrlist_meu);
    QAction *edit_al=arrlist_meu->addAction("修改数据");
    QAction *append=arrlist_meu->addAction("添加元素");
    QAction *insert=arrlist_meu->addAction("🎇插入");
    QAction *delete_=arrlist_meu->addAction("🎇删除");
    QAction *sort=arrlist_meu->addAction("🎇冒泡排序");
    QMenu *linkstack_meu=new QMenu("链式栈");
    meu1->addMenu(linkstack_meu);
    QAction *push=linkstack_meu->addAction("入栈");
    QAction *pop=linkstack_meu->addAction("出栈");
    QAction *edit_ls=linkstack_meu->addAction("修改数据");
    QAction *matching=linkstack_meu->addAction("🎇括号匹配");
    QAction *calculate=linkstack_meu->addAction("🎇表达式求值");

    //底部状态栏
    QStatusBar *stBar=new QStatusBar();
    setStatusBar(stBar);
    QLabel *info= new QLabel(this);
    stBar->addWidget(info);

    //////////////////////////////////////////
    //顺序表菜单
    //修改数据
    connect(edit_al,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0){
                int code=edit_arrList(this,ArrayList);
                if(code==1)
                    info->setText("修改数据成功!");
                else if(code==0)
                    info->setText("修改数据失败！");
            }
            else
                info->setText("修改数据要求顺序表不能为空！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //添加元素
    connect(append,&QAction::triggered,[=](){
        if(rab1->isChecked()){
//            if(ArrayList->length()!=0){
                if(ArrayList->length()<ArrayList->getMaxSize()){
                    int code=append_arrList(this,ArrayList);
                    if(code==1)
                        info->setText("添加元素成功!");
                    else if(code==0)
                        info->setText("添加元素失败！");
                }
                else
                    info->setText("顺序表已满！");
//            }
//            else
//                info->setText("此处的添加操作要求顺序表不能为空！");
            ArrayList->draw_arrList(scene);
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //插入
    connect(insert,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0){
                if(ArrayList->length()<ArrayList->getMaxSize()){
                    int code=insert_arrList(this,scene,ArrayList,info);
                    if(code==1)
                        info->setText("插入元素成功！");
                    else if(code==0)
                        info->setText("插入元素失败！");
                }
                else
                    info->setText("顺序表已满！");
            }
            else
                info->setText("插入操作要求顺序表不能为空！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //删除
    connect(delete_,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0){
                int code=delete_arrList(this,scene,ArrayList,info);
                if(code==1)
                    info->setText("删除元素成功！");
                else if(code==0)
                    info->setText("删除元素失败");
            }
            else
                info->setText("删除操作要求顺序表不能为空！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //冒泡排序
    connect(sort,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0){
                ArrayList->bubbleSort(info);
                info->setText("现在顺序表是有序的了！");
            }
            else
                info->setText("冒泡排序要求顺序表不能为空！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });
    //////////////////////////////////////////
    //链式栈菜单
    //入栈
    connect(push,&QAction::triggered,[=](){
        if(rab2->isChecked()){
            int code=push_linkStack(this,LinkStack);
            if(code==1){
                LinkStack->draw_linkStack(scene);
                info->setText("元素入栈成功！");
            }
            else if(code==0)
                info->setText("元素入栈失败！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //出栈
    connect(pop,&QAction::triggered,[=](){
       if(rab2->isChecked()){
           int item;
           if(LinkStack->pop(item))
               info->setText("元素出栈成功！");
           else
               info->setText("栈已经为空栈！");
       }
    });

    //修改数据
    connect(edit_ls,&QAction::triggered,[=](){
        if(rab2->isChecked()){
            if(LinkStack->length()!=0||LinkStack->getSize()!=0){
                int code=edit_linkStack(this,LinkStack);
                if(code==1)
                    info->setText("修改数据成功!");
                else if(code==0)
                    info->setText("修改数据失败！");
            }
            else
                info->setText("修改数据要求顺序表不能为空！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //括号匹配
    connect(matching,&QAction::triggered,[=](){
        if(rab2->isChecked()){
            w->setWindowModality(Qt::WindowModal);
            w->setWindowFlag(Qt::Widget);
            w->show();
back1:
            int value;
            int code=w->run(1,value);
            if(code==1){
                info->setText("括号匹配成功！");
                w->close();
            }
            else if(code==0){
                info->setText("括号匹配失败！该字符串没有规范地使用括号！");
                w->close();
            }
            else if(code==2){
                info->setText("字符串长度不正确！");
                goto back1;
            }
            else if(code==3)
                w->close();
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //表达式求值
    connect(calculate,&QAction::triggered,[=](){
        if(rab2->isChecked()){
            w->setWindowModality(Qt::WindowModal);
            w->setWindowFlag(Qt::Widget);
            w->show();
back2:
            int value;
            int code=w->run(2,value);
            if(code==1){
                QString content="运算成功！结果为：";
                content.append(QString::number(value,10));
                info->setText(content);
                w->close();
            }
            else if(code==0){
                info->setText("运算失败！发生错误！");
                w->close();
            }
            else if(code==2){
                info->setText("表达式长度不正确！");
                goto back2;
            }
            else if(code==3)
                w->close();
        }
        else
            info->setText("选择的数据类型不正确！");
    });
    //////////////////////////////////////////
    //清除按钮
    connect(btn2,&QPushButton::clicked,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()==0)
                info->setText("顺序表已经被清除了！");
            else{
                ArrayList->clear();
                info->setText("顺序表已清除！");
            }
        }
        if(rab2->isChecked()){
            if(LinkStack->isEmpty())
                info->setText("链式栈已经被清除了！");
            else{
                LinkStack->clear();
                info->setText("链式栈已清除！");
            }
        }
    });

    //载入按钮
    connect(btn1,&QPushButton::clicked,[=](){
        chb->setDisabled(true);
        if(rab1->isChecked()){
            delete ArrayList;
            Dialog_arrlist_load *dialog=new Dialog_arrlist_load(this);
            int ret=dialog->exec();
            if(ret==QDialog::Accepted){
                int size=dialog->getValue();
                if(chb->isChecked()&&size>10){
                    info->setText("轻量模式下最大长度必须在10以内！");
                    ArrayList=new arrList(0);
                }
                else{
                    ArrayList=new arrList(size);
                    int code=load_arrList(this,ArrayList);
                    if(code==1){
                        ArrayList->draw_arrList(scene);
                        info->setText("载入成功！");
                    }
                    else if(code==0)
                        info->setText("载入的文件不能为空！");
                    else if(code==-2)
                        info->setText("载入的文件长度超长！");
                    else if(code==-1)
                        info->setText("载入失败！");
                }
            }
            else
                ArrayList=new arrList(0);
        }
        if(rab2->isChecked()){
            delete LinkStack;
            Dialog_arrlist_load *dialog=new Dialog_arrlist_load(this);//复用顺序表的最大长度设置对话框
            int ret=dialog->exec();
            if(ret==QDialog::Accepted){
                int size=dialog->getValue();
                if(chb->isChecked()&&size>10){
                    info->setText("轻量模式下最大长度必须在10以内！");
                    LinkStack=new linkStack(0);
                }
                else{
                    LinkStack=new linkStack(size);
                    int code=load_linkStack(this,LinkStack);
                    if(code==1){
                        LinkStack->draw_linkStack(scene);
                        info->setText("载入成功！");
                    }
                    else if(code==0)
                        info->setText("载入的文件不能为空！");
                    else if(code==-2)
                        info->setText("载入的文件长度超长！");
                    else if(code==-1)
                        info->setText("载入失败！");
                }
            }
            else
                LinkStack=new linkStack(0);
        }
    });
}


MainWindow::~MainWindow()
{
    delete w;
    delete ArrayList;
    delete LinkStack;
    delete ui;
}
