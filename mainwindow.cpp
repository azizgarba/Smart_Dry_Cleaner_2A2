#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow2.h"

#include "QTranslator"
#include "QInputDialog"
#include "QApplication"
#include"arduino.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //arduino
    serial = new QSerialPort();
    arduino_available = false;

    foreach (const QSerialPortInfo &serial_Info, QSerialPortInfo::availablePorts()) {
        qDebug()<<"Port: "<<serial_Info.portName();
        portname = serial_Info.portName();

        arduino_available = true;
    }
    if(arduino_available){
        arduino_init();
    }
    //Arduino zied
              int ret=A.connect_arduino(); // lancer la connexion à arduino
                 switch(ret){
                 case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                     break;
                 case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                    break;
                 case(-1):qDebug() << "arduino is not available";
                 }
                  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_nb())); // permet de lancer
                  //le slot update_label suite à la reception du signal readyRead (reception des données).
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::arduino_init()
{
    serial->setPortName(portname);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
}


void MainWindow::on_pushButton_clicked()
{


    QString log = ui->lineEdit->text();
        QString mdps = ui->lineEdit_2->text();
        QSqlQuery qry;
        if((qry.exec("select * from COMPTE where log='"+log+"' and mdps='"+mdps+"'"))/*||((serial->isWritable()))*/) {
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



void MainWindow::on_pushButton_2_clicked()
{
    if(serial->isWritable()){
         serial->write("1");
         qDebug()<<"Accepter";
         this->hide();
         MainWindow2 *newmain= new MainWindow2();
         newmain->show();
     }
}

