#include "offre.h"

offre::offre()
{

}
bool offre::ajouterOffre()
{
    QSqlQuery query;
    query.prepare("INSERT INTO offre (offre_id,type_p, reduction ) VALUES ( :offre_id,:type_p, :reduction )");
    query.bindValue(":offre_id", offre_id);
    query.bindValue(":type_p", type_p);
    query.bindValue(":reduction", reduction);
    return query.exec();
}

QSqlQueryModel *offre::afficherOffre()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM offre");
    return model;
}
bool  offre::supprimerOffre()
{  QSqlQuery query;
    QString id_string=QString:: number(offre_id);
    query.prepare("Delete from offre where offre_id=:offre_id");
    query.bindValue(":offre_id", offre_id);
    return query.exec();
}
bool offre::modifierOffre()
{
    QSqlQuery query;
    query.prepare("UPDATE offre SET offre_id= :offre_id, type_p= :type_p,reduction= :reduction where offre_id= :offre_id ");
    query.bindValue(":offre_id", offre_id);
    query.bindValue(":type_p", type_p);
    query.bindValue(":reduction", reduction);
    return query.exec();
}
