#include "widget.h"
#include "ui_widget.h"
#include "chatboxconnectiondialog.h"
#include <QTcpSocket>
#include <QTextStream>

namespace DuarteCorporation{
widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);
    nSocket=new QTcpSocket(this);
    connect(nSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(nSocket);
        auto text=T.readAll();
        ui->textEdit->append(text);
    });
}

widget::~widget()
{
    delete ui;
}


void DuarteCorporation::widget::on_send_clicked()
{
    QTextStream T(nSocket);
    T << ui->lineEdit-> text() << ": " << ui->message->text();
    nSocket->flush();
    ui->message->clear();
}

void DuarteCorporation::widget::on_bind_clicked()
{
    ChatboxConnectionDialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;
    }
    nSocket->connectToHost(D.hostname(),D.port());
    }
}
