#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setStyle("fusion");
    Dialog w;
    w.show();
    return a.exec();
    Connection c;
    bool test=c.createconnect();
    MainWindow ww;
    if(test)
    {w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
