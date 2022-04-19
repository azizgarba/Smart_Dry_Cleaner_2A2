#include "fournisseur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Fournisseur::Fournisseur()
{
    cin=0; nom=""; numero=""; adresse=""; paiment=0; date="";

}

Fournisseur::Fournisseur(int cin,QString nom,QString numero,QString adresse,int paiment,QString date)
{
      this->cin=cin;
      this->nom=nom;
      this->numero=numero;
      this->adresse=adresse;
      this->paiment=paiment;
      this->date=date;

}

//Getters
  int Fournisseur::getcin(){return  cin;}
  QString Fournisseur::getnom(){return  nom;}
  QString Fournisseur::getnumero(){return  numero;}
  QString Fournisseur::getadresse(){return  adresse;}
  int Fournisseur::getpaiment(){return  paiment;}
  QString Fournisseur::getdate(){return  date;}
  //Setters
  void Fournisseur::setcin(int cin){this->cin=cin;}
  void Fournisseur::setnom(QString nom){this->nom=nom;}
  void Fournisseur::setnumero(QString numero){this->numero=numero;}
  void Fournisseur::setadresse(QString adresse){this->adresse=adresse;}
  void Fournisseur::setpaiment(int paiment){ this->paiment=paiment;}
  void Fournisseur::setdate(QString date){this->date=date;}




  bool Fournisseur::ajouter()
  {
      bool test=false;

      QSqlQuery query;
      QString id_string= QString::number(cin);
      QString paiment_string= QString::number(paiment);
            query.prepare("INSERT INTO fournisseurs (fournis_id, nom_f, numero_tel, adresse_f, paiment_achat_f, date_contrat) "
                          "VALUES (:cin, :forename, :numero, :adresse, :paiment, :date)");
            query.bindValue(":cin", id_string);
            query.bindValue(":forename", nom);
            query.bindValue(":numero", numero);
            query.bindValue(":adresse", adresse);
            query.bindValue(":paiment", paiment_string);
            query.bindValue(":date", date);
            query.exec();
            test =true;

      return test;
  }



  QSqlQueryModel* Fournisseur::afficher()
   {
       QSqlQueryModel* model=new QSqlQueryModel();

            model->setQuery("SELECT* FROM FOURNISSEURS");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Paiment"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nom"));

            return model;

   }


bool Fournisseur::supprimer(int cin)
{

         QSqlQuery query;
               query.prepare("Delete from Fournisseurs where fournis_id=:cin");
               query.bindValue(":cin", cin);
               return query.exec();
 }




bool Fournisseur::modifier(){

    bool test=false;

    QSqlQuery query;
    QString id_string= QString::number(cin);
    QString paiment_string= QString::number(paiment);
     query.prepare("UPDATE fournisseurs SET fournis_id=:cin, nom_f=:forename, numero_tel=:numero, adresse_f=:adresse, paiment_achat_f=:paiment, date_contrat=:date "
                              "WHERE fournis_id=:cin");

          query.bindValue(":cin", id_string);
          query.bindValue(":forename", nom);
          query.bindValue(":numero", numero);
          query.bindValue(":adresse", adresse);
          query.bindValue(":paiment", paiment_string);
          query.bindValue(":date", date);
          query.exec();
          test =true;

    return test;
}






//afficher les fournisseurs selon le nom
QSqlQueryModel* Fournisseur::afficher_fournis_par_nom()
{
    QSqlQueryModel* model1=new QSqlQueryModel();

         model1->setQuery("SELECT* FROM FOURNISSEURS ORDER BY NOM_F");
         model1->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
         model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Paiment"));
         model1->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
         model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
         model1->setHeaderData(5, Qt::Horizontal, QObject::tr("Nom"));

         return model1;

}

QSqlQueryModel* Fournisseur::afficher_fournis_par_achat()
{
    QSqlQueryModel* model2=new QSqlQueryModel();

         model2->setQuery("SELECT* FROM FOURNISSEURS ORDER BY PAIMENT_ACHAT_F");
         model2->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model2->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
         model2->setHeaderData(2, Qt::Horizontal, QObject::tr("Paiment"));
         model2->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
         model2->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
         model2->setHeaderData(5, Qt::Horizontal, QObject::tr("Nom"));

         return model2;
}
QSqlQueryModel* Fournisseur::afficher_fournis_par_date()
{
    QSqlQueryModel* model3=new QSqlQueryModel();

         model3->setQuery("SELECT* FROM FOURNISSEURS ORDER BY DATE_CONTRAT");
         model3->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model3->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
         model3->setHeaderData(2, Qt::Horizontal, QObject::tr("Paiment"));
         model3->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
         model3->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
         model3->setHeaderData(5, Qt::Horizontal, QObject::tr("Nom"));

         return model3;

}

 QSqlQueryModel * Fournisseur::chercher(QString rech)
 {
     QString sQuery="SELECT* FROM FOURNISSEURS WHERE FOURNIS_ID LIKE '%"+rech+"%' or NOM_F LIKE '%"+rech+"%'";

     QSqlQueryModel *model4=new QSqlQueryModel();
     QSqlQuery qry;
     qry.prepare(sQuery);
     qry.exec();
     model4->setQuery(qry);
     return model4;



 }
