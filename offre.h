#ifndef OFFRE_H
#define OFFRE_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <vector>


class offre
{
    int offre_id ;
    QString type_p ;
    QString reduction ;
public:
    offre();
    offre (int offre_id, QString type_p ,QString reduction)
    {
        this->offre_id=offre_id ;
        this->type_p=type_p ;
        this->reduction=reduction ;
    }

           //getters
           int getoffre_id(){return offre_id;};
           QString gettype_p(){return type_p;};
           QString getreduction() { return reduction; };


           //setters
           void setoffre_id(int id_o){offre_id=id_o;}
           void settype_p(QString t_o){type_p=t_o;}
           void setreduction(QString r_o) {reduction = r_o; }


           //fonctions
           bool ajouterOffre();
           bool modifierOffre();
           QSqlQueryModel *afficherOffre();
           bool supprimerOffre();
};

#endif // OFFRE_H
