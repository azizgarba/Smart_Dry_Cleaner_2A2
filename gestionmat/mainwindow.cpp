#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QRegularExpression
            QRegExp("[a-zA-Z]+");
    QRegularExpressionValidator *validator = new
            QRegularExpressionValidator(QRegExp,this);
    ui->setupUi(this);
    ui->tableView->setModel(mtmp.afficher());
    ui->modele->setValidator(validator);
    ui->temperature->setValidator(new QIntValidator(0,9999));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_valider_clicked()
{
    QString model_m=ui->modele->text();
    QString date_acham=ui->dateachat->text();
    QString  tempera_m=ui->temperature->text();
    QString  ref_m=ui->reference->text();
    QString etat_m=ui->etat->text();

materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m);
bool test=mo.ajouter();
ui->modele->setText("");
ui->temperature->setText("");
ui->reference->setText("");
ui->etat->setText("");

if(test)
{
    ui->tableView->setModel(mtmp.afficher());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("ajout effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                             QObject::tr("ajout non effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);


}


void MainWindow::on_supprimer_clicked()
{ materiel m;
   m.setRef_m(ui->reference->text());
   bool test=mtmp.supprimer(m);
   ui->reference->setText("");
   ui->modele->setText("");
   ui->temperature->setText("");
   ui->etat->setText("");
   if(test)
   {
       ui->tableView->setModel(mtmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("suppression effectué \n"
                                            "click cancel to exit."),QMessageBox::Cancel);
   }
   else
       QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                QObject::tr("suppression non effectué \n"
                                            "click cancel to exit."),QMessageBox::Cancel);
}





void MainWindow::on_modifier_clicked()
{
    QString model_m=ui->modele->text();
    QString date_acham=ui->dateachat->text();
    QString  tempera_m=ui->temperature->text();
    QString  ref_m=ui->reference->text();
    QString etat_m=ui->etat->text();

materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m);
bool test=mo.modifier();
ui->modele->setText("");
ui->temperature->setText("");
ui->reference->setText("");
ui->etat->setText("");

if(test)
{
    ui->tableView->setModel(mtmp.afficher());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("modification effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                             QObject::tr("modification non effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);


}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
  QString val=ui->tableView->model()->data(index).toString();
  QSqlQuery query;
  query.prepare("SELECT REF_M,DATE_ACHAM,MODEL_M,TEMPERA_M,ETAT_M FROM MATERIELS WHERE REF_M='"+val+"' or DATE_ACHAM='"+val+"' or MODEL_M='"+val+"'or TEMPERA_M='"+val+"' or ETAT_M='"+val+"' ");
  if (query.exec())
  {
      while(query.next())
      {
          ui->reference->setText(query.value(0).toString());
         ui->dateachat->setDate(query.value(1).toDate());
          ui->modele->setText(query.value(2).toString());
          ui->temperature->setText(query.value(3).toString());
          ui->etat->setText(query.value(4).toString());

      }

  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("not OK"),
                               QObject::tr("error \n"
                                           "click cancel to exit."),QMessageBox::Cancel);
  }
}

void MainWindow::on_afficher_clicked()
{

    QString model_m=ui->modele->text();
    QString date_acham=ui->dateachat->text();
    QString  tempera_m=ui->temperature->text();
    QString  ref_m=ui->reference->text();
    QString etat_m=ui->etat->text();

    materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m);

    bool test=mo.afficher();
    ui->tableView->setModel(mtmp.afficher());
     if(test)
     {
         ui->tableView->setModel(mtmp.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("affichage effectué \n"
                                              "click cancel to exit."),QMessageBox::Cancel);
     }
     else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                  QObject::tr("affichge non effectué \n"
                                              "click cancel to exit."),QMessageBox::Cancel);

     if (QString::number(ui->trie->currentIndex())=="0")
     {
         ui->tableView->setModel(mtmp.triedate());
     }

     else if(QString::number(ui->trie->currentIndex())=="1")
     {
         ui->tableView->setModel(mtmp.trieetat());
     }
     else if(QString::number(ui->trie->currentIndex())=="2")
     {
         ui->tableView->setModel(mtmp.trienbrproduit());
     }


}















