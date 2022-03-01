#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString numero=ui->le_numero->text();
    QString adresse=ui->le_adresse->text();
    int paiment=ui->le_paiment->text().toInt();
    QString date=ui->le_date->text();
 Fournisseur F(cin,nom,numero,adresse,paiment,date);
 F.ajouter();
}
