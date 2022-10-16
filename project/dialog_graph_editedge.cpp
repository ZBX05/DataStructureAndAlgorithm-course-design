#include "dialog_graph_editedge.h"
#include "ui_dialog_graph_editedge.h"

Dialog_graph_editedge::Dialog_graph_editedge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_graph_editedge)
{
    ui->setupUi(this);
}

Dialog_graph_editedge::~Dialog_graph_editedge()
{
    delete ui;
}

void Dialog_graph_editedge::setBox(char *vertex,int len)
{
    QStringList list;
    for(int i=0;i<len;i++){
        if(vertex[i]!=0)
            list.append((QChar)vertex[i]);
    }
    ui->pos_box1->addItems(list);
    ui->pos_box2->addItems(list);
}

void Dialog_graph_editedge::getPos(QString &from,QString &to)
{
    from=ui->pos_box1->currentText();
    to=ui->pos_box2->currentText();
}

int Dialog_graph_editedge::getValue()
{
    return ui->line_value->text().toInt(nullptr,10);
}
