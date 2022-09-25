#ifndef DIALOG_ARRLIST_LOAD_H
#define DIALOG_ARRLIST_LOAD_H

#include <QDialog>

namespace Ui {
class Dialog_arrlist_load;
}

class Dialog_arrlist_load : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_arrlist_load(QWidget *parent = nullptr);
    ~Dialog_arrlist_load();
    int getValue();
private:
    Ui::Dialog_arrlist_load *ui;
};

#endif // DIALOG_ARRLIST_LOAD_H
