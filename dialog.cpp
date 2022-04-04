//metier chat
#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QHostAddress me(get_ip());

      ui->setupUi(this);
      clientSocket=new QUdpSocket(this);
      clientSocketc=new QUdpSocket(this);
      clientSocketc->bind(me, 7000);
      connect(clientSocketc,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_envoyer_clicked()
{
    QString word=ui->msg->text();
       ui->textBrowser->append(word);
       QByteArray buffer;
       buffer.resize(clientSocket->pendingDatagramSize());
       QHostAddress sender;
       quint16 senderPort;
       buffer=word.toUtf8();
       clientSocketc->writeDatagram(buffer.data(), QHostAddress::Broadcast, 8001 );
       ui->msg->clear();
}


