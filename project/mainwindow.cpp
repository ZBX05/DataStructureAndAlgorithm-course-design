#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrlist.h"
#include "methods.h"
#include "dialog_arrlist_load.h"
#include "graph_methods.h"
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
    QMenu *graph_meu=new QMenu("图");
    meu1->addMenu(graph_meu);
    QAction *add_vertex=graph_meu->addAction("添加节点");
    QAction *del_vertex=graph_meu->addAction("删除节点");
    QAction *set_edge=graph_meu->addAction("添加/修改边");
    QAction *del_edge=graph_meu->addAction("删除边");
    QAction *dfs=graph_meu->addAction("🎇深度优先周游");
    QAction *bfs=graph_meu->addAction("🎇广度优先周游");
    QAction *prim=graph_meu->addAction("🎇Prim算法求最小生成树");

    //底部状态栏
    QStatusBar *stBar=new QStatusBar();
    setStatusBar(stBar);
    QLabel *info= new QLabel(this);
    stBar->addWidget(info);


    connect(rab1,&QRadioButton::clicked,[=]{
        if(rab3->isChecked()){
            chb->setChecked(true);
            chb->setDisabled(true);
        }
        if(!rab3->isChecked())
            chb->setDisabled(false);
    });

    connect(rab2,&QRadioButton::clicked,[=]{
        if(rab3->isChecked()){
            chb->setChecked(true);
            chb->setDisabled(true);
        }
        if(!rab3->isChecked())
            chb->setDisabled(false);
    });

    connect(rab3,&QRadioButton::clicked,[=]{
        if(rab3->isChecked()){
            chb->setChecked(true);
            chb->setDisabled(true);
        }
        if(!rab3->isChecked())
            chb->setDisabled(false);
    });
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
    //图菜单
    //添加节点
    connect(add_vertex,&QAction::triggered,[=]{
        if(rab3->isChecked()){
            if(graph->getNumVertex()!=0){
                if(graph->addVertex()){
                    graph->update_graph(scene);
                    info->setText("添加节点成功！");
                }
                else
                    info->setText("添加节点失败！已到达分配的最大节点数！");
            }
            else
                info->setText("请先加载图！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //删除节点
    connect(del_vertex,&QAction::triggered,[=](){
        if(rab3->isChecked()){
            if(graph->getNumVertex()!=0){
                if(graph->getLen()!=0){
                    if(delVertex_Graph(this,scene,graph)){
                        graph->update_graph(scene);
                        info->setText("删除节点成功！");
                    }
                }
                else
                    info->setText("图已经没有节点了！");
            }
            else
                info->setText("请先加载图！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //添加/修改边
    connect(set_edge,&QAction::triggered,[=]{
       if(rab3->isChecked()){
           if(graph->getNumVertex()!=0){
               if(graph->getLen()>=2){
                    int code=editEdge_Graph(this,graph);
                    if(code==1){
                        graph->update_graph(scene);
                        info->setText("对边的操作成功！");
                    }
                    else if(code==0)
                        info->setText("起点和终点不能相同！");
                    else if(code==-1)
                        info->setText("边的权重不能设置为0！");
               }
               else
                   info->setText("图的节点数不够多！");
           }
           else
               info->setText("请先加载图！");
       }
       else
           info->setText("选择的数据类型不正确！");
    });

    //删除边
    connect(del_edge,&QAction::triggered,[=]{
       if(rab3->isChecked()){
           if(graph->getNumVertex()!=0){
               if(graph->EdgesNum()!=0){
                    int code=delEdge_Graph(this,scene,graph);
                    if(code==1){
                        graph->update_graph(scene);
                        info->setText("删除边成功！");
                    }
                    else if(code==0)
                        info->setText("起点和终点不能相同！");
                    else if(code==-1)
                        info->setText("选定的起点和终点之间没有边！");
               }
               else
                   info->setText("图的边数已经为0！");
           }
           else
               info->setText("请先加载图！");
       }
       else
           info->setText("选择的数据类型不正确！");
    });

    //深度优先周游
    connect(dfs,&QAction::triggered,[=]{
        if(rab3->isChecked()){
            QGraphicsEllipseItem *unit=graph->get_unit();
            QString text="深度优先周游完成！周游序列为：";
            QTimer* timer=new QTimer(nullptr);
            timer->setSingleShot(true);
            QEventLoop* loop=new QEventLoop(nullptr);
            Graph::connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
            QPen *pen=new QPen();
            pen->setWidth(4);
            pen->setColor(Qt::green);
            if(graph->getNumVertex()!=0){
                QStringList str;
                DFS(*graph,0,str);
                for(int i=0;i<str.length();i++){
                    timer->start(1000);
                    loop->exec();
                    unit[str[i].toInt(nullptr,10)].setPen(*pen);
                    scene->update();
                    text.append(QString(graph->get_vertex()[str[i].toInt(nullptr,10)]));
                }
                info->setText(text);
                pen->setColor(Qt::black);
                timer->start(3000);
                loop->exec();
                graph->update_graph(scene);
            }
            else
                info->setText("请先加载图！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //广度优先周游
    connect(bfs,&QAction::triggered,[=]{
        if(rab3->isChecked()){
            if(graph->getNumVertex()!=0){
                QGraphicsEllipseItem *unit=graph->get_unit();
                QString text="广度优先周游完成！周游序列为：";
                QTimer* timer=new QTimer(nullptr);
                timer->setSingleShot(true);
                QEventLoop* loop=new QEventLoop(nullptr);
                Graph::connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
                QPen *pen=new QPen();
                pen->setWidth(4);
                pen->setColor(Qt::green);
                QStringList str;
                BFS(*graph,0,str);
                for(int i=0;i<str.length();i++){
                    timer->start(1000);
                    loop->exec();
                    unit[str[i].toInt(nullptr,10)].setPen(*pen);
                    scene->update();
                    text.append(QString(graph->get_vertex()[str[i].toInt(nullptr,10)]));
                }
                info->setText(text);
                pen->setColor(Qt::black);
                timer->start(3000);
                loop->exec();
                graph->update_graph(scene);
            }
            else
                info->setText("请先加载图！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //Prim算法
    connect(prim,&QAction::triggered,[=]{
        if(rab3->isChecked()){
            if(graph->getNumVertex()!=0){
                QGraphicsLineItem **line=graph->get_line();
                QGraphicsEllipseItem *unit=graph->get_unit();
                QString text="Prim算法完成！";
                QTimer* timer=new QTimer(nullptr);
                timer->setSingleShot(true);
                QEventLoop* loop=new QEventLoop(nullptr);
                Graph::connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
                QPen *pen=new QPen();
                pen->setWidth(4);
                pen->setColor(Qt::green);
                QStringList str;
                Edge *MST=new Edge[graph->getNumVertex()];
                Prim(*graph,0,MST,str);
                for(int i=0;i<str.length();i++){
                    timer->start(500);
                    loop->exec();
                    unit[str[i].toInt(nullptr,10)].setPen(*pen);
                    scene->update();
                    if(i!=str.length()-1){
                        timer->start(500);
                        loop->exec();
                        MST[i].from>MST[i].to?line[MST[i].from][MST[i].to].setPen(*pen):line[MST[i].to][MST[i].from].setPen(*pen);
                    }
                }
                info->setText(text);
            }
            else
                info->setText("请先加载图！");
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
        if(rab3->isChecked()){
            if(graph->isEmpty())
                info->setText("图已经是空的了！");
            else{
                graph->clear();
                info->setText("图已清空！");
            }
        }
    });

    //载入按钮
    connect(btn1,&QPushButton::clicked,[=](){
//        chb->setDisabled(true);
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
        if(rab3->isChecked()){
            delete graph;
            Dialog_arrlist_load *dialog=new Dialog_arrlist_load(this);
            int ret=dialog->exec();
            if(ret==QDialog::Accepted){
                int size=dialog->getValue();
                if(chb->isChecked()&&size>15){
                    info->setText("轻量模式下最大节点数必须在15以内！");
                    graph=new Graph(0);
                }
                else{
                    graph=new Graph(size);
                    int code=load_Graph(this,graph,size);
                    if(code==1){
                        graph->update_graph(scene);
                        info->setText("载入成功！");
                    }
                    else if(code==0)
                        info->setText("载入的文件不能为空！");
                    else if(code==-2)
                        info->setText("载入的文件节点数超出设定的范围！");
                    else if(code==-1)
                        info->setText("载入失败！");
                }
            }
            else
                graph=new Graph(0);
        }
    });
}


MainWindow::~MainWindow()
{
    delete w;
    delete graph;
    delete ArrayList;
    delete LinkStack;
    delete ui;
}
