#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "QTranslator"
#include "QInputDialog"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator T;
    Connection c;
   bool test=c.createconnect();

   if(test)
       {
           QMessageBox::critical(nullptr, QObject::tr("database is open"),
                       QObject::tr("connection successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }

   else
   {
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("connection failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

  }



        QStringList languages;
          languages <<"Anglais"<<"Francais";
          const QString lang = QInputDialog::getItem(NULL,"language ","Select language",languages);

        if (lang == "Anglais")
        {
            T.load(":/new/prefix1/anglais.qm");

        }

        if (lang !="Francais")
        {
            a.installTranslator(&T);
        }

       MainWindow w;

        w.show();
        return a.exec();

    }




















