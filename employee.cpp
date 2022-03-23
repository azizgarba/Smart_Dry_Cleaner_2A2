#include "employee.h"

Employee::Employee()
{
    id_e=0;
    nom_e="";
    prenom_e="";
    numero_e="";
    adresse_e="";
}

Employee::Employee(int id_e, QString nom_e, QString prenom_e, QString numero_e, QString adresse_e)
{
    this->id_e=id_e;
    this->nom_e=nom_e;
    this->prenom_e=prenom_e;
    this->numero_e=numero_e;
    this->adresse_e=adresse_e;
}

int Employee::get_id()
{
    return id_e;
}
QString Employee::get_nom()
{
    return nom_e;
}
QString Employee::get_prenom()
{
    return prenom_e;
}
QString Employee::get_numero()
{
    return numero_e;
}
QString Employee::get_adresse()
{
    return adresse_e;
}

void Employee::setid(int id_e)
{
    this->id_e=id_e;
}
void Employee::setnom(QString nom_e)
{
    this->nom_e=nom_e;
}
void Employee::setprenom(QString prenom_e)
{
    this->prenom_e=prenom_e;
}
void Employee::setnumero(QString numero_e)
{
    this->numero_e=numero_e;
}
void Employee::setadresse(QString adresse_e)
{
    this->adresse_e=adresse_e;
}

bool Employee::ajouter()
{
        bool test=false;
        QSqlQuery query;
        QString id_string= QString::number(id_e);
          query.prepare("INSERT INTO EMPLOYEE (ID_E, NOM_E, PRENOM_E, NUMERO_E, ADRESSE_E) "
                        "VALUES (:ID_E, :NOM_E, :PRENOM_E,:NUMERO_E,:ADRESSE_E)");
          query.bindValue(":ID_E",id_string);
          query.bindValue(":NOM_E",nom_e);
          query.bindValue(":PRENOM_E", prenom_e);
          query.bindValue(":NUMERO_E", numero_e);
          query.bindValue(":ADRESSE_E", adresse_e);
          query.exec();
          test =true;
        return test ;
}

QSqlQueryModel * Employee::afficher()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

       model->setQuery("SELECT* FROM EMPLOYEE");
       model->setQuery("select * from EMPLOYEE ORDER BY ID_E ASC ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));

      return model;
}

bool Employee::supprimer(int id_e)
{
  /*  QSqlQuery query;
    QString res=QString::number(id_e);

    query.prepare("Delete from Employee where id_e= : ID_E");
    query.bindValue(":ID_E",res);
    return query.exec();*/

    QSqlQuery qry;
       qry.prepare("Delete from EMPLOYEE where ID_E = :ID_E");
       qry.bindValue(":ID_E",id_e);
       return qry.exec();
}

bool Employee::modifier(){
    bool test=false;
    QSqlQuery query;
    QString id_string= QString::number(id_e);
      query.prepare("UPDATE EMPLOYEE SET ID_E=:ID_E, NOM_E=:NOM_E, PRENOM_E=:PRENOM_E, NUMERO_E=:NUMERO_E, ADRESSE_E=:ADRESSE_E "
                    "WHERE ID_E=:ID_E");
      query.bindValue(":ID_E",id_string);
      query.bindValue(":NOM_E",nom_e);
      query.bindValue(":PRENOM_E", prenom_e);
      query.bindValue(":NUMERO_E", numero_e);
      query.bindValue(":ADRESSE_E", adresse_e);
      query.exec();
      test =true;
    return test ;
}

QSqlQueryModel *Employee::trier_nom(){
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from EMPLOYEE order by NOM_E ASC");
    model->setQuery("select * from EMPLOYEE ORDER BY NOM_E ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    qry->exec();
    model->setQuery(*qry);
    return model;
}
QSqlQueryModel *Employee::trier_prenom(){
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from EMPLOYEE order by PRENOM_E ASC");
    model->setQuery("select * from EMPLOYEE ORDER BY PRENOM_E ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    qry->exec();
    model->setQuery(*qry);
    return model;
}
QSqlQueryModel *Employee::trier_adresse(){
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from EMPLOYEE order by ADRESSE_E ASC");
    model->setQuery("select * from EMPLOYEE ORDER BY ADRESSE_E ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    qry->exec();
    model->setQuery(*qry);
    return model;
}
