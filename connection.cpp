#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("emna");
    db.setUserName("emna");//inserer nom de l'utilisateur
    db.setPassword("0000");//inserer mot de passe de cet utilisateur


if (db.open())
test=true;





    return  test;
}
