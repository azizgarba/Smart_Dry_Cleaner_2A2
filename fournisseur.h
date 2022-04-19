#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseur
{
    int cin, paiment;
    QString nom, numero, adresse, date;

public:
    Fournisseur();
    Fournisseur(int,QString,QString,QString,int,QString);

    //Getters
      int getcin();
      QString getnom();
      QString getnumero();
      QString getadresse();
      int getpaiment();
      QString getdate();

      //Setters
      void setcin(int);
      void setnom(QString);
      void setnumero(QString);
      void setadresse(QString);
      void setpaiment(int);
      void setdate(QString);

      //CRUD
      bool ajouter();
      bool supprimer(int);
      bool modifier();
      QSqlQueryModel * afficher();
      QSqlQueryModel * afficher_fournis_par_nom();
      QSqlQueryModel * afficher_fournis_par_achat();
      QSqlQueryModel * afficher_fournis_par_date();
      QSqlQueryModel * chercher(QString rech);




};

#endif // FOURNISSEUR_H
