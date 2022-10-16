#include "dialog_graph_delete.h"
#include "ui_dialog_graph_delete.h"

Dialog_graph_delete::Dialog_graph_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_graph_delete)
{
    ui->setupUi(this);
}

Dialog_graph_delete::~Dialog_graph_delete()
{
    delete ui;
}

void Dialog_graph_delete::setBox(char *vertex,int len)
{
    QStringList list;
    for(int i=0;i<len;i++){
        if(vertex[i]!=0)
            list.append((QChar)vertex[i]);
    }
    ui->pos_box1->addItems(list);
    ui->pos_box2->addItems(list);
}

void Dialog_graph_delete::getPos(QString &from,QString &to)
{
    from=ui->pos_box1->currentText();
    to=ui->pos_box2->currentText();
}
