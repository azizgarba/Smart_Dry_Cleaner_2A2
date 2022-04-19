#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "employee.h"
#include "exportexcel.h"
#include "qrcode.h"
#include "qrwidget.h"
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
#include <QPixmap>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
//#include<QDirModel>
#include<QDir>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
//#include<QDirModel>
#include <QtPrintSupport/QPrintDialog>
#include "widget.h"
#include"client.h"
#include<QPdfWriter>
#include<QDesktopServices>
#include"smtp.h"
#include"produit.h"
#include"offre.h"
#include<QSystemTrayIcon>
#include"excel.h"
#include "fournisseur.h"
MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());

    QRegularExpression QRegExp("[a-zA-Z]+");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegExp,this);
    ui->lineEdit_ID->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_nom->setValidator(validator);
    ui->lineEdit_prenom->setValidator(validator);
    ui->lineEdit_num->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_adr->setValidator(validator);

       connect(ui->pushButton_chat, SIGNAL(click()), this, SLOT(openDialog()));
//restrictions aziz
       //place holders
       ui->lineEdit_nom_4->setPlaceholderText("john");
       ui->lineEdit_prenom_4->setPlaceholderText("adams");
       ui->lineEdit_adresse_3->setPlaceholderText("ariana");
       ui->lineEdit_email_3->setPlaceholderText("example@hotmail.com");
       ui->lineEdit_num_tel_3->setPlaceholderText("12345678");
       ui->lineEdit_cin_3->setPlaceholderText("87654321");
       ui->lineEdit_age_3->setPlaceholderText("18");
       ui->lineEdit_search_2->setPlaceholderText("recherche");
       //line edits restrections
           QRegularExpression QRegExp0( "[a-zA-Z]+");
           QRegularExpression QRegExp2("[a-zA-Z0-9]+@[a-zA-Z]+.[a-zA-Z]+");
           QRegularExpressionValidator *validator1 = new QRegularExpressionValidator(QRegExp0,this);
           QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(QRegExp2,this);
           ui->lineEdit_nom_4->setValidator(validator1);
           ui->lineEdit_prenom_4->setValidator(validator1);
           ui->lineEdit_adresse_3->setValidator(validator1);
           ui->lineEdit_email_3->setValidator(validator2);
           ui->lineEdit_cin_3->setValidator(new QIntValidator(0,99999999,this));
           ui->lineEdit_num_tel_3->setValidator(new QIntValidator(0,99999999,this));
           ui->lineEdit_age_3->setValidator(new QIntValidator(0,100,this));
//restrictions rania
           ui->recherche_prod->setPlaceholderText("  Chercher(Id-Type)...");
               QRegularExpression QRegExp3( "[a-zA-Z]+");
               QRegularExpressionValidator *validator3 = new QRegularExpressionValidator(QRegExp3,this);
               ui->type_prod->setValidator(validator3);
               ui->matiere_prod->setValidator(validator3);
               ui->etat_prod->setValidator(validator3);
               ui->id_prod->setValidator(new QIntValidator(0,9999,this));
               ui->prix_prod->setValidator(new QIntValidator(0,9999999,this));
               //------------------
               ui->id_offre->setValidator(new QIntValidator(0,9999,this));
               ui->type_offre->setValidator(validator3);
                 ui->reduc_offre->setValidator(new QIntValidator(0,9999999,this));

           ui->treeView->setModel(pr.afficher());
           ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
           ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
                       //offre
                   ui->treeView_2->setModel(of.afficherOffre());
                   ui->treeView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                   ui->treeView_2->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_pushButton_ajouter_clicked()
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

void MainWindow2::on_pushButton_modif_clicked()
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

void MainWindow2::on_pushButton_qr_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
                        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                                 QObject::tr("Veuillez Choisir un employé du Tableau.\n"
                                                             "Click Ok to exit."), QMessageBox::Ok);
                    else
                    {
                         int  Code=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
                         const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(std::to_string(Code).c_str(), qrcodegen::QrCode::Ecc::LOW);
                         std::ofstream myfile;
                         myfile.open ("qrcode.svg") ;
                         myfile << qr.toSvgString(1);
                         myfile.close();
                         QSvgRenderer svgRenderer(QString("qrcode.svg"));
                         QPixmap pix( QSize(90, 90) );
                         QPainter pixPainter( &pix );
                         svgRenderer.render(&pixPainter);
                         ui->label_6->setPixmap(pix);
                    }
}

