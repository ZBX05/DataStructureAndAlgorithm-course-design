#ifndef DIALOG_ARRLIST_EDIT_H
#define DIALOG_ARRLIST_EDIT_H

#include <QDialog>
#include <QObject>

namespace Ui {
class Dialog_arrlist_edit;
}

class Dialog_arrlist_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_arrlist_edit(QWidget *parent = nullptr);
    ~Dialog_arrlist_edit();
    void setBox(int len);
    int getPos();
    int getValue();

private slots:

private:
    Ui::Dialog_arrlist_edit *ui;
};

#endif // DIALOG_ARRLIST_EDIT_H
