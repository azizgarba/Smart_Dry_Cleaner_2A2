#ifndef MATERIEL_H
#define MATERIEL_H
#include "excel.h"

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMessageBox>

class materiel
{
    QString ref_m, etat_m, date_acham, model_m, image_m,
    date_histo, descri_histo,tempera_m;
    int nbr_prodm;


    public:

    //consctructeurs
    materiel(){}
   materiel(QString, QString,QString ,QString, QString, QString);

    //getters
    QString getRef_m(){return ref_m;}
    QString getEtat_m(){return etat_m;}
    QString getDate_acham(){return date_acham;}
    QString getModel_m(){return model_m;}
    //int getNbr_prodm(){return nbr_prodm;}
    QString getTempera_m(){return tempera_m;}
    QString getImage_m(){return image_m;}

    //setters

    void setRef_m(QString r){ref_m=r;}
    void setEtat_m(QString e){etat_m=e;}
    void setDate_acham(QString da){date_acham=da;}
    void setModel_m_m(QString m){model_m=m;}
    void setImage_m(QString i){image_m=i;}
    //void setNbr_prodm(int nbr_prodm){this->nbr_prodm=nbr_prodm;}
    void setTempera_m(QString tempera_m){this->tempera_m=tempera_m;}

//fonctions
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(materiel m);
    bool modifier();
    QSqlQueryModel * triedate();
    QSqlQueryModel * trieetat();
    QSqlQueryModel * trienbrproduit();
    QSqlQueryModel * chercher(QString reche);
    QSqlQueryModel * afficherMachineForExcel();
    bool ajoutImage();
    QSqlQueryModel * afficher_historique();
    void ajouter_valid(QString ref);
    void ajouter_suppri(QString ref);
    void ajouter_modif(QString ref);




};

#endif // MATERIEL_H
