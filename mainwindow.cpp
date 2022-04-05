#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include "excel.h"
#include "offre.h"
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include<QWidget>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>
#include <QRadioButton>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



/**************/
      ui->lineEdit_7->setPlaceholderText("  Chercher(Id-Type)...");
          QRegularExpression QRegExp( "[a-zA-Z]+");
          QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegExp,this);
          ui->lineEdit_2->setValidator(validator);
          ui->lineEdit_3->setValidator(validator);
          ui->lineEdit_5->setValidator(validator);
          ui->lineEdit->setValidator(new QIntValidator(0,9999,this));
          ui->lineEdit_4->setValidator(new QIntValidator(0,9999999,this));
          //------------------
          ui->lineEdit_8->setValidator(new QIntValidator(0,9999,this));
          ui->lineEdit_9->setValidator(validator);
            ui->lineEdit_10->setValidator(new QIntValidator(0,9999999,this));

      ui->treeView->setModel(pr.afficher());
      ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
      ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
                  //offre
              ui->treeView_2->setModel(of.afficherOffre());
              ui->treeView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
              ui->treeView_2->setSelectionMode(QAbstractItemView::SingleSelection);




}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    int produit_id=ui->lineEdit->text().toInt();
    QString type= ui->lineEdit_2->text();
    QString matiere= ui->lineEdit_3->text();
    QString etat_p= ui->lineEdit_5->text();
    int prix= ui->lineEdit_4->text().toInt();


   produit p(produit_id, type, matiere, etat_p, prix);
    p.ajouter() ;

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/rania/OneDrive/Bureau/hydro.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion d'un produit","Un produit a été ajoutée",QSystemTrayIcon::Information,15000);



    ui->treeView->setModel(pr.afficher());


}
void MainWindow::on_pushButton_7_clicked()
{
                 QItemSelectionModel *select = ui->treeView->selectionModel();
                   int produit_id =select->selectedRows().value(0).data().toInt();
                   if(pr.supprimer(produit_id))
                   {
                       ui->treeView->setModel(pr.afficher());

                   }
                   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->setIcon(QIcon("C:/Users/rania/OneDrive/Bureau/hydro.png"));
                   notifyIcon->show();
                   notifyIcon->showMessage("Gestion d'un produit","Un produit a été supprimée",QSystemTrayIcon::Information,15000);


}

void MainWindow::on_pushButton_6_clicked()
{

       int d =ui->lineEdit->text().toInt();
        QString t= ui->lineEdit_2->text();
        QString m= ui->lineEdit_3->text();
        QString e= ui->lineEdit_5->text();
        int prr = ui->lineEdit_4->text().toInt();


         produit p (d, t, m, e, prr);
         QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
         notifyIcon->setIcon(QIcon("C:/Users/rania/OneDrive/Bureau/hydro.png"));
         notifyIcon->show();
         notifyIcon->showMessage("Gestion d'un produit","Un produit a été modifiée",QSystemTrayIcon::Information,15000);


         p.modifier() ;

         ui->treeView->setModel(pr.afficher());

}
void MainWindow::on_pushButton_clicked()
{
    int offre_id=ui->lineEdit_8->text().toInt();
    QString type_p= ui->lineEdit_10->text();
    QString reduction= ui->lineEdit_9->text();



    offre o(offre_id, reduction, type_p);
    o.ajouterOffre() ;
    ui->treeView_2->setModel(of.afficherOffre());
}

void MainWindow::on_pushButton_4_clicked()
{
    QItemSelectionModel *select = ui->treeView_2->selectionModel();
                   int offre_id =select->selectedRows().value(0).data().toInt();
                   if(of.supprimerOffre(offre_id))
                   {
                       ui->treeView_2->setModel(of.afficherOffre());

                   }
}

void MainWindow::on_pushButton_3_clicked()
{

    int offre_id=ui->lineEdit_8->text().toInt();
    QString type_p= ui->lineEdit_10->text();
    QString reduction= ui->lineEdit_9->text();



    offre o(offre_id,reduction,type_p);

    o.modifierOffre() ;
    ui->treeView_2->setModel(of.afficherOffre());



}


/***************************METIER***********************/
void MainWindow::on_pushButton_5_clicked()
{
         QString rech =ui->lineEdit_7->text();
         ui->treeView->setModel(pr.rechercher(rech));

}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->radioButton->isChecked())
        {
            ui->treeView->setModel(pr.trier_produit_id());
        }
        else if(ui->radioButton_2->isChecked())
        {
            ui->treeView->setModel(pr.trier_etat_p());
        }
    else if(ui->radioButton_3->isChecked())
    {
        ui->treeView->setModel(pr.trier_prix());
    }

}


void MainWindow::on_treeView_activated(const QModelIndex &index)
{
    QString val=ui->treeView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from produit where produit_id='"+val+"' or type='"+val+"' or matiere='"+val+"' or etat_p='"+val+"' or prix='"+val+"'");

       if (qry.exec())
       {
           while (qry.next())
           {
               ui->lineEdit->setText(qry.value(0).toString());
               ui->lineEdit_2->setText(qry.value(1).toString());
               ui->lineEdit_3->setText(qry.value(2).toString());
               ui->lineEdit_4->setText(qry.value(3).toString());
               ui->lineEdit_5->setText(qry.value(4).toString());
           }
       }
}

void MainWindow::on_treeView_2_activated(const QModelIndex &index)
{
    QString val=ui->treeView_2->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from offre where offre_id='"+val+"' or type_p='"+val+"' or reduction='"+val+"'");

       if (qry.exec())
       {
           while (qry.next())
           {
               ui->lineEdit_8->setText(qry.value(0).toString());
               ui->lineEdit_9->setText(qry.value(1).toString());
               ui->lineEdit_10->setText(qry.value(2).toString());

           }
       }
}


void MainWindow::on_pushButton_9_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                              tr("Excel Files (*.xls)"));
              if (fileName.isEmpty())
                  return;

              ExportExcel obj(fileName, "Produit", ui->treeView);

              //colums to export
              obj.addField(0, "ID", "char(20)");
              obj.addField(1, "Type", "char(20)");
              obj.addField(2, "¨Matiere", "char(20)");
              obj.addField(3, "Prix", "char(20)");
              obj.addField(4, "Etat", "char(20)");




              int retVal = obj.export2Excel();
              if( retVal > 0)
              {
                  QMessageBox::information(this, tr("Done"),
                                           tr("Tous les informations ont été enregistrée"));
              }
}