void MainWindow2::on_pushButton_supp_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
           int id_e =select->selectedRows().value(0).data().toInt();
           if(etmp.supprimer(id_e))
           {
               ui->tableView->setModel(etmp.afficher());
               ui->statusbar->showMessage("SUPPRESSION : SUCCESS");
           }
}

void MainWindow2::on_pushButton_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                           tr("Excel Files (*.xls)"));
           if (fileName.isEmpty())
               return;

           ExportExcel obj(fileName, "mydata", ui->tableView);

           //colums to export
           obj.addField(0, "ID", "char(20)");
           obj.addField(1, "Nom", "char(20)");
           obj.addField(2, "¨Prenom", "char(20)");
           obj.addField(3, "Nnumero", "char(20)");
           obj.addField(4, "Adresse", "char(20)");




           int retVal = obj.export2Excel();
           if( retVal > 0)
           {
               QMessageBox::information(this, tr("Done"),
                                        QString(tr("%1 records exported!")).arg(retVal)
                                        );
           }
}

void MainWindow2::on_pushButton_trier_clicked()
{
    if (ui->radioButton->isChecked())
    {
        ui->tableView->setModel(etmp.trier_nom());
    }
    else if (ui->radioButton_2->isChecked())
    {
        ui->tableView->setModel(etmp.trier_prenom());
    }
    else if(ui->radioButton_3->isChecked())
    {
        ui->tableView->setModel(etmp.trier_adresse());
    }

}

void MainWindow2::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from EMPLOYEE where id_e='"+val+"' or nom_e='"+val+"' or prenom_e='"+val+"' or numero_e='"+val+"' or adresse_e='"+val+"'");

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->lineEdit_ID->setText(qry.value(0).toString());;
            ui->lineEdit_nom->setText(qry.value(1).toString());
            ui->lineEdit_prenom->setText(qry.value(2).toString());
            ui->lineEdit_num->setText(qry.value(3).toString());
            ui->lineEdit_adr->setText(qry.value(4).toString());
        }
    }
}

