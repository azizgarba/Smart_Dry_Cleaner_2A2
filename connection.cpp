#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hydro");
db.setUserName("myriam");//inserer nom de l'utilisateur
db.setPassword("myriam2001");//inserer mot de passe de cet utilisateur

if (db.open())

test=true;

//men 3andi hedhi
/*QSqlQuery q( db );
q.exec( "SELECT field_name FROM table_name" );*/


    return  test;
}
void Connection::closeConnection(){db.close();}
