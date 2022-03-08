#include "materiel.h"



materiel::materiel(QString ref_m,QString model_m,QString etat_m,QString date_acham,QString tempera_m)
{

    this->ref_m=ref_m;
    this->model_m=model_m;
    this->date_acham=date_acham;
    this->etat_m=etat_m;
    //this->image_m=image_m;
    this->tempera_m=tempera_m;


}

bool materiel::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO MATERIELS (REF_M,MODEL_M,DATE_ACHAM,ETAT_M,TEMPERA_M) VALUES (:ref_m, :model_m, :date_acham, :etat_m, :tempera_m)");
query.bindValue(":tempera_m",tempera_m);
query.bindValue(":ref_m",ref_m);
query.bindValue(":model_m",model_m);
query.bindValue(":date_acham",date_acham);
query.bindValue(":etat_m",etat_m);

 query.exec();

//query.bindValue(":image_m",mo.get);

/*if(query.exec())
{
    QMessageBox::critical(nullptr, QObject::tr("OK"),
                             QObject::tr("ajout effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                             QObject::tr("ajout non effectué \n"
                                         "click cancel to exit."),QMessageBox::Cancel);

return query.exec();*/


}
QSqlQueryModel * materiel::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("model_m"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_acham"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("tempera_m"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ref_m"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat_m"));
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
query.prepare("UPDATE MATERIELS SET REF_M='"+ref_m+"',ETAT_M='"+etat_m+"',DATE_ACHAM='"+date_acham+"',MODEL_M='"+model_m+"',TEMPERA_M='"+tempera_m+"'WHERE MATERIEL_ID=(SELECT MATERIEL_ID FROM MATERIELS WHERE REF_M='"+ref_m+"' OR ETAT_M='"+etat_m+"' OR DATE_ACHAM='"+date_acham+"' OR MODEL_M='"+model_m+"' OR TEMPERA_M='"+tempera_m+"')");

 query.exec();
}
QSqlQueryModel * materiel::triedate()
{
    QSqlQueryModel * modeldate=new QSqlQueryModel();
    modeldate->setQuery("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS ORDER BY DATE_ACHAM ");
    modeldate->setHeaderData(0,Qt::Horizontal,QObject::tr("model_m"));
    modeldate->setHeaderData(1,Qt::Horizontal,QObject::tr("date_acham"));
    modeldate->setHeaderData(2,Qt::Horizontal,QObject::tr("tempera_m"));
    modeldate->setHeaderData(3,Qt::Horizontal,QObject::tr("ref_m"));
    modeldate->setHeaderData(4,Qt::Horizontal,QObject::tr("etat_m"));
    return modeldate;
}

QSqlQueryModel * materiel::trieetat()
{
    QSqlQueryModel * modeletat=new QSqlQueryModel();
    modeletat->setQuery("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS ORDER BY ETAT_M ");
    modeletat->setHeaderData(0,Qt::Horizontal,QObject::tr("model_m"));
    modeletat->setHeaderData(1,Qt::Horizontal,QObject::tr("date_acham"));
    modeletat->setHeaderData(2,Qt::Horizontal,QObject::tr("tempera_m"));
    modeletat->setHeaderData(3,Qt::Horizontal,QObject::tr("ref_m"));
    modeletat->setHeaderData(4,Qt::Horizontal,QObject::tr("etat_m"));
    return modeletat;
}
QSqlQueryModel * materiel::trienbrproduit()

{
    QSqlQueryModel * modelnbrprod=new QSqlQueryModel();
    modelnbrprod->setQuery("SELECT MODEL_M,DATE_ACHAM,TEMPERA_M,REF_M,ETAT_M FROM MATERIELS ORDER BY NBR_PRODM  ");
    modelnbrprod->setHeaderData(0,Qt::Horizontal,QObject::tr("model_m"));
    modelnbrprod->setHeaderData(1,Qt::Horizontal,QObject::tr("date_acham"));
    modelnbrprod->setHeaderData(2,Qt::Horizontal,QObject::tr("tempera_m"));
    modelnbrprod->setHeaderData(3,Qt::Horizontal,QObject::tr("ref_m"));
    modelnbrprod->setHeaderData(4,Qt::Horizontal,QObject::tr("etat_m"));
    return modelnbrprod;
}
