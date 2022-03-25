//metier chat
#include "dialog.h"
#include "ui_dialog.h"
#include <QTcpSocket>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
}

Dialog::~Dialog()
{
    delete ui;
}

