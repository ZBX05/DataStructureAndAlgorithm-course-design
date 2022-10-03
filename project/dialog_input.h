#ifndef DIALOG_INPUT_H
#define DIALOG_INPUT_H

#include <QDialog>

namespace Ui {
class Dialog_input;
}

class Dialog_input : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_input(QWidget *parent = nullptr);
    ~Dialog_input();
    QString getText();

private:
    Ui::Dialog_input *ui;
};

#endif // DIALOG_INPUT_H
