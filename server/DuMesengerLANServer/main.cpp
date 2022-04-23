#include <QCoreApplication>
#include "DuMessengerServer.h"

using namespace ramymgaidi;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
DuMessengerServer Server;
if(!Server.startServer(3333)){
qDebug()<<"error:" << Server.errorString();
return 1;
}
qDebug() << "Server started ...";
    return a.exec();
}
