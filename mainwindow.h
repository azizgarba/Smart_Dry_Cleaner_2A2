#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "mainwindow2.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
   //arduino zied
   void update_nb();


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    MainWindow2 *mainwindow2;
    QSerialPort *serial;
        QString portname;

        bool arduino_available;
        void arduino_init();


        //arduino zied
        QByteArray data; // variable contenant les données reçues
        Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
