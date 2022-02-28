#ifndef PRODUIT_H
#define PRODUIT_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <vector>




class produit
{
 int produit_id ;
 QString type ;
 QString matiere;
 QString etat_p ;
 int prix ;


public:
      produit();
      produit(int produit_id, QString type ,QString matiere,QString etat_p,int prix)
      {
          this->produit_id=produit_id ;
          this->type=type;
          this->matiere=matiere ;
          this->etat_p=etat_p ;
          this->prix=prix ;
      }



             //getters
             int getproduit_id(){return produit_id;};
             QString gettype(){return type;};
             QString getmatiere() { return matiere; };
             QString getetat_p() { return etat_p; };
             int getprix() { return prix; };


             //setters
             void setproduit_id(int id){produit_id=id;}
             void settype(QString t){type=t;}
             void setmatiere(QString m) { matiere=m; }
             void setetat_p(QString e) { etat_p = e; }
             void setprix(int p) { prix = p; }


             //fonctions
             bool ajouter();
             bool modifier();
             QSqlQueryModel *afficher();
             bool supprimer();
            // void genererPDFact() ;
             QSqlQueryModel * rechercher(QString);
             QSqlQueryModel * trier_produit_id();
             QSqlQueryModel * trier_etat_p();
             QSqlQueryModel * trier_prix();


};

#endif // PRODUIT_H
