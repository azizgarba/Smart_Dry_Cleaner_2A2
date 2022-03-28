//metier chat
#include "dialog.h"
#include "ui_dialog.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QLineEdit>
#include <QTextBrowser>

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

void Dialog::on_envoyer_clicked()
{
    QTextStream T(mSocket);
    T << ui->nom->text() << ":  " << ui->msg->text();
    mSocket->flush();
    ui->msg->clear();
}


