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
        ui->lineEdit_10->setValidator(validator);
        ui->lineEdit_9->setValidator(validator);
        
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
         ui->treeView->setModel(pr.afficher());

}
//--------------------------------offre
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



