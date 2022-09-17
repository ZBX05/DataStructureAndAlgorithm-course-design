#include "dialog_arrlist_append.h"
#include "ui_dialog_arrlist_append.h"

Dialog_arrlist_append::Dialog_arrlist_append(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_arrlist_append)
{
    ui->setupUi(this);
}

Dialog_arrlist_append::~Dialog_arrlist_append()
{
    delete ui;
}

int Dialog_arrlist_append::getValue(){
    return ui->line_value->text().toInt();
}
