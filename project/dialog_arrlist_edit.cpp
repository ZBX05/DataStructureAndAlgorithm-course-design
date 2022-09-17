#include "dialog_arrlist_edit.h"
#include "ui_dialog_arrlist_edit.h"

Dialog_arrlist_edit::Dialog_arrlist_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_arrlist_edit)
{
    ui->setupUi(this);
}

Dialog_arrlist_edit::~Dialog_arrlist_edit()
{
    delete ui;
}

void Dialog_arrlist_edit::setBox(int len)
{
    QStringList list;
    for(int i=0;i<len;i++)
        list.append(QString::number(i,10));
    ui->pos_box->addItems(list);
}

int Dialog_arrlist_edit::getPos()
{
    return ui->pos_box->currentText().toInt();
}

int Dialog_arrlist_edit::getValue()
{
    return ui->line_value->text().toInt();
}



