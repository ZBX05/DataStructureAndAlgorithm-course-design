#ifndef DIALOG_ARRLIST_DELETE_H
#define DIALOG_ARRLIST_DELETE_H

#include <QDialog>

namespace Ui {
class Dialog_arrlist_delete;
}

class Dialog_arrlist_delete : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_arrlist_delete(QWidget *parent = nullptr);
    ~Dialog_arrlist_delete();
    void setBox(int len);
    void setBox(char *str,int len);
    int getPos();
    QString getVertexPos();
private:
    Ui::Dialog_arrlist_delete *ui;
};

#endif // DIALOG_ARRLIST_DELETE_H
