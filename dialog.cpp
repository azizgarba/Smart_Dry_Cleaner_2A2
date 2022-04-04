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


QString Dialog::get_ip()
{
    QProcess process;
    process.start("ipconfig");
    process.waitForFinished(-1); // will wait forever until finished

    QString output = process.readAllStandardOutput();
    QString errors = process.readAllStandardError();

    int pos=output.toStdString().find("Wi-Fi");
    QRegularExpression ip_regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]+)");
    QRegularExpressionMatch ip_match=ip_regex.match(output.mid(pos+50,220));

    qDebug() <<ip_match.captured(0);

    return ip_match.captured(0);
}


void Dialog::readPendingDatagrams()
{
    while (clientSocketc->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(clientSocketc->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        clientSocketc->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
        ui->textBrowser->append(buffer.data());

    }

}
