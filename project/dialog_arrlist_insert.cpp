#include "dialog_arrlist_insert.h"
#include "ui_dialog_arrlist_insert.h"

Dialog_arrlist_insert::Dialog_arrlist_insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_arrlist_insert)
{
    ui->setupUi(this);
}

Dialog_arrlist_insert::~Dialog_arrlist_insert()
{
    delete ui;
}

void Dialog_arrlist_insert::setBox(int len)
{
    QStringList list;
    for(int i=0;i<len;i++)
        list.append(QString::number(i,10));
    ui->pos_box->addItems(list);
}

int Dialog_arrlist_insert::getPos()
{
    return ui->pos_box->currentText().toInt();
}

int Dialog_arrlist_insert::getValue()
{
    return ui->line_value->text().toInt();
}
