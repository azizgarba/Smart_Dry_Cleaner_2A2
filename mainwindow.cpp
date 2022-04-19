#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "excel.h"
#include "materiel.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QRegularExpression
            QRegExp("[a-zA-Z]+");
    QRegularExpression
            QRegExp1("^[0-2]*$");
    QRegularExpressionValidator *validator = new
            QRegularExpressionValidator(QRegExp,this);
            QRegularExpressionValidator *validator1 = new
                    QRegularExpressionValidator(QRegExp1,this);

           // QPixmap pix1(":/Users/User/Desktop/projet qt/im.jpg");
           // ui->image->setPixmap(pix1);
    ui->setupUi(this);
    ui->affmate->setModel(mtmp.afficher());
    ui->modele->setValidator(validator);
    ui->temperature->setValidator(new QIntValidator(0,9999));
    ui->ecricherche->setPlaceholderText("Cherchez ici...");


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

    QString etat_m;
    if(ui->panne->isChecked())
        etat_m="0";
    else if(ui->pause->isChecked())
        etat_m="1";
    else if(ui->marche->isChecked())
        etat_m="2";
    QString image_m=ui->image->text();


materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m,image_m);
mo.ajouter_valid(ui->reference->text());
bool test=mo.ajouter();
ui->modele->setText("");
ui->temperature->setText("");
ui->reference->setText("");
QImage pix(":/Users/User/Desktop/projet qt/im.jpg");
ui->image->setPixmap(QPixmap::fromImage(pix));
       pix = pix.scaledToWidth(ui->image->width(), Qt::SmoothTransformation);
//QPixmap pix1("C:/Users/User/Desktop/projet qt/im.jpg");
//ui->image->setPixmap(pix1);




if(test)
{
    ui->affmate->setModel(mtmp.afficher());
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
    m.ajouter_suppri(ui->reference->text());
   m.setRef_m(ui->reference->text());
   bool test=mtmp.supprimer(m);
   ui->reference->setText("");
   ui->modele->setText("");
   ui->temperature->setText("");
   //QPixmap pix1(":/Users/User/Desktop/projet qt/im.jpg");
  // ui->image->setPixmap(pix1);

   if(test)
   {
       ui->affmate->setModel(mtmp.afficher());
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
   // QString etat_m=ui->etat->text();
    QString etat_m;
    if(ui->panne->isChecked())
        etat_m="0";
    else if(ui->pause->isChecked())
        etat_m="1";
    else if(ui->marche->isChecked())
        etat_m="2";
    QString image_m=ui->image->text();


materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m,image_m);
mo.ajouter_modif(ui->reference->text());
bool test=mo.modifier();
ui->modele->setText("");
ui->temperature->setText("");
ui->reference->setText("");
ui->image->setText("");
//QPixmap pix1(":/Users/User/Desktop/projet qt/im.jpg");
//ui->image->setPixmap(pix1);


QDate date = QDate::currentDate();
  ui->dateachat->setDate(date);
if(test)
{
    ui->affmate->setModel(mtmp.afficher());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("modification effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                             QObject::tr("modification non effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);


}




void MainWindow::on_afficher_clicked()
{

    QString model_m=ui->modele->text();
    QString date_acham=ui->dateachat->text();
    QString  tempera_m=ui->temperature->text();
    QString  ref_m=ui->reference->text();
    QString etat_m;
    if(ui->panne->isChecked())
        etat_m="0";
    else if(ui->pause->isChecked())
        etat_m="1";
    else if(ui->marche->isChecked())
        etat_m="2";
    QString image_m=ui->image->text();
    materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m,image_m);

    bool test=mo.afficher();

     if(test)
     {
         ui->affmate->setModel(mtmp.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("affichage effectué \n"
                                              "click cancel to exit."),QMessageBox::Cancel);
     }
     else{
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                  QObject::tr("affichge non effectué \n"
                                              "click cancel to exit."),QMessageBox::Cancel);}

     if (QString::number(ui->trie->currentIndex())=="0")
     {
         ui->affmate->setModel(mtmp.triedate());
     }

     else if(QString::number(ui->trie->currentIndex())=="1")
     {
         ui->affmate->setModel(mtmp.trieetat());
     }
     else if(QString::number(ui->trie->currentIndex())=="2")
     {
         ui->affmate->setModel(mtmp.trienbrproduit());
     }


}

