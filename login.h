#ifndef LOGIN_H
#define LOGIN_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class login
{
    QString log, mdps;
public:
    login();
    login(QString, QString);

    //Fonctions
    bool ajouter();
};


#endif // LOGIN_H