void MainWindow2::on_pushButton_ajouter_pressed()
{
    ui->pushButton_ajouter->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_ajouter_released()
{
    ui->pushButton_ajouter->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::on_pushButton_modif_pressed()
{
    ui->pushButton_modif->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_modif_released()
{
    ui->pushButton_ajouter->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::on_pushButton_qr_pressed()
{
    ui->pushButton_qr->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_qr_released()
{
    ui->pushButton_qr->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::on_pushButton_supp_pressed()
{
    ui->pushButton_supp->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_supp_released()
{
    ui->pushButton_supp->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::on_pushButton_excel_pressed()
{
    ui->pushButton_excel->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_excel_released()
{
    ui->pushButton_excel->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::on_pushButton_chat_pressed()
{
    ui->pushButton_chat->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_chat_released()
{
    ui->pushButton_chat->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::on_pushButton_trier_pressed()
{
    ui->pushButton_trier->setStyleSheet("QPushButton{background-color: rgb(0, 89, 193)}");
}

void MainWindow2::on_pushButton_trier_released()
{
    ui->pushButton_trier->setStyleSheet("QPushButton{background-color: rgb(169, 223, 247)}");
}

void MainWindow2::openDialog()
{
    DuarteCorporation::Widget *neww = new DuarteCorporation::Widget();
    neww->show();
}

void MainWindow2::on_pushButton_chat_clicked()
{
    openDialog();
}
//************************************** client *************************************
//ajouter client
void MainWindow2::on_pushButton_8_clicked()
{
    QRegularExpression QRegExp2("[a-zA-Z0-9]+@[a-zA-Z]+.[a-zA-Z]+");
    Client c;
    QString mail;
    c.set_email(ui->lineEdit_email_3->text());
    mail=c.get_email();
    if(mail.contains(QRegExp2)){
    c.set_cin(ui->lineEdit_cin_3->text());
    c.set_nom(ui->lineEdit_nom_4->text());
    c.set_prenom(ui->lineEdit_prenom_4->text());
    c.set_adresse(ui->lineEdit_adresse_3->text());
    c.set_num_tel(ui->lineEdit_num_tel_3->text());
    //c.set_email(ui->lineEdit_email->text());
    c.set_age(ui->lineEdit_age_3->text());

    c.ajouter_client(c);
    ui->lineEdit_cin_3->setText("");
    ui->lineEdit_nom_4->setText("");
    ui->lineEdit_prenom_4->setText("");
    ui->lineEdit_adresse_3->setText("");
    ui->lineEdit_num_tel_3->setText("");
    ui->lineEdit_email_3->setText("");
    ui->lineEdit_age_3->setText("");
    ui->tableView_3->setModel(c.afficher_client());}
    else{
        QMessageBox::critical(nullptr, QObject::tr("email error"),
                           QObject::tr("pls enter a valid email.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

//afficher client+ triee
void MainWindow2::on_pushButton_13_clicked()
{
Client c;
//affichage simple
ui->tableView_3->setModel(c.afficher_client());
//afficher selon le nom
if(QString::number(ui->comboBox_2->currentIndex())=="0"){
 ui->tableView_3->setModel(c.afficher_client_trie_nom());
}
//afficher selon le prenom
else if(QString::number(ui->comboBox_2->currentIndex())=="1"){
    ui->tableView_3->setModel(c.afficher_client_trie_prenom());
}
//afficher selon l'age
else if(QString::number(ui->comboBox_2->currentIndex())=="2"){
    ui->tableView_3->setModel(c.afficher_client_trie_age());
}
}

//afficher clinet in line edits
void MainWindow2::on_tableView_3_activated(const QModelIndex &index)
{
    QString val=ui->tableView_3->model()->data(index).toString();
    QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C FROM CLIENTS WHERE CIN='"+val+"' or NOM_C='"+val+"' or PRENOM_C='"+val+"' or AGE='"+val+"' or ADRESSE_C='"+val+"' or NUMERO_TEL='"+val+"' or EMAIL_C='"+val+"'";
    QSqlQuery qry;
    qry.prepare(sQuery);

    if(qry.exec()){
        while(qry.next())
        {
            ui->lineEdit_cin_3->setText(qry.value(0).toString());
            ui->lineEdit_nom_4->setText(qry.value(1).toString());
            ui->lineEdit_prenom_4->setText(qry.value(2).toString());
            ui->lineEdit_age_3->setText(qry.value(3).toString());
            ui->lineEdit_adresse_3->setText(qry.value(4).toString());
            ui->lineEdit_num_tel_3->setText(qry.value(5).toString());
            ui->lineEdit_email_3->setText(qry.value(6).toString());

        }
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not shown.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

//supprimer client
void MainWindow2::on_pushButton_12_clicked()
{
    Client c;
    c.set_cin(ui->lineEdit_cin_3->text());
    c.supprimer_client(c);
    ui->lineEdit_cin_3->setText("");
    ui->lineEdit_nom_4->setText("");
    ui->lineEdit_prenom_4->setText("");
    ui->lineEdit_adresse_3->setText("");
    ui->lineEdit_num_tel_3->setText("");
    ui->lineEdit_email_3->setText("");
    ui->lineEdit_age_3->setText("");
    ui->tableView_3->setModel(c.afficher_client());
}

//modifier client
void MainWindow2::on_pushButton_11_clicked()
{
    QRegularExpression QRegExp2("[a-zA-Z0-9]+@[a-zA-Z]+.[a-zA-Z]+");
    Client c;
    QString mail;
    c.set_email(ui->lineEdit_email_3->text());
    mail=c.get_email();
    if(mail.contains(QRegExp2)){
    c.set_cin(ui->lineEdit_cin_3->text());
    c.set_nom(ui->lineEdit_nom_4->text());
    c.set_prenom(ui->lineEdit_prenom_4->text());
    c.set_adresse(ui->lineEdit_adresse_3->text());
    c.set_num_tel(ui->lineEdit_num_tel_3->text());
    c.set_age(ui->lineEdit_age_3->text());
    c.modifier_client(c);
    ui->lineEdit_cin_3->setText("");
    ui->lineEdit_nom_4->setText("");
    ui->lineEdit_prenom_4->setText("");
    ui->lineEdit_adresse_3->setText("");
    ui->lineEdit_num_tel_3->setText("");
    ui->lineEdit_email_3->setText("");
    ui->lineEdit_age_3->setText("");
    ui->tableView_3->setModel(c.afficher_client());}
    else{
        QMessageBox::critical(nullptr, QObject::tr("email error"),
                           QObject::tr("pls enter a valid email.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

//generer pdf + calculer pts_fidelite
void MainWindow2::on_pushButton_9_clicked()
{
    Client c;
    float prix=0;
 QString nom,prenom,space;
 space=" ";
 nom=ui->lineEdit_nom_4->text();
 prenom=ui->lineEdit_prenom_4->text();
QDateTime date = QDateTime::currentDateTime();
QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
QPdfWriter pdf("C:/Users/rania/OneDrive/Documents/Employee/pdf_test1.pdf");

QPainter painter(&pdf);

painter.setPen(Qt::blue);
painter.drawText(4500,200,"Hydro+ pressing");

painter.setPen(Qt::blue);
painter.drawText(100,800,"hello Mr/s."+nom+""+space+""+prenom+""+space+"we are pleased to tell you that due to your purchases you have a 10% coupon to use in your next purchase");
painter.setPen(Qt::red);
painter.drawText(100,1000,"CODE:10HYriKf");
painter.setPen(Qt::blue);
painter.drawText(100,1200,formattedTime);
painter.drawPixmap(QRect(3000,2000,4000,3000),QPixmap("C:/Users/MAG-PC/OneDrive/Pictures/coupon10%OFF.png"));
painter.drawPixmap(QRect(-300,-300,1500,1000),QPixmap("C:/Users/MAG-PC/OneDrive/Pictures/hydro+2.png"));

painter.end();
c.nbr_fidelite2(prix,nom);
QDesktopServices::openUrl(QUrl("file:///D:/Esprit/c++/QT%20exercices/Hydro_Plus_Pdf/pdf_test1.pdf"));
//c.decre_pts_fidelite(nom);
}

//send mail
void MainWindow2::on_pushButton_10_clicked()
{
    Client c;
        QString mail;
        mail=ui->lineEdit_email_3->text();
        Smtp* smtp = new Smtp("mohamedaziz.guerbouj@esprit.tn" , "201JMT2698", "smtp.gmail.com",465);
         connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        smtp->sendMail("test",mail,"test","hello this is a mail test!!!");
        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                     QObject::tr("Email Sent Successfully.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}
//******************************* produit + offre *************************************
//ajouter produit
void MainWindow2::on_pushButton_2_clicked()
{
    int produit_id=ui->id_prod->text().toInt();
    QString type= ui->type_prod->text();
    QString matiere= ui->matiere_prod->text();
    QString etat_p= ui->etat_prod->text();
    int prix= ui->prix_prod->text().toInt();


   produit p(produit_id, type, matiere, etat_p, prix);
    p.ajouter() ;

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/MAG-PC/OneDrive/Pictures/hydro+2.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion d'un produit","Un produit a été ajoutée",QSystemTrayIcon::Information,15000);



    ui->treeView->setModel(pr.afficher());


}
//modifier produit



void MainWindow2::on_pushButton_6_clicked()
{
    int d =ui->id_prod->text().toInt();
     QString t= ui->type_prod->text();
     QString m= ui->matiere_prod->text();
     QString e= ui->etat_prod->text();
     int prr = ui->prix_prod->text().toInt();


      produit p (d, t, m, e, prr);
      QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
      notifyIcon->setIcon(QIcon("C:/Users/MAG-PC/OneDrive/Pictures/hydro+2.png"));
      notifyIcon->show();
      notifyIcon->showMessage("Gestion d'un produit","Un produit a été modifiée",QSystemTrayIcon::Information,15000);


      p.modifier() ;

      ui->treeView->setModel(pr.afficher());
}
//supprimer produit


void MainWindow2::on_pushButton_7_clicked()
{
    QItemSelectionModel *select = ui->treeView->selectionModel();
      int produit_id =select->selectedRows().value(0).data().toInt();
      if(pr.supprimer(produit_id))
      {
          ui->treeView->setModel(pr.afficher());

      }
      QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
      notifyIcon->setIcon(QIcon("C:/Users/MAG-PC/OneDrive/Pictures/hydro+2.png"));
      notifyIcon->show();
      notifyIcon->showMessage("Gestion d'un produit","Un produit a été supprimée",QSystemTrayIcon::Information,15000);

}

//ajouter offre
void MainWindow2::on_pushButton_clicked()
{
    int offre_id=ui->id_offre->text().toInt();
    QString type_p= ui->type_offre->text();
    QString reduction= ui->reduc_offre->text();



    offre o(offre_id, reduction, type_p);
    o.ajouterOffre() ;
    ui->treeView_2->setModel(of.afficherOffre());
}
//modifier offre

void MainWindow2::on_pushButton_3_clicked()
{
    int offre_id=ui->id_offre->text().toInt();
    QString type_p= ui->type_offre->text();
    QString reduction= ui->reduc_offre->text();



    offre o(offre_id,reduction,type_p);

    o.modifierOffre() ;
    ui->treeView_2->setModel(of.afficherOffre());
}
//supprimer offre

void MainWindow2::on_pushButton_4_clicked()
{
    QItemSelectionModel *select = ui->treeView_2->selectionModel();
                   int offre_id =select->selectedRows().value(0).data().toInt();
                   if(of.supprimerOffre(offre_id))
                   {
                       ui->treeView_2->setModel(of.afficherOffre());

                   }
}

//trier produit
void MainWindow2::on_pushButton_14_clicked()
{
    if(ui->id_radio_butt->isChecked())
        {
            ui->treeView->setModel(pr.trier_produit_id());
        }
        else if(ui->etat_radio_butt->isChecked())
        {
            ui->treeView->setModel(pr.trier_etat_p());
        }
    else if(ui->prix_radio_butt->isChecked())
    {
        ui->treeView->setModel(pr.trier_prix());
    }
}
//rechercher produit

void MainWindow2::on_pushButton_5_clicked()
{
    QString rech =ui->recherche_prod->text();
    ui->treeView->setModel(pr.rechercher(rech));
}

//afficher produit in line edits
void MainWindow2::on_treeView_activated(const QModelIndex &index)
{
    QString val=ui->treeView->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from produit where produit_id='"+val+"' or type='"+val+"' or matiere='"+val+"' or etat_p='"+val+"' or prix='"+val+"'");

       if (qry.exec())
       {
           while (qry.next())
           {
               ui->id_prod->setText(qry.value(0).toString());
               ui->type_prod->setText(qry.value(1).toString());
               ui->matiere_prod->setText(qry.value(2).toString());
               ui->prix_prod->setText(qry.value(3).toString());
               ui->etat_prod->setText(qry.value(4).toString());
           }
       }
}

//afficher offre in line edits
void MainWindow2::on_treeView_2_activated(const QModelIndex &index)
{
    QString val=ui->treeView_2->model()->data(index).toString();
       QSqlQuery qry;
       qry.prepare("select * from offre where offre_id='"+val+"' or type_p='"+val+"' or reduction='"+val+"'");

       if (qry.exec())
       {
           while (qry.next())
           {
               ui->id_offre->setText(qry.value(0).toString());
               ui->type_offre->setText(qry.value(1).toString());
               ui->reduc_offre->setText(qry.value(2).toString());

           }
       }
}

//afficher excel
void MainWindow2::on_pushButton_15_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                              tr("Excel Files (*.xls)"));
              if (fileName.isEmpty())
                  return;

              Export obj(fileName, "Produit", ui->treeView);

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


void MainWindow2::on_lineEdit_search_2_textChanged(const QString &arg1)
{
    Client c;
    ui->tableView_3->setModel(c.afficher_client_recherche(arg1));
}


void MainWindow2::on_pb_ajouter_clicked()
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

void MainWindow2::on_le_aff_clicked()
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
