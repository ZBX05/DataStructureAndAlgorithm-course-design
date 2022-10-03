#include "dialog_arrlist_load.h"
#include "ui_dialog_arrlist_load.h"

Dialog_arrlist_load::Dialog_arrlist_load(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_arrlist_load)
{
    ui->setupUi(this);
}

Dialog_arrlist_load::~Dialog_arrlist_load()
{
    delete ui;
}

int Dialog_arrlist_load::getValue(){
    return ui->line_value->text().toInt(nullptr,10);
}

