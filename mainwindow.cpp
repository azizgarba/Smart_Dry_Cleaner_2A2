#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QString>
#include <QValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDebug>
#include<QWidget>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>
#include "qcustomplot.h"
#include "connection.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_numero->setValidator(new QIntValidator(100, 99999999, this));
    ui->recherche->setPlaceholderText("Rechercher");


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

void MainWindow::on_recherche_textChanged(const QString &arg1)
{

    Fournisseur Fe;
    ui->tab_fournisseurs->setModel(Fe.chercher(arg1));

}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_pdf_aff_clicked()
{   QString numero,adresse,date,nom,cin,paiment;

    QString space=" ";
    numero=ui->le_numero->text();
    adresse=ui->le_adresse->text();
    date=ui->le_date->text();
    nom=ui->le_nom->text();
    cin=ui->le_cin->text();
    paiment=ui->le_paiment->text();


    QPdfWriter pdf("C:/Users/ThinkPad/Desktop/projet c++ 2eme/fournisseur/pdf_four.pdf");

    QPainter painter(&pdf);

    painter.setPen(Qt::blue);
    painter.drawText(4200,200,"Hydro+ pressing:Fournisseurs");
    painter.drawText(100,1100,"CIN :"+space+""+cin+"");
    painter.drawText(100,1300,"date :"+space+""+date+"");

    painter.drawPixmap(QRect(-300,-300,1500,1000),QPixmap("C:/Users/ThinkPad/Desktop/projet c++ 2eme/fournisseur/logo.png"));



    painter.end();

  QDesktopServices::openUrl(QUrl("file:///C:/Users/ThinkPad/Desktop/projet%20c++%202eme/fournisseur/pdf_four.pdf"));
}


void MainWindow::on_traduire_clicked()
{
    QString test ;
    test = ui->label_3->text();
    if(test=="Nombre")
    {


           ui->label_2->setText("Name");
           ui->label_3->setText("Numbre");
           ui->label_4->setText("Address");
           ui->label_5->setText("Payment");
           ui->label_7->setText("Sort by");
           ui->label_8->setText("Translate to Frensh");
           ui->pb_ajouter->setText("ADD");
           ui->pb_modifier->setText("Modify");
           ui->le_aff->setText("Display");
           ui->pb_supprimer->setText("Remove");
           ui->pdf_aff->setText("Display PDF");
           ui->groupBox->setTitle("Add a Provider");
           ui->groupBox_2->setTitle("Display");

           ui->recherche->setPlaceholderText("Search");
           ui->traduire->setText("Translate");
    }
    else
    {
        ui->label_2->setText("Nom");
        ui->label_3->setText("Nombre");
        ui->label_4->setText("Adresse");
        ui->label_5->setText("Paiment");
        ui->label_7->setText("Trier par");
        ui->label_8->setText("Traduire en anglais");
        ui->pb_ajouter->setText("Ajouter");
        ui->pb_modifier->setText("Modifier");
        ui->le_aff->setText("Afficher");
        ui->pb_supprimer->setText("Supprimer");
        ui->pdf_aff->setText("Afficher un PDF");
        ui->groupBox->setTitle("Ajouter un Fournisseur");
        ui->groupBox_2->setTitle("Afficher");

        ui->recherche->setPlaceholderText("Rechercher");
        ui->traduire->setText("Traduire");
    }


}

void MainWindow::on_le_aff_2_clicked()
{
    QTableView table_necessiteux,table_n2;
             QSqlQueryModel * Mod=new  QSqlQueryModel();
             QSqlQueryModel * Mod2=new  QSqlQueryModel();
                  Connection c;
                  QSqlQuery qry,q2;
                  qry.prepare("select NOM_F from fournisseurs");
                  qry.exec();
                  Mod->setQuery(qry);
                  table_necessiteux.setModel(Mod);

                  q2.prepare("select AVG(paiment_achat_f) from fournisseurs group by nom_f");
                  q2.exec();
                  Mod2->setQuery(q2);
                  table_n2.setModel(Mod2);

                  c.closeConnection();

                 qDebug()<<table_necessiteux.model()->data(table_necessiteux.model()->index(0, 0)).toString().simplified();
                 qDebug()<<table_n2.model()->data(table_n2.model()->index(0, 0)).toInt();

                 const int rowCount = table_necessiteux.model()->rowCount();
                 const int rowCount2 = table_n2.model()->rowCount();



                // set dark background gradient:
                 QLinearGradient gradient(0, 0, 0, 400);
                 gradient.setColorAt(0, QColor(192, 192, 192));
                 gradient.setColorAt(0.38, QColor(105, 105, 105));
                 gradient.setColorAt(1, QColor(70, 70, 70));
                 ui->customPlot->setBackground(QBrush(gradient));

                 // create empty bar chart objects:
                 QCPBars *besoin = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);

                 besoin->setAntialiased(false); // gives more crisp, pixel aligned bar borders

                 besoin->setStackingGap(1);

                 // set names and colors:

                 besoin->setName("Paiment");
                 besoin->setPen(QPen(QColor(0, 168, 140).lighter(130)));
             besoin->setBrush(QColor(18, 116, 161));
                 // stack bars on top of each other:


                 // prepare x axis with needs' labels:
                 QVector<double> ticks;
                 QVector<QString> labels;

                 for(int i=0; i<rowCount; ++i){
                     ticks.push_back(i);
                     labels.push_back(table_necessiteux.model()->data(table_necessiteux.model()->index(i, 0)).toString().simplified());
                     qDebug()<<ticks[i];
                     qDebug()<<labels[i];
                 }
                 QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                 textTicker->addTicks(ticks, labels);
                 ui->customPlot->xAxis->setTicker(textTicker);
                 ui->customPlot->xAxis->setTickLabelRotation(60);
                 ui->customPlot->xAxis->setSubTicks(false);
                 ui->customPlot->xAxis->setTickLength(0, 4);
                 ui->customPlot->xAxis->setRange(0, 8);
                 ui->customPlot->xAxis->setBasePen(QPen(Qt::black));
                 ui->customPlot->xAxis->setTickPen(QPen(Qt::black));
                 ui->customPlot->xAxis->grid()->setVisible(true);
                 ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                 ui->customPlot->xAxis->setTickLabelColor(Qt::black);
                 ui->customPlot->xAxis->setLabelColor(Qt::black);

                 // prepare y axis:
                 ui->customPlot->yAxis->setRange(0,50);
             ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
             ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
             ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
             ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
             ui->customPlot->yAxis->grid()->setSubGridVisible(true);
             ui->customPlot->yAxis->setTickLabelColor(Qt::white);
             ui->customPlot->yAxis->setLabelColor(Qt::white);
             ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
             ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                 // Add data:
                 QVector<double>besoinData;

                 for(int i=0; i<rowCount2; ++i){
                     besoinData.push_back(table_n2.model()->data(table_n2.model()->index(i, 0)).toInt());
                     qDebug()<<besoinData;

                 }

                 besoin->setData(ticks, besoinData);

                 // setup legend:
                 ui->customPlot->legend->setVisible(true);
             ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
             ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
             ui->customPlot->legend->setBorderPen(Qt::NoPen);
             QFont legendFont = font();
             legendFont.setPointSize(10);
             ui->customPlot->legend->setFont(legendFont);
             ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

             ui->customPlot->replot();
}
