#ifndef WIDGET_LINKSTACK_MATCHING_H
#define WIDGET_LINKSTACK_MATCHING_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class Widget_linkstack_matching;
}

class Widget_linkstack_matching : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
public:
//    linkStack *LinkStack=new linkStack(0);
    explicit Widget_linkstack_matching(QWidget *parent = nullptr);
    ~Widget_linkstack_matching();
    int brackets_matching(int step);
    int expression_calculate(int &value,int step);
    int run(int code,int &value,int step);
private:
    Ui::Widget_linkstack_matching *ui;
};

#endif // WIDGET_LINKSTACK_MATCHING_H
