#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrlist.h"
#include "methods.h"
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QRect>

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setFixedSize(600,400);

    //单选按钮1
    QRadioButton* rab1=new QRadioButton("顺序表",this);
    rab1->setChecked(true);
    rab1->move(500,5);

    //单选按钮2
    QRadioButton* rab2=new QRadioButton("链式栈",this);
    rab2->move(500,25);

    //单选按钮3
    QRadioButton* rab3=new QRadioButton("图",this);
    rab3->move(500,45);

    //按钮1
    QPushButton* btn1=new QPushButton("载入",this);
    btn1->move(480,85);

    //底部状态栏
    QStatusBar* stBar=new QStatusBar();
    setStatusBar(stBar);
    QLabel* info= new QLabel(this);
    stBar->addWidget(info);

    //文件打开对话框
    connect(btn1,&QPushButton::clicked,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()!=0)
                ArrayList->clear();
            if(load_arrList(this,ArrayList)){
                info->setText(QString("载入成功！"));
                //repaint();
            }
            else
                info->setText(QString("载入的文件不能为空！"));
        }
    });
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(ArrayList->length()!=0)
        ArrayList->draw_arrList(painter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
