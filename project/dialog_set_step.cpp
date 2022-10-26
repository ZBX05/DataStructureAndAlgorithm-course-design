#include "dialog_set_step.h"
#include "ui_dialog_set_step.h"

Dialog_set_step::Dialog_set_step(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_set_step)
{
    ui->setupUi(this);
}

Dialog_set_step::~Dialog_set_step()
{
    delete ui;
}

int Dialog_set_step::get_Value()
{
    return ui->step_value->value();
}
