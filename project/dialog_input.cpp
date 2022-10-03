#include "dialog_input.h"
#include "ui_dialog_input.h"

Dialog_input::Dialog_input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_input)
{
    ui->setupUi(this);
}

Dialog_input::~Dialog_input()
{
    delete ui;
}

QString Dialog_input::getText(){
    return ui->line_text->text();
}
