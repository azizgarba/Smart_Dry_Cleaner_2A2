#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class Employee
{
    int id_e;
    QString nom_e, prenom_e, numero_e, adresse_e;
public:
    //Constructeurs
    Employee();
    Employee(int, QString, QString, QString, QString);

    //Getters
    int get_id();
    QString get_nom();
    QString get_prenom();
    QString get_numero();
    QString get_adresse();

    //Setters
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setnumero(QString);
    void setadresse(QString);


    //CRUD
    bool ajouter();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * afficher();

};

#endif // EMPLOYEE_H
