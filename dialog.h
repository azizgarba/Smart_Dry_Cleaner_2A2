//metier chat
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class Dialog;
}

class QTcpSocket;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


private:
    Ui::Dialog *ui;
    QTcpSocket *mSocket;
};

#endif // DIALOG_H
