#include "widget.h"
#include "ui_widget.h"
#include "chatboxconnectiondialog.h"
#include <QTcpSocket>
#include <QTextStream>

#include "QTranslator"
#include "QInputDialog"
#include "QApplication"

DuarteCorporation::Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    nSocket=new QTcpSocket(this);
        connect(nSocket,&QTcpSocket::readyRead,[&](){
            QTextStream T(nSocket);
            auto text=T.readAll();
            ui->textEdit->append(text);
        });
}

DuarteCorporation::Widget::~Widget()
{
    delete ui;
}

void DuarteCorporation::Widget::on_pushButton_clicked()
{
    QTextStream T(nSocket);
    T << ui->lineEdit_2-> text() << ": " << ui->lineEdit->text();
    nSocket->flush();
    ui->lineEdit->clear();
}

void DuarteCorporation::Widget::on_pushButton_2_clicked()
{
    ChatboxConnectionDialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;
    }
    nSocket->connectToHost(D.hostname(),D.port());
}

