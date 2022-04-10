//Metier Authentification

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString log = ui->lineEdit->text();
        QString mdps = ui->lineEdit_2->text();
        QSqlQuery qry;
        if(qry.exec("select * from COMPTE where log='"+log+"' and mdps='"+mdps+"'")) {
          int count=0;
          while (qry.next())
          {
              count++;
          }
          if(count==1){
              ui->label_3->setText("Username and password is correct");
              this->hide();
              MainWindow2 *newmain= new MainWindow2();
              newmain->show();
          }
          if(count>1)
              ui->label_3->setText("Duplicate Username and password is correct");
          if(count<1)
              ui->label_3->setText("Username and password is not correct");
        }
        else {
            QMessageBox::warning(this,"Login", "Username and password is not correct");
        }
}
