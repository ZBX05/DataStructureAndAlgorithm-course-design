#include "widget_linkstack_matching.h"
#include "ui_widget_linkstack_matching.h"
#include "dialog_input.h"
#include "linkstack.h"

Widget_linkstack_matching::Widget_linkstack_matching(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_linkstack_matching)
{
    ui->setupUi(this);

    setFixedSize(1100,600);

    scene=new QGraphicsScene(this);
    //scene->setSceneRect(-300,-250,300,250);
    scene->setSceneRect(-550,-300,1090,550);
    view=new QGraphicsView(this);
    view->resize(1100,600);
    view->setScene(scene);
    view->setAlignment(Qt::AlignCenter);
}

int Widget_linkstack_matching::run(int code,int &value){
    scene->clear();
    if(code==1)
        return brackets_matching();
    else if(code==2)
        return expression_calculate(value);
}

int Widget_linkstack_matching::brackets_matching(){
    Dialog_input *dialog=new Dialog_input(this);
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        QString text=dialog->getText();
        if(text.length()==0||text.length()>20)
            return 2;
        else{
            linkStack *ls=new linkStack(text.length());
            if(ls->brackets_matching(scene,&text))
                return 1;
            else
                return 0;
        }
    }
    else{
        return 3;
        delete this;
    }
}

int Widget_linkstack_matching::expression_calculate(int &value){
    Dialog_input *dialog=new Dialog_input(this);
    int ret=dialog->exec();
    if(ret==QDialog::Accepted){
        QString text=dialog->getText();
        if(text.length()==0||text.length()>20)
            return 2;
        else{
            linkStack *ls=new linkStack(text.length());
            if(ls->expression_calculate(scene,&text,value))
                return 1;
            else
                return 0;
        }
    }
    else{
        return 3;
        delete this;
    }
}

Widget_linkstack_matching::~Widget_linkstack_matching()
{
    delete ui;
}
