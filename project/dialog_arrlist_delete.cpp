#include "dialog_arrlist_delete.h"
#include "ui_dialog_arrlist_delete.h"

Dialog_arrlist_delete::Dialog_arrlist_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_arrlist_delete)
{
    ui->setupUi(this);
}

Dialog_arrlist_delete::~Dialog_arrlist_delete()
{
    delete ui;
}

void Dialog_arrlist_delete::setBox(int len)
{
    QStringList list;
    for(int i=0;i<len;i++)
        list.append(QString::number(i,10));
    ui->pos_box->addItems(list);
}

void Dialog_arrlist_delete::setBox(char *str,int len)
{
    QStringList list;
    for(int i=0;i<len;i++){
        if(str[i]!=0)
            list.append((QChar)str[i]);
    }
    ui->pos_box->addItems(list);
}

int Dialog_arrlist_delete::getPos()
{
    return ui->pos_box->currentText().toInt();
}

QString Dialog_arrlist_delete::getVertexPos()
{
    return ui->pos_box->currentText();
}