void MainWindow::on_ecricherche_textChanged(const QString &arg1)
{
    QSqlQueryModel query;
    QString model_m=ui->modele->text();
    QString date_acham=ui->dateachat->text();
    QString  tempera_m=ui->temperature->text();
    QString  ref_m=ui->reference->text();

    QString etat_m;
    if(ui->panne->isChecked())
        etat_m="0";
    else if(ui->pause->isChecked())
        etat_m="1";
    else if(ui->marche->isChecked())
        etat_m="2";
    QString image_m=ui->image->text();

materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m,image_m);

bool test=mo.afficher();
    ui->affmate->setModel(mtmp.chercher(arg1));

}


void MainWindow::on_insererim_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr(" (*.png *.jpg *.jpeg)"));
   // QFileInfo file("filename");//houni 3mlt modif
      // qDebug() << file.absolutePath() << file.exists();

        if(QString::compare(filename, QString()) !=0 )
        {
            QImage image;
            bool valid = image.load(filename);
            if(valid)
            {
                image = image.scaledToWidth(ui->image->width(), Qt::SmoothTransformation);

                ui->image->setPixmap(QPixmap::fromImage(image));
                 image.save(filename);

            }
            else
            {
    //error handling
            }
        }


}


void MainWindow::on_afficherexcel_clicked()
{/*
    QString model_m=ui->modele->text();
    QString date_acham=ui->dateachat->text();
    QString  tempera_m=ui->temperature->text();
    QString  ref_m=ui->reference->text();

    QString etat_m;
    if(ui->panne->isChecked())
        etat_m="0";
    else if(ui->pause->isChecked())
        etat_m="1";
    else if(ui->marche->isChecked())
        etat_m="2";
    QString image_m=ui->image->text();

materiel mo(ref_m,model_m,etat_m,date_acham,tempera_m,image_m);

        QTableView *table=new QTableView;
        table->setModel(mo.afficherMachineForExcel());



                   QString filters("CSV files (*.csv) ;; All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");//
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);//d:fenetre d'enrgtr
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();
                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {//tc:type de fch
                       QTextStream data(&file);
                       QStringList strList;//separation des chaines


                       for (int i = 0; i < model->columnCount(); i++)
                       {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");
                       }

                       data << strList.join(";") << "\n";


                       for (int i = 0; i < model->rowCount(); i++)
                       {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++)
                           {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                       data << strList.join(";") + "\n";
                       }
                       file.close();
                       QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                                 QObject::tr("Export avec succes .\n"
                                                             "Click OK to exit."), QMessageBox::Ok);
                   }

*/




    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                                  tr("Excel Files (*.xls)"));
                  if (fileName.isEmpty())
                      return;

                  excel obj(fileName, "Produit", ui->affmate);

                  //colums to export
                  obj.addField(0, "model", "char(20)");
                  obj.addField(1, "reference", "char(20)");
                  obj.addField(2, "¨date", "char(20)");
                  obj.addField(3, "etat", "char(20)");
                  obj.addField(4, "temperature", "char(20)");




                  int retVal = obj.export2Excel();
                  if( retVal > 0)
                  {
                      QMessageBox::information(this, tr("Done"),
                                               tr("Tous les informations ont été enregistrée"));
                  }



}


void MainWindow::on_historique_clicked()
{
materiel mo;
ui->affhisto->setModel(mo.afficher_historique());
}


void MainWindow::on_affmate_activated(const QModelIndex &index)
{
    QString val=ui->affmate->model()->data(index).toString();
    QSqlQuery query;
    QString date;
    query.prepare("SELECT REF_M,DATE_ACHAM,MODEL_M,TEMPERA_M,ETAT_M FROM MATERIELS WHERE REF_M='"+val+"' or DATE_ACHAM='"+val+"' or MODEL_M='"+val+"'or TEMPERA_M='"+val+"' or ETAT_M='"+val+"' ");
    if (query.exec())
    {
        while(query.next())
        {
            ui->reference->setText(query.value(0).toString());
            date = query.value(1).toString();

            QDate Date = QDate::fromString(date,"M/d/yyyy");
            ui->dateachat->setDate(Date);
            ui->modele->setText(query.value(2).toString());
            ui->temperature->setText(query.value(3).toString());

            if(query.value(4).toString()=="0")
                    ui->panne->setChecked(true);
            else if(query.value(4).toString()=="1")
                    ui->pause->setChecked(true);
            else if(query.value(4).toString()=="2")
                    ui->marche->setChecked(true);

        }

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                                 QObject::tr("error \n"
                                             "click cancel to exit."),QMessageBox::Cancel);
    }

}

