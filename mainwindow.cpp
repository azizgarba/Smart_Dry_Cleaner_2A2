#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QString>
#include <QValidator>
#include <QMessageBox>
#include <QDebug>
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
    ui->le_cin->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_numero->setValidator(new QIntValidator(100, 99999999, this));


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
 bool test=F.ajouter();
 if (test)
         {
             Fournisseur Fe;
             ui->tab_fournisseurs->setModel(Fe.afficher());
             QMessageBox::information(nullptr, QObject::tr("ok"),
                                      QObject::tr("Ajout effectué.\n"
                                                  "Click cancel to exit."), QMessageBox::Cancel);
         }
         else
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                   QObject::tr("Ajout non effectué.\n"
                                               "Click cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_ajouter_pressed()
{
    ui->pb_ajouter->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow::on_pb_ajouter_released()
{
    ui->pb_ajouter->setStyleSheet("QPushButton{background-color: rgb(0, 129, 233)}");
}




















void MainWindow::on_le_aff_clicked()
{
    Fournisseur Fe;
    ui->tab_fournisseurs->setModel(Fe.afficher());
    //afficher selon le nom
     if(QString::number(ui->pb_tri->currentIndex())=="0"){
      ui->tab_fournisseurs->setModel(Fe.afficher_fournis_par_nom());
     }
     //afficher selon le prenom
     else if(QString::number(ui->pb_tri->currentIndex())=="1"){
        ui->tab_fournisseurs->setModel(Fe.afficher_fournis_par_achat());
     }
     //afficher selon l'age
     else if(QString::number(ui->pb_tri->currentIndex())=="2"){
         ui->tab_fournisseurs->setModel(Fe.afficher_fournis_par_date());
     }
}





void MainWindow::on_pb_supprimer_clicked()
{
    QItemSelectionModel *select = ui->tab_fournisseurs->selectionModel();
                   int cin =select->selectedRows().value(0).data().toInt();
                   if(ftmp.supprimer(cin))
                   {
                       ui->tab_fournisseurs->setModel(ftmp.afficher());
                       ui->statusbar->showMessage("SUPPRESSION : SUCCESS");
                   }


}


void MainWindow::on_pb_supprimer_pressed()
{
     ui->pb_supprimer->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}


void MainWindow::on_pb_supprimer_released()
{
     ui->pb_supprimer->setStyleSheet("QPushButton{background-color: rgb(0, 129, 233)}");
}

;




void MainWindow::on_pb_modifier_clicked()
{
           int cin=ui->le_cin->text().toInt();
           QString nom=ui->le_nom->text();
           QString numero=ui->le_numero->text();
           QString adresse=ui->le_adresse->text();
           int paiment=ui->le_paiment->text().toInt();
           QString date=ui->le_date->text();

            Fournisseur F(cin,nom,numero,adresse,paiment,date);


                       bool test=F.modifier();

                       if (test)
                               {
                                   Fournisseur Fe;
                                   ui->tab_fournisseurs->setModel(Fe.afficher());
                                   QMessageBox::information(nullptr, QObject::tr("ok"),
                                                            QObject::tr("Modification effectué.\n"
                                                                        "Click cancel to exit."), QMessageBox::Cancel);
                               }
                               else
                                   QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                                         QObject::tr("Modification non effectué.\n"
                                                                     "Click cancel to exit."), QMessageBox::Cancel);

  }






void MainWindow::on_tab_fournisseurs_activated(const QModelIndex &index)
{
    QString val=ui->tab_fournisseurs->model()->data(index).toString();
        QString sQuery="SELECT FOURNIS_ID, NOM_F, NUMERO_TEL, ADRESSE_F, PAIMENT_ACHAT_F, DATE_CONTRAT FROM FOURNISSEURS WHERE FOURNIS_ID='"+val+"' or NOM_F='"+val+"' or NUMERO_TEL='"+val+"' or ADRESSE_F='"+val+"' or PAIMENT_ACHAT_F='"+val+"' or DATE_CONTRAT='"+val+"'";
        QSqlQuery qry;
        qry.prepare(sQuery);

        if(qry.exec()){

                        while(qry.next())

                                {
                                    ui->le_cin->setText(qry.value(0).toString());
                                    ui->le_nom->setText(qry.value(1).toString());
                                    ui->le_numero->setText(qry.value(2).toString());
                                    ui->le_adresse->setText(qry.value(3).toString());
                                    ui->le_paiment->setText(qry.value(4).toString());
                                    ui->le_date->setDate(qry.value(5).toDate());


                                }
        }

}





void MainWindow::on_pb_tri_activated(const QString &arg1)
{

}
