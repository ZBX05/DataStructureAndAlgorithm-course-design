#ifndef DIALOG_LINKSTACK_PUSH_H
#define DIALOG_LINKSTACK_PUSH_H

#include <QDialog>

namespace Ui {
class Dialog_linkstack_push;
}

class Dialog_linkstack_push : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_linkstack_push(QWidget *parent = nullptr);
    ~Dialog_linkstack_push();
    int getValue();
private:
    Ui::Dialog_linkstack_push *ui;
};

#endif // DIALOG_LINKSTACK_PUSH_H
