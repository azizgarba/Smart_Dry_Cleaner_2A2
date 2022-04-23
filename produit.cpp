#include "produit.h"
#include "mainwindow.h"
#include<QSqlQuery>
#include<QtDebug>
#include<qobject.h>
#include <QComboBox>
#include <QApplication>
#include <QtCore>
#include <QSystemTrayIcon>
#include <QSystemTrayIcon>
#include<QMessageBox>
produit::produit()
{

}

bool produit::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO produits (produit_id,type, matiere, etat_p, prix ) VALUES ( :produit_id,:type, :matiere, :etat_p,:prix )");
    query.bindValue(":produit_id", produit_id);
    query.bindValue(":type", type);
    query.bindValue(":matiere", matiere);
    query.bindValue(":etat_p", etat_p);
    query.bindValue(":prix", prix);
    return query.exec();
}
bool produit::modifier()
{

      QSqlQuery query;
       query.prepare("UPDATE produits SET produit_id= :produit_id, type= :type,matiere= :matiere, etat_p= :etat_p,prix= :prix where produit_id= :produit_id ");
       query.bindValue(":produit_id", produit_id);
       query.bindValue(":type", type);
       query.bindValue(":matiere", matiere);
       query.bindValue(":etat_p", etat_p);
       query.bindValue(":prix", prix);
       return query.exec();

}

QSqlQueryModel *produit::afficher()
{
    produit p ;
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM produits order by produit_id ASC");


    return model;


}
/*
bool  produit::supprimer()
{  QSqlQuery query;
    QString id_string=QString:: number(produit_id);
    query.prepare("Delete from produits where produit_id=:produit_id");
    query.bindValue(":produit_id", produit_id);
    return query.exec();
}*/
bool produit::supprimer(int produit_id)
{

    QSqlQuery qry;
       qry.prepare("Delete from produits where produit_id = :produit_id");
       qry.bindValue(":produit_id",produit_id);
       return qry.exec();
}

QSqlQueryModel *produit::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from produits where produit_id LIKE ('%"+rech+"%') or type LIKE ('%"+rech+"%') ");



    return model;

}
QSqlQueryModel *produit::recherche()
{
    QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select etat_p from produits where etat_p LIKE 'finie' ");

    return model;
}

QSqlQueryModel *produit::trier_produit_id(){
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from produits order by produit_id ASC");
    qry->exec();
    model->setQuery(*qry);
    return model;
}


QSqlQueryModel *produit::trier_etat_p(){
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from produits order by etat_p ASC");
    qry->exec();
    model->setQuery(*qry);
    return model;
}
QSqlQueryModel *produit::trier_prix(){
    QSqlQuery *qry=new QSqlQuery();
    QSqlQueryModel *model=new QSqlQueryModel();
    qry->prepare("select * from produits order by prix ASC");
    qry->exec();
    model->setQuery(*qry);
    return model;
}




