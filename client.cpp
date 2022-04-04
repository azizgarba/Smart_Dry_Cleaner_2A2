#include "client.h"
Client::Client()
{
cin="";
nom="";
prenom="";
adresse="";
num_tel="";
email="";
age="";
rech="";
}
//setters
void Client::set_cin(QString n){cin=n;}
void Client::set_nom(QString n){nom=n;}
void Client::set_prenom(QString n){prenom=n;}
void Client::set_adresse(QString n){adresse=n;}
void Client::set_num_tel(QString n){num_tel=n;}
void Client::set_email(QString n){email=n;}
void Client::set_age(QString n){age=n;};
//getters
QString Client::get_cin(){return cin;}
QString Client::get_nom(){return nom;}
QString Client::get_prenom(){return prenom;}
QString Client::get_adresse(){return adresse;}
QString Client::get_num_tel(){return num_tel;}
QString Client::get_email(){return email;}
QString Client::get_age(){return age;}
QString Client::get_rech(){return rech;}
//ajout d'un client
void Client::ajouter_client(Client c){
    QString sQuery="INSERT INTO CLIENTS (NOM_C,PRENOM_C,ADRESSE_C,NUMERO_TEL,EMAIL_C,CIN,AGE) VALUES (:nom,:prenom,:adresse,:num_tel,:email,:cin,:age)";

    QSqlQuery qry;

    qry.prepare(sQuery);
    qry.bindValue(":nom",c.get_nom());
    qry.bindValue(":prenom",c.get_prenom());
    qry.bindValue(":adresse",c.get_adresse());
    qry.bindValue(":num_tel",c.get_num_tel());
    qry.bindValue(":email",c.get_email());
    qry.bindValue(":cin",c.get_cin());
    qry.bindValue(":age",c.get_age());
    if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row created and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not created and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
//modifier un client via son l'id du client(PK)
void Client::modifier_client(Client c){

    QString nom,prenom,adresse,num_tel,email,cin,age;
    nom=c.get_nom();
    prenom=c.get_prenom();
    adresse=c.get_adresse();
    num_tel=c.get_num_tel();
    email=c.get_email();
    cin=c.get_cin();
    age=c.get_age();

    QString sQuery="UPDATE CLIENTS set CIN='"+cin+"',NOM_C='"+nom+"',PRENOM_C='"+prenom+"',ADRESSE_C='"+adresse+"',NUMERO_TEL='"+num_tel+"',EMAIL_C='"+email+"',AGE='"+age+"' WHERE ID_CLIENT=(SELECT ID_CLIENT FROM CLIENTS WHERE CIN='"+cin+"' or NOM_C='"+nom+"' or PRENOM_C='"+prenom+"' or ADRESSE_C='"+adresse+"' or NUMERO_TEL='"+num_tel+"' or EMAIL_C='"+email+"' or AGE='"+age+"')";

    QSqlQuery qry;

    qry.prepare(sQuery);
    if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row updated and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not updated and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
//supprimer un client via son cin
void Client::supprimer_client(Client c){

    QString cin;
    cin=c.get_cin();

    QString sQuery="DELETE FROM CLIENTS WHERE CIN='"+cin+"'";

    QSqlQuery qry;

    qry.prepare(sQuery);
    if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row deleted successfully.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not deleted.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
//afficher les clients
QSqlQueryModel* Client::afficher_client(){
   QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C,PTS_FIDELITE FROM CLIENTS";

   QSqlQueryModel* model=new QSqlQueryModel();

   QSqlQuery qry;

   qry.prepare(sQuery);

   qry.exec();
   model->setQuery(qry);
return model;
}
//afficher les clients selon le nom
QSqlQueryModel* Client::afficher_client_trie_nom(){
    QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C,PTS_FIDELITE FROM CLIENTS ORDER BY NOM_C";

    QSqlQueryModel*model1=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model1->setQuery(qry);
return model1;
}
//afficher les clients selon le prenom
QSqlQueryModel* Client::afficher_client_trie_prenom(){
    QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C,PTS_FIDELITE FROM CLIENTS ORDER BY PRENOM_C";

    QSqlQueryModel*model2=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model2->setQuery(qry);
return model2;
}
//afficher les clients selon l'age
QSqlQueryModel* Client::afficher_client_trie_age(){
    QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C,PTS_FIDELITE FROM CLIENTS ORDER BY AGE";

    QSqlQueryModel*model3=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model3->setQuery(qry);
return model3;
}
// afficher client recherche
QSqlQueryModel* Client::afficher_client_recherche(QString rech){
QString sQuery="SELECT CIN,NOM_C,PRENOM_C,AGE,ADRESSE_C,NUMERO_TEL,EMAIL_C,PTS_FIDELITE FROM CLIENTS WHERE NOM_C LIKE'%"+rech+"%' or PRENOM_C LIKE'%"+rech+"%'";

QSqlQueryModel*model4=new QSqlQueryModel();

QSqlQuery qry;

qry.prepare(sQuery);

qry.exec();
model4->setQuery(qry);
return model4;
}
//retourne prix initial
float Client::nbr_fidelite0(){
    QString sQuery="SELECT PRIX FROM PRODUITS";
    float prix=0;
    QSqlQuery qry;

    qry.prepare(sQuery);
    if(qry.exec()){
        while(qry.next()){
            prix=qry.value(0).toFloat();
        }
    }
    return prix;
}
//retourne le prix apres soustraction
float Client::nbr_fidelite(float prix){
while(prix>200){
if(prix>=200){
    prix=prix-200;
    return prix;
}
else return prix;}
}
//calcule le nbr de fidelite est decrimente le prix
void Client::nbr_fidelite2(float prix,QString nom){
    prix=nbr_fidelite0();
    float pts_fidelite;
    pts_fidelite=prix/2;
    QSqlQuery qry,qry1;
    if(pts_fidelite>=200){
    pts_fidelite=nbr_fidelite(pts_fidelite);
    QString prixx = QString::number(pts_fidelite);
    //qry1.prepare("UPDATE CLIENTS SET PTS_FIDELITE=");
    qry.prepare("UPDATE CLIENTS SET PTS_FIDELITE='"+prixx+"' WHERE NOM_C='"+nom+"'");
    if(qry.exec()){
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr(" successfully.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query not successful"),
                           QObject::tr("unsuccessfully.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query not successful"),
                           QObject::tr("don't have fidelity points.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }

}
//generate random string for coupon(lenght is 8)    !!!!!!!!!!!! to dooooo! !!!!!!!!!!!!!!!!!!!!
QString Client::coupon_generator() const{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
      const int randomStringLength = 8;

      QString randomString;
      for(int i=0; i<randomStringLength; ++i)
      {
          //int index = QRandomGenerator::generate() % possibleCharacters.length();
          //QChar nextChar = possibleCharacters.at(index);
          //randomString.append(nextChar);
      }
      return randomString;
}
//decremente les pts_fidelite apres avoir generer un coupon(PDF)
/*void Client::decre_pts_fidelite(QString nom){
    QString sQuery="SELECT PTS_FIDELITE FROM CLIENTS WHERE NOM_C='"+nom+"'";
    float pts_fidelite = 0;
    QSqlQuery qry,qry1;
    qry.prepare(sQuery);
    if(qry.exec())
    {
        while(qry.next()){
            pts_fidelite = qry.value(0).toFloat();
        }
    }
    pts_fidelite=pts_fidelite-50;
qDebug("it's me: %f",pts_fidelite);
    QString pts_fidelite1=QString::number(pts_fidelite);
    QString sQuery1="UPDATE CLIENTS SET PTS_FIDELITE='"+pts_fidelite1+"' WHERE NOM_C='"+nom+"'";
    qry1.prepare(sQuery1);
    if(qry1.exec()){
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr(" successfully.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query not successful"),
                           QObject::tr("unsuccessfully.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);}
}*/
