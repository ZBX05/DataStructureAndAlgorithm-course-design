#ifndef DIALOG_GRAPH_EDITEDGE_H
#define DIALOG_GRAPH_EDITEDGE_H

#include <QDialog>

namespace Ui {
class Dialog_graph_editedge;
}

class Dialog_graph_editedge : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_graph_editedge(QWidget *parent = nullptr);
    ~Dialog_graph_editedge();
    void setBox(char *vertex,int len);
    void getPos(QString &from,QString &to);
    int getValue();
private:
    Ui::Dialog_graph_editedge *ui;
};

#endif // DIALOG_GRAPH_EDITEDGE_H
