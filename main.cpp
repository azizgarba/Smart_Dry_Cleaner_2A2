#include "mainwindow.h"
#include<QSplashScreen>
#include <QApplication>
#include<QTimer>
#include<QThread>
#include"connection.h"
#include<QMessageBox>
#include"client.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
        QPixmap pixmap("C:/Users/MAG-PC/OneDrive/Pictures/hydro+2.png");
        QSplashScreen splash(pixmap);
        splash.show();
        app.thread()->sleep(5); // wait for just 5 second and then show main window
        app.processEvents();
        MainWindow window;
        splash.finish(&window);
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test=c.createconnect();
    if(test==true){
    w.show();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                           QObject::tr("connection failed.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}

