#include "mainwindow.h"
//#include "myscene.h"
#include "dialog_set_step.h"
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
#include <QGraphicsPathItem>
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

    QGraphicsScene *scene=new QGraphicsScene(this);
    //scene->setSceneRect(-300,-250,300,250);
    scene->setSceneRect(-600,-350,1190,650);
    view=new QGraphicsView(this);
    view->resize(1200,700);
    view->setScene(scene);
    view->setAlignment(Qt::AlignCenter);




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

    //按钮3
    QPushButton *btn3=new QPushButton("全部清除",this);
    btn3->move(1080,205);


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
    QAction *dijkstra=graph_meu->addAction("🎇迪杰斯特拉算法求最单源最短路径");
    QMenu *meu2=new QMenu("保存");
    meb->addMenu(meu2);
    QAction *save_this=new QAction("保存当前数据结构");
    meu2->addAction(save_this);
    QAction *save_all=new QAction("保存所有数据结构");
    meu2->addAction(save_all);
    QAction *print_screen=new QAction("截图");
    meb->addAction(print_screen);
    QMenu *meu3=new QMenu("设置");
    meb->addMenu(meu3);
    QAction *set_step=new QAction("设置动画步长");
    meu3->addAction(set_step);

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
        else
            chb->setDisabled(false);
        if(rab1->isChecked()){
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(ArrayList->getMaxSize()!=0&&ArrayList->length()!=0)
                ArrayList->draw_arrList(scene);
        }
        else if(rab2->isChecked()){
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(LinkStack->getSize()!=0&&!LinkStack->isEmpty())
                LinkStack->draw_linkStack(scene);
        }
        else{
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(graph->getNumVertex()!=0&&graph->len!=0)
                graph->update_graph(scene);
        }
    });

    connect(rab2,&QRadioButton::clicked,[=]{
        if(rab3->isChecked()){
            chb->setChecked(true);
            chb->setDisabled(true);
        }
        else
            chb->setDisabled(false);
        if(rab1->isChecked()){
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(ArrayList->getMaxSize()!=0&&ArrayList->length()!=0)
                ArrayList->draw_arrList(scene);
        }
        else if(rab2->isChecked()){
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(LinkStack->getSize()!=0&&!LinkStack->isEmpty())
                LinkStack->draw_linkStack(scene);
        }
        else{
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(graph->getNumVertex()!=0&&graph->len!=0)
                graph->update_graph(scene);
        }
    });

    connect(rab3,&QRadioButton::clicked,[=]{
        if(rab3->isChecked()){
            chb->setChecked(true);
            chb->setDisabled(true);
        }
        else
            chb->setDisabled(false);
        if(rab1->isChecked()){
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(ArrayList->getMaxSize()!=0&&ArrayList->length()!=0)
                ArrayList->draw_arrList(scene);
        }
        else if(rab2->isChecked()){
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(LinkStack->getSize()!=0&&!LinkStack->isEmpty())
                LinkStack->draw_linkStack(scene);
        }
        else{
            foreach (QGraphicsItem *item, scene->items()) {
                scene->removeItem(item);
            }
            if(graph->getNumVertex()!=0&&graph->len!=0)
                graph->update_graph(scene);
        }
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
                    int code=insert_arrList(this,scene,ArrayList,info,step);
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
                int code=delete_arrList(this,scene,ArrayList,info,step);
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
                ArrayList->bubbleSort(info,step);
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
            int code=w->run(1,value,step);
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
            int code=w->run(2,value,step);
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
            if(graph->getNumVertex()!=0){
                Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(this);
                dialog->setBox(graph->get_vertex(),graph->getLen());
                dialog->setInfo(QString("起始位置:"));
                int ret=dialog->exec();
                if(ret==QDialog::Accepted){
                    graph->update_graph(scene);
                    QString string=dialog->getVertexPos();
                    int start=0;
                    for(int i=0;i<graph->getLen();i++){
                        if(string[0]==(QChar)graph->get_vertex()[i]){
                            start=i;
                        }
                    }
                    QGraphicsEllipseItem *unit=graph->get_unit();
                    QString text="深度优先周游完成！周游序列为：";
                    QTimer* timer=new QTimer(nullptr);
                    timer->setSingleShot(true);
                    QEventLoop* loop=new QEventLoop(nullptr);
                    Graph::connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
                    QPen *pen=new QPen();
                    pen->setWidth(4);
                    pen->setColor(Qt::green);
                    QStringList str;
                    DFS(*graph,start,str);
                    for(int i=0;i<str.length();i++){
                        timer->start(step);
                        loop->exec();
                        unit[str[i].toInt(nullptr,10)].setPen(*pen);
                        scene->update();
                        text.append(QString(graph->get_vertex()[str[i].toInt(nullptr,10)]));
                    }
                    info->setText(text);
                    for(int i=0;i<graph->getNumVertex();i++)
                        graph->Mark[i]=UNVISITED;
                }
                delete dialog;
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
                Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(this);
                dialog->setBox(graph->get_vertex(),graph->getLen());
                dialog->setInfo(QString("起始位置:"));
                int ret=dialog->exec();
                if(ret==QDialog::Accepted){
                    graph->update_graph(scene);
                    QString string=dialog->getVertexPos();
                    int start=0;
                    for(int i=0;i<graph->getLen();i++){
                        if(string[0]==(QChar)graph->get_vertex()[i]){
                            start=i;
                        }
                    }
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
                    BFS(*graph,start,str);
                    for(int i=0;i<str.length();i++){
                        timer->start(step);
                        loop->exec();
                        unit[str[i].toInt(nullptr,10)].setPen(*pen);
                        scene->update();
                        text.append(QString(graph->get_vertex()[str[i].toInt(nullptr,10)]));
                    }
                    info->setText(text);
                    for(int i=0;i<graph->getNumVertex();i++)
                        graph->Mark[i]=UNVISITED;
                }
                delete dialog;
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
                Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(this);
                dialog->setBox(graph->get_vertex(),graph->getLen());
                dialog->setInfo(QString("起始位置:"));
                int ret=dialog->exec();
                if(ret==QDialog::Accepted){
                    graph->update_graph(scene);
                    QString string=dialog->getVertexPos();
                    int start=0;
                    for(int i=0;i<graph->getLen();i++){
                        if(string[0]==(QChar)graph->get_vertex()[i]){
                            start=i;
                        }
                    }
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
                    Prim(*graph,start,MST,str);
                    for(int i=0;i<str.length();i++){
                        timer->start(step);
                        loop->exec();
                        unit[str[i].toInt(nullptr,10)].setPen(*pen);
                        scene->update();
                        if(i!=str.length()-1){
                            timer->start(step);
                            loop->exec();
                            MST[i].from>MST[i].to?line[MST[i].from][MST[i].to].setPen(*pen):line[MST[i].to][MST[i].from].setPen(*pen);
                        }
                    }
                    info->setText(text);
                }
                delete dialog;
            }
            else
                info->setText("请先加载图！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });

    //Dijkstra算法
    connect(dijkstra,&QAction::triggered,[=](){
        if(rab3->isChecked()){
            if(graph->getNumVertex()!=0){
                Dialog_arrlist_delete *dialog=new Dialog_arrlist_delete(this);
                dialog->setBox(graph->get_vertex(),graph->getLen());
                dialog->setInfo(QString("起始位置:"));
                int ret=dialog->exec();
                if(ret==QDialog::Accepted){
                    graph->update_graph(scene);
                    QString string=dialog->getVertexPos();
                    Dist *D;
                    int start=0;
                    for(int i=0;i<graph->getLen();i++){
                        if(string[0]==(QChar)graph->get_vertex()[i]){
                            start=i;
                        }
                    }
//                    QGraphicsLineItem **line=graph->get_line();
//                    QGraphicsEllipseItem *unit=graph->get_unit();
//                    QString text="Prim算法完成！";
//                    QTimer* timer=new QTimer(nullptr);
//                    timer->setSingleShot(true);
//                    QEventLoop* loop=new QEventLoop(nullptr);
//                    Graph::connect(timer,&QTimer::timeout,loop,&QEventLoop::quit);
//                    QPen *pen=new QPen();
//                    pen->setWidth(4);
//                    pen->setColor(Qt::green);
//                    QStringList str;
//                    Edge *MST=new Edge[graph->getNumVertex()];

                    Dijkstra(scene,info,step,*graph,start,D);
                    delete D;
                }
                delete dialog;
            }
            else
                info->setText("请先加载图！");
        }
        else
            info->setText("选择的数据类型不正确！");
    });
    //////////////////////////////////////////
    //保存
    //保存当前
    connect(save_this,&QAction::triggered,[=](){
        if(rab1->isChecked()){
            if(ArrayList->length()==0)
                info->setText("保存失败！顺序表是空的！");
            else{
                if(save_arrList(this,ArrayList))
                    info->setText("保存成功！");
//                else
//                    info->setText("保存失败！");
            }
        }
        if(rab2->isChecked()){
            if(LinkStack->isEmpty())
                info->setText("保存失败！链式栈是空的！");
            else{
                if(save_linkStack(this,LinkStack))
                    info->setText("保存成功！");
//                else
//                    info->setText("保存失败！");
            }
        }
        if(rab3->isChecked()){
            if(graph->isEmpty())
                info->setText("保存失败！图是空的！");
            else{
                if(save_Graph(this,graph))
                    info->setText("保存成功！");
//                else
//                    info->setText("保存失败！");
            }
        }
    });
    //保存全部
    connect(save_all,&QAction::triggered,[=](){
        QString str_1="",str_2="",str_3="",text="已执行全部保存操作！执行情况：";
        if(ArrayList->length()==0)
            str_1="顺序表保存失败！顺序表是空的！";
        else{
            if(save_arrList(this,ArrayList))
                str_1="顺序表保存成功！";
//            else
//                str_1="顺序表保存失败！";
        }
        if(LinkStack->isEmpty())
            str_2="链式栈保存失败！链式栈是空的！";
        else{
            if(save_linkStack(this,LinkStack))
                str_2="链式栈保存成功！";
//            else
//                str_2="链式栈保存失败！";
        }
        if(graph->isEmpty())
            str_3="图保存失败！图是空的！";
        else{
            if(!save_Graph(this,graph))
                str_3="图保存成功！";
//            else
//                str_3="图保存失败！";
        }
        text.append(str_1);
        text.append(str_2);
        text.append(str_3);
        info->setText(text);
    });
    //////////////////////////////////////////
    //截图
    connect(print_screen,&QAction::triggered,[=](){
        QPixmap p = this->grab(QRect(0, 0, 1200, 700));
        if(p.save("picture.jpg"))
            info->setText("窗口截图成功！");
        else
            info->setText("窗口截图失败！");
    });
    //////////////////////////////////////////
    //设置
    //设置步长
    connect(set_step,&QAction::triggered,[=](){
        Dialog_set_step *dialog=new Dialog_set_step(this);
        int ret=dialog->exec();
        if(ret==QDialog::Accepted){
            step=dialog->get_Value();
            info->setText("步长设置完成!");
            delete dialog;
        }
    });
    //////////////////////////////////////////
    //全部清除按钮
    connect(btn3,&QPushButton::clicked,[=](){
        QString str_1="",str_2="",str_3="",text="已执行全部清除操作！执行情况：";
        if(ArrayList->length()==0)
            str_1="顺序表清除失败！顺序表已经是空的了！";
        else{
            ArrayList->clear();
            str_1="顺序表清除成功！";
        }
        if(LinkStack->isEmpty())
            str_2="链式栈清除失败！链式栈已经是空的了！";
        else{
            LinkStack->clear();
            str_2="链式栈清除成功！";
        }
        if(graph->isEmpty())
            str_3="图清除失败！图已经是空的了！";
        else{
            graph->clear();
            str_3="图清除成功！";
        }
        text.append(str_1);
        text.append(str_2);
        text.append(str_3);
        info->setText(text);
    });

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
                    int code=load_Graph(this,scene,graph,size);
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

void MainWindow::mousePressEvent(QMouseEvent *ev){
    grabMouse();
    if(ev->button()==Qt::LeftButton&&hit_tag==0&&graph->getLen()!=0){
        for(int i=0;i<graph->getLen();i++){
            if(graph->get_vertex()[i]!=0){
                QPointF point=QPointF(graph->get_unit()[i].mapFromScene(graph->get_unit()[i].boundingRect().x()+605,
                                                                    graph->get_unit()[i].boundingRect().y()+375));
                if(ev->pos().x()>=point.x()&&
                        ev->pos().x()<=point.x()+40&&
                        ev->pos().y()>=point.y()&&
                        ev->pos().y()<=point.y()+40){
                    graph->tag[i]=1;
                    hit_pos=i;
                    hit_tag=1;
                }
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev){
    releaseMouse();
    if(ev->button()==Qt::LeftButton&&hit_tag==1&&graph->getLen()!=0){
        for(int i=0;i<graph->getLen();i++){
            if(graph->get_vertex()[i]!=0){
                if(graph->tag[i]==1){
                    graph->tag[i]=0;
                    hit_pos=-1;
                    hit_tag=0;
                }
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev){
    if((ev->buttons()&Qt::LeftButton)&&hit_tag==1&&graph->getLen()!=0){
        if(hit_pos>=0){
            if(graph->tag[hit_pos]==1){
                if(ev->pos().x()<=20||ev->pos().y()<=44||ev->pos().x()>=765||ev->pos().y()>=680){
                    qreal x=ev->pos().x(),y=ev->pos().y();
                    if(ev->pos().x()<=20)
                        x=20;
                    else if(ev->pos().x()>=765)
                        x=765;
                    if(ev->pos().y()<=44)
                        y=44;
                    else if(ev->pos().y()>=680)
                        y=680;
                    graph->get_unit()[hit_pos].setRect(x-625,y-395,40,40);
                }
                else
                    graph->get_unit()[hit_pos].setRect(ev->pos().x()-625,ev->pos().y()-395,40,40);
                graph->get_text()[hit_pos].setPos(graph->get_unit()[hit_pos].boundingRect().x()+10,graph->get_unit()[hit_pos].boundingRect().y()+10);
                for(int i=0;i<graph->getLen();i++){
                    if(graph->get_matrix()[hit_pos][i]!=0){
                        graph->get_line()[hit_pos][i].setLine(graph->get_unit()[hit_pos].boundingRect().x()+20,
                                                              graph->get_unit()[hit_pos].boundingRect().y()+20,
                                                              graph->get_unit()[i].boundingRect().x()+20,
                                                              graph->get_unit()[i].boundingRect().y()+20);
                        graph->get_w()[hit_pos][i].setPos((graph->get_unit()[hit_pos].boundingRect().x()+20+graph->get_unit()[i].boundingRect().x()+20)/2,
                                                          (graph->get_unit()[hit_pos].boundingRect().y()+20+graph->get_unit()[i].boundingRect().y()+20)/2);
                    }
                    if(graph->get_matrix()[i][hit_pos]!=0){
                        graph->get_line()[i][hit_pos].setLine(graph->get_unit()[i].boundingRect().x()+20,
                                                              graph->get_unit()[i].boundingRect().y()+20,
                                                              graph->get_unit()[hit_pos].boundingRect().x()+20,
                                                              graph->get_unit()[hit_pos].boundingRect().y()+20);
                        graph->get_w()[i][hit_pos].setPos((graph->get_unit()[i].boundingRect().x()+20+graph->get_unit()[hit_pos].boundingRect().x()+20)/2,
                                                          (graph->get_unit()[i].boundingRect().y()+20+graph->get_unit()[hit_pos].boundingRect().y()+20)/2);
                    }
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete w;
    delete graph;
    delete ArrayList;
    delete LinkStack;
    delete ui;
}
