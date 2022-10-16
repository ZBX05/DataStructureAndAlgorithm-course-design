#ifndef DIALOG_GRAPH_DELETE_H
#define DIALOG_GRAPH_DELETE_H

#include <QDialog>

namespace Ui {
class Dialog_graph_delete;
}

class Dialog_graph_delete : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_graph_delete(QWidget *parent = nullptr);
    ~Dialog_graph_delete();
    void setBox(char *vertex,int len);
    void getPos(QString &from,QString &to);
private:
    Ui::Dialog_graph_delete *ui;
};

#endif // DIALOG_GRAPH_DELETE_H
