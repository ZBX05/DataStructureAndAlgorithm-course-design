#ifndef DIALOG_ARRLIST_INSERT_H
#define DIALOG_ARRLIST_INSERT_H

#include <QDialog>

namespace Ui {
class Dialog_arrlist_insert;
}

class Dialog_arrlist_insert : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_arrlist_insert(QWidget *parent = nullptr);
    ~Dialog_arrlist_insert();
    void setBox(int len);
    int getPos();
    int getValue();
private:
    Ui::Dialog_arrlist_insert *ui;
};

#endif // DIALOG_ARRLIST_INSERT_H
