#ifndef DIALOG_SET_STEP_H
#define DIALOG_SET_STEP_H

#include <QDialog>

namespace Ui {
class Dialog_set_step;
}

class Dialog_set_step : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_set_step(QWidget *parent = nullptr);
    ~Dialog_set_step();
    int get_Value();
private:
    Ui::Dialog_set_step *ui;
};

#endif // DIALOG_SET_STEP_H
