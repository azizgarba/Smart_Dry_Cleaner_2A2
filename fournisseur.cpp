#include "fournisseur.h"
#include <QSqlQuery>
#include <QtDebug>
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

      return test;
  }
