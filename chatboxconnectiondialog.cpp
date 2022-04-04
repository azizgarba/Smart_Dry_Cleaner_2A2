#include "chatboxconnectiondialog.h"
#include "ui_chatboxconnectiondialog.h"

ChatboxConnectionDialog::ChatboxConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatboxConnectionDialog)
{
    ui->setupUi(this);
}

ChatboxConnectionDialog::~ChatboxConnectionDialog()
{
    delete ui;
}

void ChatboxConnectionDialog::on_ok_clicked()
{
    nHostname = ui->hostname->text();
       nPort = ui->port->value();
       accept();
}

void ChatboxConnectionDialog::on_pushButton_2_clicked()
{
    reject();
}
