#include "dialog_linkstack_push.h"
#include "ui_dialog_linkstack_push.h"

Dialog_linkstack_push::Dialog_linkstack_push(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_linkstack_push)
{
    ui->setupUi(this);
}

Dialog_linkstack_push::~Dialog_linkstack_push()
{
    delete ui;
}

int Dialog_linkstack_push::getValue(){
    return ui->line_value->text().toInt(nullptr,10);
}
