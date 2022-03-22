#include "gemployee.h"
#include "ui_gemployee.h"

GEmployee::GEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GEmployee)
{
    ui->setupUi(this);
}

GEmployee::~GEmployee()
{
    delete ui;
}
