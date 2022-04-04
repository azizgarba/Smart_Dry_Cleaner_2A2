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
#include<QDirModel>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include<QDirModel>
#include <QtPrintSupport/QPrintDialog>
#include "dialog.h"

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
    class Dialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow2::on_pushButton_chat_clicked()
{
    openDialog();
}
