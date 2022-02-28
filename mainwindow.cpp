#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include "offre.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
       //produit
    ui->setupUi(this);
    ui->tableView->setModel(pr.afficher());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
                //offre
            ui->tableView_2->setModel(of.afficherOffre());
            ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//------------------produit-------------------------
void MainWindow::on_pushButton_2_clicked()
{

    int produit_id=ui->lineEdit->text().toInt();
    QString type= ui->lineEdit_2->text();
    QString matiere= ui->lineEdit_3->text();
    QString etat_p= ui->lineEdit_5->text();
    int prix= ui->lineEdit_4->text().toInt();


   produit p(produit_id, type, matiere, etat_p, prix);
    p.ajouter() ;
    ui->tableView->setModel(pr.afficher());
}

void MainWindow::on_pushButton_7_clicked()
{

    produit p;
    p.setproduit_id(ui->lineEdit_6->text().toInt());
    p.supprimer();
     ui->tableView->setModel(pr.afficher());



}

void MainWindow::on_pushButton_6_clicked()
{

    int d =ui->lineEdit->text().toInt();
    QString t= ui->lineEdit_2->text();
    QString m= ui->lineEdit_3->text();
    QString e= ui->lineEdit_5->text();
    int prr = ui->lineEdit_4->text().toInt();


     produit p (d, t, m, e, prr);
     p.modifier() ;
     ui->tableView->setModel(pr.afficher());

}
//--------------------------------offre
void MainWindow::on_pushButton_clicked()
{
    int offre_id=ui->lineEdit_8->text().toInt();
    QString type_p= ui->lineEdit_10->text();
    QString reduction= ui->lineEdit_9->text();



    offre o(offre_id, type_p, reduction);
    o.ajouterOffre() ;
    ui->tableView_2->setModel(of.afficherOffre());
}

void MainWindow::on_pushButton_4_clicked()
{
    offre O;
    O.setoffre_id(ui->lineEdit_11->text().toInt());
    O.supprimerOffre();
     ui->tableView_2->setModel(of.afficherOffre());

}

void MainWindow::on_pushButton_3_clicked()
{

    int offre_id=ui->lineEdit_8->text().toInt();
    QString type_p= ui->lineEdit_10->text();
    QString reduction= ui->lineEdit_9->text();



    offre o(offre_id, type_p, reduction);
    o.modifierOffre() ;
    ui->tableView_2->setModel(of.afficherOffre());



}



void MainWindow::on_pushButton_5_clicked()
{
         QString rech =ui->lineEdit_7->text();
         ui->tableView->setModel(pr.rechercher(rech));

}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->radioButton->isChecked())
        {
            ui->tableView->setModel(pr.trier_produit_id());
        }
        else if(ui->radioButton_2->isChecked())
        {
            ui->tableView->setModel(pr.trier_etat_p());
        }
    else if(ui->radioButton_3->isChecked())
    {
        ui->tableView->setModel(pr.trier_prix());
    }

}

