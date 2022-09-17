#ifndef DIALOG_ARRLIST_APPEND_H
#define DIALOG_ARRLIST_APPEND_H

#include <QDialog>

namespace Ui {
class Dialog_arrlist_append;
}

class Dialog_arrlist_append : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_arrlist_append(QWidget *parent = nullptr);
    ~Dialog_arrlist_append();
    int getValue();

private:
    Ui::Dialog_arrlist_append *ui;
};

#endif // DIALOG_ARRLIST_APPEND_H
