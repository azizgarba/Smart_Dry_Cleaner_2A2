//metier chat
#include "dialog.h"
#include "ui_dialog.h"
#include "chatboxconnectiondialog.h"
#include <QTcpSocket>
#include <QTextStream>
#include "chatboxconnectiondialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    nSocket=new QTcpSocket(this);
    connect(nSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(nSocket);
        auto text=T.readAll();
        ui->textEdit->append(text);
    });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_send_clicked()
{
    QTextStream T(nSocket);
    T << ui->lineEdit-> text() << ": " << ui->message->text();
    nSocket->flush();
    ui->message->clear();
}

void Dialog::on_bind_clicked()
{
    ChatboxConnectionDialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;
    }
    nSocket->connectToHost(D.hostname(),D.port());
}
