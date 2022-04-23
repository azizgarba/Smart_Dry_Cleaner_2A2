#include "materiel.h"
#include<qfiledialog.h>
#include "excel.h"
#include <QDate>

materiel::materiel(QString ref_m,QString model_m,QString etat_m,QString date_acham,QString tempera_m,QString image_m)
{

    this->ref_m=ref_m;
    this->model_m=model_m;
    this->date_acham=date_acham;
    this->etat_m=etat_m;
    this->image_m=image_m;
    this->tempera_m=tempera_m;


}

bool materiel::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO MATERIELS (REF_M,MODEL_M,DATE_ACHAM,ETAT_M,TEMPERA_M,IMAGE_M) VALUES (:ref_m, :model_m, :date_acham, :etat_m, :tempera_m, :image_m)");
query.bindValue(":tempera_m",tempera_m);
query.bindValue(":ref_m",ref_m);
query.bindValue(":model_m",model_m);
query.bindValue(":date_acham",date_acham);
query.bindValue(":etat_m",etat_m);
query.bindValue(":image_m",image_m);

 query.exec();
}

QSqlQueryModel * materiel::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M,IMAGE_M  FROM MATERIELS");
    qry.exec();
    model->setQuery(qry);

    return model;

}
bool materiel::supprimer(materiel m)
{
QSqlQuery query;
QString ref_m;
ref_m=m.getRef_m();
query.prepare("DELETE FROM MATERIELS WHERE REF_M='"+ref_m+"'");
//query.bindValue(":ref_m",ref_m);
query.exec();
}

/*void materiel::modifier(materiel m)
{
 QString model_m,etat_m,date_acham,ref_m;
 QString t
 model_m=m.getModel_m();
 etat_m=m.getEtat_m();
 date_acham=m.getDate_acham();
 ref_m=m.getRef_m();
 tempera_m=m.getTempera_m();

 QSqlQuery query;
 query.prepare("UPDATE MATERIELS set REF_M='"+ref_m+"',ETAT_M='"+etat_m+"',DATE_ACHAM='"+date_acham+"',MODEL_M='"+model_m+"',TEMPERA_M='"+tempera_m+"'");
}*/
bool materiel::modifier()
{
QSqlQuery query;
query.prepare("UPDATE MATERIELS SET REF_M='"+ref_m+"',ETAT_M='"+etat_m+"',DATE_ACHAM='"+date_acham+"',MODEL_M='"+model_m+"',TEMPERA_M='"+tempera_m+"'WHERE MATERIEL_ID =(SELECT MATERIEL_ID FROM MATERIELS WHERE REF_M='"+ref_m+"' )");

 query.exec();
}
QSqlQueryModel * materiel::triedate()
{
    QSqlQueryModel * modeldate=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS ORDER BY DATE_ACHAM ");
    qry.exec();

    modeldate->setQuery(qry);

    return modeldate;
}

QSqlQueryModel * materiel::trieetat()
{
    QSqlQueryModel * modeletat=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS ORDER BY ETAT_M ");
    qry.exec();
    modeletat->setQuery(qry);

    return modeletat;
}
QSqlQueryModel * materiel::trienbrproduit()

{
    QSqlQueryModel * modelnbrprod=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS ORDER BY NBR_PRODM  ");
    qry.exec();
    modelnbrprod->setQuery(qry);

    return modelnbrprod;
}

QSqlQueryModel * materiel::chercher(QString reche)

{

    QString query="SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS WHERE REF_M LIKE'%"+reche+"%' OR MODEL_M LIKE '%"+reche+"%'";
    QSqlQueryModel*modelrech=new QSqlQueryModel();
    QSqlQuery qry;
qry.prepare(query);
qry.exec();
modelrech->setQuery(qry);
return modelrech;
}

QSqlQueryModel * materiel::afficherMachineForExcel()
{
    QSqlQueryModel * modelexcel=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT MODEL_M,TEMPERA_M,REF_M,ETAT_M,DATE_ACHAM FROM MATERIELS ");
   qry.exec();
   modelexcel->setQuery(qry);

    return modelexcel ;
}

/*bool materiel::ajoutImage()
{

        QSqlQuery query;
        query.prepare("INSERT INTO MATERIELS (IMAGE_M) VALUES (:image_m)");
        query.bindValue(":image_m",image_m);
        query.exec();
}*/
//afficher historique
QSqlQueryModel * materiel::afficher_historique(){
    QSqlQueryModel * modelhisto =new QSqlQueryModel();
    QSqlQuery qry;
    QString query="SELECT REF_H,DATE_H,DESC_H FROM HISTORIQUE";
    qry.prepare(query);
    qry.exec();
    modelhisto->setQuery(qry);

    return modelhisto;

}
//ajouter a la bd historique en cliquant sur boutton valider
void materiel::ajouter_valid(QString ref){
QString desc="ajout";
QString date =QDate::currentDate().toString("dd.MM.yyyy");
QSqlQuery qry;
qry.prepare("INSERT INTO HISTORIQUE (REF_H,DATE_H,DESC_H) VALUES (:ref_h,:date_h,:desc_h)");
//QString sQuery="INSERT INTO HISTORIQUE (REF_H,DATE_H,DESC_H) VALUES (:ref_h,:date_h,:desc_h)";
qry.bindValue(":ref_h",ref);
qry.bindValue(":date_h",date);
qry.bindValue(":desc_h",desc);
qry.exec();
}
//ajouter a la bd historique en cliquant sur boutton supprimer
void materiel::ajouter_suppri(QString ref){
    QString desc="suppression";
    QString date =QDate::currentDate().toString("dd.MM.yyyy");
    QSqlQuery qry;
    qry.prepare("INSERT INTO HISTORIQUE (REF_H,DATE_H,DESC_H) VALUES (:ref_h,:date_h,:desc_h)");
    //QString sQuery="INSERT INTO HISTORIQUE (REF_H,DATE_H,DESC_H) VALUES (:ref_h,:date_h,:desc_h)";
    qry.bindValue(":ref_h",ref);
    qry.bindValue(":date_h",date);
    qry.bindValue(":desc_h",desc);
    qry.exec();

}
//ajouter a la bd historique en cliquant sur boutton modif
void materiel::ajouter_modif(QString ref){
    QString desc="modification";
    QString date =QDate::currentDate().toString("dd.MM.yyyy");
    QSqlQuery qry;
    qry.prepare("INSERT INTO HISTORIQUE (REF_H,DATE_H,DESC_H) VALUES (:ref_h,:date_h,:desc_h)");
    //QString sQuery="INSERT INTO HISTORIQUE (REF_H,DATE_H,DESC_H) VALUES (:ref_h,:date_h,:desc_h)";
    qry.bindValue(":ref_h",ref);
    qry.bindValue(":date_h",date);
    qry.bindValue(":desc_h",desc);
    qry.exec();

}
