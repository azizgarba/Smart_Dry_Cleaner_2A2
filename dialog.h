//metier chat
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QUdpSocket>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QNetworkInterface>

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


private slots:
    void on_envoyer_clicked();
    void readPendingDatagrams();
    QString get_ip();

private:
    Ui::Dialog *ui;
    QUdpSocket *clientSocket;
    QUdpSocket *clientSocketc;
};

#endif // DIALOG_H
