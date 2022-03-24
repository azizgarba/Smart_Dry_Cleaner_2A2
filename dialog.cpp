//metier chat
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_chat_pressed()
{
    ui->chat->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void Dialog::on_chat_released()
{
    ui->chat->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}
