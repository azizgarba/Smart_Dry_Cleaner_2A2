#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseur
{
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
      bool ajouter();

private:
    int cin, paiment;
    QString nom, numero, adresse, date;

};

#endif // FOURNISSEUR_H
