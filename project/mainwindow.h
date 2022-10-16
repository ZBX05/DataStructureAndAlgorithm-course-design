#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "arrlist.h"
#include "linkstack.h"
#include "widget_linkstack_matching.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Widget_linkstack_matching *w=new Widget_linkstack_matching;
public:
    arrList *ArrayList=new arrList(0);
    linkStack *LinkStack=new linkStack(0);
    Graph *graph=new Graph(0);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
