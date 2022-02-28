#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QRegularExpressionValidator>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
#include<QDateTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//place holders
ui->lineEdit_nom->setPlaceholderText("john");
ui->lineEdit_prenom->setPlaceholderText("adams");
ui->lineEdit_adresse->setPlaceholderText("ariana");
ui->lineEdit_email->setPlaceholderText("example@hotmail.com");
ui->lineEdit_num_tel->setPlaceholderText("12345678");
ui->lineEdit_cin->setPlaceholderText("87654321");
ui->lineEdit_age->setPlaceholderText("18");
ui->lineEdit_search->setPlaceholderText("recherche");
//line edits restrections
    QRegularExpression QRegExp( "[a-zA-Z]+");
    QRegularExpression QRegExp2("[a-zA-Z0-9]+@[a-zA-Z]+.[a-zA-Z]+");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegExp,this);
    QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(QRegExp2,this);
    ui->lineEdit_nom->setValidator(validator);
    ui->lineEdit_prenom->setValidator(validator);
    ui->lineEdit_adresse->setValidator(validator);
    ui->lineEdit_email->setValidator(validator2);
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_num_tel->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_age->setValidator(new QIntValidator(0,100,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_pressed()
{
ui->pushButton->setStyleSheet("QPushButton{ background-color: rgb(0, 89, 193) }");
}

void MainWindow::on_pushButton_released()
{
ui->pushButton->setStyleSheet("QPushButton{ background-color: rgb(0, 129, 233) }");
}


void MainWindow::on_pushButton_2_pressed()
{
ui->pushButton_2->setStyleSheet("QPushButton{ background-color: rgb(0, 89, 193) }");
}


void MainWindow::on_pushButton_2_released()
{
ui->pushButton_2->setStyleSheet("QPushButton{ background-color: rgb(0, 129, 233) }");
}


void MainWindow::on_pushButton_3_pressed()
{
ui->pushButton_3->setStyleSheet("QPushButton{ background-color: rgb(0, 89, 193) }");
}


void MainWindow::on_pushButton_3_released()
{
ui->pushButton_3->setStyleSheet("QPushButton{ background-color: rgb(0, 129, 233) }");
}


void MainWindow::on_pushButton_4_pressed()
{
ui->pushButton_4->setStyleSheet("QPushButton{ background-color: rgb(0, 89, 193) }");
}


void MainWindow::on_pushButton_4_released()
{
ui->pushButton_4->setStyleSheet("QPushButton{ background-color: rgb(0, 129, 233) }");
}


void MainWindow::on_pushButton_5_pressed()
{
ui->pushButton_5->setStyleSheet("QPushButton{ background-color: rgb(0, 89, 193) }");
}


void MainWindow::on_pushButton_5_released()
{
ui->pushButton_5->setStyleSheet("QPushButton{ background-color: rgb(0, 129, 233) }");
}




//ajouter client buttton clicked
void MainWindow::on_pushButton_clicked()
{
Client c;
c.set_cin(ui->lineEdit_cin->text());
c.set_nom(ui->lineEdit_nom->text());
c.set_prenom(ui->lineEdit_prenom->text());
c.set_adresse(ui->lineEdit_adresse->text());
c.set_num_tel(ui->lineEdit_num_tel->text());
c.set_email(ui->lineEdit_email->text());
c.set_age(ui->lineEdit_age->text());
c.ajouter_client(c);
ui->lineEdit_cin->setText("");
ui->lineEdit_nom->setText("");
ui->lineEdit_prenom->setText("");
ui->lineEdit_adresse->setText("");
ui->lineEdit_num_tel->setText("");
ui->lineEdit_email->setText("");
ui->lineEdit_age->setText("");
ui->tableView->setModel(c.afficher_client());
}

//modifier client button clicked
void MainWindow::on_pushButton_2_clicked()
{
 Client c;
 c.set_cin(ui->lineEdit_cin->text());
 c.set_nom(ui->lineEdit_nom->text());
 c.set_prenom(ui->lineEdit_prenom->text());
 c.set_adresse(ui->lineEdit_adresse->text());
 c.set_num_tel(ui->lineEdit_num_tel->text());
 c.set_email(ui->lineEdit_email->text());
 c.set_age(ui->lineEdit_age->text());
 c.modifier_client(c);
 ui->lineEdit_cin->setText("");
 ui->lineEdit_nom->setText("");
 ui->lineEdit_prenom->setText("");
 ui->lineEdit_adresse->setText("");
 ui->lineEdit_num_tel->setText("");
 ui->lineEdit_email->setText("");
 ui->lineEdit_age->setText("");
 ui->tableView->setModel(c.afficher_client());
}

//supprimer client button clicked
void MainWindow::on_pushButton_3_clicked()
{
 Client c;
 c.set_cin(ui->lineEdit_cin->text());
 c.supprimer_client(c);
 ui->lineEdit_cin->setText("");
 ui->lineEdit_nom->setText("");
 ui->lineEdit_prenom->setText("");
 ui->lineEdit_adresse->setText("");
 ui->lineEdit_num_tel->setText("");
 ui->lineEdit_email->setText("");
 ui->lineEdit_age->setText("");
 ui->tableView->setModel(c.afficher_client());
}

//afficher clients in tableview and in the lineEdits
void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C FROM CLIENTS WHERE CIN='"+val+"' or NOM_C='"+val+"' or PRENOM_C='"+val+"' or AGE='"+val+"' or ADRESSE_C='"+val+"' or NUMERO_TEL='"+val+"' or EMAIL_C='"+val+"'";
    QSqlQuery qry;
    qry.prepare(sQuery);

    if(qry.exec()){
        while(qry.next())
        {
            ui->lineEdit_cin->setText(qry.value(0).toString());
            ui->lineEdit_nom->setText(qry.value(1).toString());
            ui->lineEdit_prenom->setText(qry.value(2).toString());
            ui->lineEdit_age->setText(qry.value(3).toString());
            ui->lineEdit_adresse->setText(qry.value(4).toString());
            ui->lineEdit_num_tel->setText(qry.value(5).toString());
            ui->lineEdit_email->setText(qry.value(6).toString());

        }
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not shown.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

//send mail to client
void MainWindow::on_pushButton_5_clicked()
{

}

//afficher client button clicked
void MainWindow::on_pushButton_6_clicked()
{
 Client c;
 //afficher simple
 ui->tableView->setModel(c.afficher_client());
 //afficher selon le nom
 if(QString::number(ui->comboBox->currentIndex())=="0"){
  ui->tableView->setModel(c.afficher_client_trie_nom());
 }
 //afficher selon le prenom
 else if(QString::number(ui->comboBox->currentIndex())=="1"){
     ui->tableView->setModel(c.afficher_client_trie_prenom());
 }
 //afficher selon l'age
 else if(QString::number(ui->comboBox->currentIndex())=="2"){
     ui->tableView->setModel(c.afficher_client_trie_age());
 }
 //QMessageBox::information(this,"title",QString::number(ui->comboBox->currentIndex()));
}

//generate pdf of coupon button clicked
void MainWindow::on_pushButton_4_clicked()
{
QDateTime date = QDateTime::currentDateTime();
QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
QPdfWriter pdf("D:/Esprit/c++/QT exercices/Hydro_Plus_Pdf/pdf_test1.pdf");

QPainter painter(&pdf);

painter.setPen(Qt::blue);
painter.drawText(4500,0,"Hydro+ pressing");

painter.setPen(Qt::blue);
painter.drawText(100,400,"hello,we are pleased to tell you that due to your purchases you have a 10% coupon to use in your next purchase");
painter.setPen(Qt::red);
painter.drawText(100,600,"CODE:10HYriKf");
painter.setPen(Qt::blue);
painter.drawText(100,800,formattedTime);
painter.drawPixmap(QRect(3000,2000,4000,3000),QPixmap("C:/Users/MAG-PC/OneDrive/Pictures/coupon10%OFF.png"));

painter.end();
}


void MainWindow::on_lineEdit_search_textEdited(const QString &arg1)
{

}


void MainWindow::on_lineEdit_search_textChanged(const QString &arg1)
{
    Client c;
    ui->tableView->setModel(c.afficher_client_recherche(arg1));
}

