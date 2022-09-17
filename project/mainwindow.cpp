#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrlist.h"
#include "methods.h"
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

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setFixedSize(600,500);

    scene=new QGraphicsScene(this);
    scene->setSceneRect(-300,-250,300,250);
    QGraphicsRectItem* rect=new QGraphicsRectItem(-100,-100,20,20);
    QGraphicsTextItem* text=new QGraphicsTextItem("try",rect);
    rect->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    qDebug()<<rect->boundingRect().x()<<"   "<<rect->boundingRect().y();
    text->setPos(rect->boundingRect().x(),rect->boundingRect().y());
    QPen pen;
    pen.setWidth(2);
    rect->setPen(pen);
    scene->addItem(rect);
    view=new QGraphicsView(this);
    view->resize(600,500);
    view->setScene(scene);


    //单选按钮1
    QRadioButton* rab1=new QRadioButton("顺序表",this);
    rab1->setChecked(true);
    rab1->move(500,25);

    //单选按钮2
    QRadioButton* rab2=new QRadioButton("链式栈",this);
    rab2->move(500,45);

    //单选按钮3
    QRadioButton* rab3=new QRadioButton("图",this);
    rab3->move(500,65);

    //按钮1
    QPushButton* btn1=new QPushButton("载入",this);
    btn1->move(480,105);

    //按钮2
    QPushButton* btn2=new QPushButton("新建",this);
    btn2->move(480,145);

    //按钮3
    QPushButton* btn3=new QPushButton("清除",this);
    btn3->move(480,185);

    //顶部菜单栏
    QMenuBar* meb=new QMenuBar(this);
    setMenuBar(meb);
    //菜单
    QMenu* meu1=new QMenu("操作");
    meb->addMenu(meu1);
    QMenu* arrlist_meu=new QMenu("顺序表");
    meu1->addMenu(arrlist_meu);
    QAction* edit_data=arrlist_meu->addAction("修改数据");
    QAction* append=arrlist_meu->addAction("添加元素");
    QAction* insert=arrlist_meu->addAction("插入");
    QAction* delete_=arrlist_meu->addAction("删除");

    //底部状态栏
    QStatusBar* stBar=new QStatusBar();
    setStatusBar(stBar);
    QLabel* info= new QLabel(this);
    stBar->addWidget(info);

    //菜单：顺序表
    //设置无效条件
    connect(arrlist_meu,&QMenu::aboutToShow,[=](){
       if(rab1->isCheckable())
           arrlist_meu->setEnabled(true);
       else
           arrlist_meu->setEnabled(false);
    });

    //修改数据
    connect(edit_data,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0){
                if(edit_arrList(this,ArrayList))
                    info->setText("修改数据成功!");
                else
                    info->setText("修改数据失败！");
            }
            else{
                info->setText("修改数据时要求顺序表不能为空！");
            }
        }
        scene->update();
        view->update();
    });

    //添加元素
    connect(append,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0){
                if(ArrayList->length()<ArrayList->getMaxSize()){
                    if(append_arrList(this,ArrayList))
                        info->setText("添加元素成功!");
                    else
                        info->setText("添加元素失败！");
                }
                else{
                    info->setText("顺序表已满！");
                }
            }
            else
                info->setText("此处的添加操作要求顺序表不能为空！");
        }
        ArrayList->draw_arrList(scene);
        scene->update();
        view->update();
    });
    //////////////////////////////////////////
    //清除按钮
    connect(btn3,&QPushButton::clicked,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()==0)
                info->setText("顺序表已经是空的了！");
            else{
                scene->clear();
                ArrayList->clear();
                info->setText("顺序表已清空！");
            }
        }
        update();
    });

    //载入按钮
    connect(btn1,&QPushButton::clicked,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0)
                ArrayList->clear();
            int code=load_arrList(this,ArrayList);
            if(code==1){
                ArrayList->draw_arrList(scene);
                info->setText(QString("载入成功！"));
            }
                //repaint();
            else if(code==0)
                info->setText(QString("载入的文件不能为空！"));
            else if(code==-1)
                info->setText(QString("载入失败！"));
        }
    });
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
//    if(ArrayList->length()!=0)
//        ArrayList->draw_arrList(painter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
