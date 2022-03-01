#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include<QWidget>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_ajouter_clicked()
{
    int id_e=ui->lineEdit_ID->text().toInt();
        QString nom_e=ui->lineEdit_nom->text();
        QString prenom_e=ui->lineEdit_prenom->text();
        QString numero_e=ui->lineEdit_num->text();
        QString adresse_e=ui->lineEdit_adr->text();
        Employee E(id_e,nom_e,prenom_e,numero_e,adresse_e);

        bool test=E.ajouter();

        if (test)
        {
            ui->tableView->setModel(etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Ajout effectué.\n"
                                                 "Click cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "Click cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_ajouter_pressed()
{
    ui->pushButton_ajouter->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow::on_pushButton_ajouter_released()
{
    ui->pushButton_ajouter->setStyleSheet("QPushButton{background-color: rgb(0, 129, 233)}");
}


void MainWindow::on_pushButton_modif_clicked()
{
    int id_e=ui->lineEdit_ID->text().toInt();
        QString nom_e=ui->lineEdit_nom->text();
        QString prenom_e=ui->lineEdit_prenom->text();
        QString numero_e=ui->lineEdit_num->text();
        QString adresse_e=ui->lineEdit_adr->text();


        Employee E(id_e,nom_e,prenom_e,numero_e,adresse_e);

                    bool test=E.modifier();
                    if(test)

                        {
                        QMessageBox::information(nullptr,QObject::tr("Ok"),
                                             QObject::tr("Modification effectuée\n"
                                                           "Click cancel to exit."),QMessageBox::Cancel);
                        ui->tableView->setModel(E.afficher());
                        }
                    else
                        {
                        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                             QObject::tr("Modification non effectuée\n"
                                                           "Click cancel to exit."),QMessageBox::Cancel);
                        }
}



void MainWindow::on_pushButton_modif_pressed()
{
    ui->pushButton_modif->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow::on_pushButton_modif_released()
{
    ui->pushButton_modif->setStyleSheet("QPushButton{background-color: rgb(0, 129, 233)}");
}

void MainWindow::on_pushButton_supp_clicked()
{
    /* Employee E;
        E.setid(ui->lineEdit_ID->text().toInt());
        bool test=etmp.supprimer(E.get_id());

        if (test)
        {
            ui->tableView->setModel(etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Suppression effectué.\n"
                                                 "Click cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                  QObject::tr("Suppression non effectué.\n"
                                              "Click cancel to exit."), QMessageBox::Cancel);*/

        QItemSelectionModel *select = ui->tableView->selectionModel();
               int id_e =select->selectedRows().value(0).data().toInt();
               if(etmp.supprimer(id_e))
               {
                   ui->tableView->setModel(etmp.afficher());
                   ui->statusbar->showMessage("SUPPRESSION : SUCCESS");
               }
}

void MainWindow::on_pushButton_supp_pressed()
{
    ui->pushButton_supp->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow::on_pushButton_supp_released()
{
    ui->pushButton_supp->setStyleSheet("QPushButton{background-color: rgb(0, 129, 233)}");
}
