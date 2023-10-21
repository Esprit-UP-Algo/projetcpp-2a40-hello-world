
#include "employe.h"
#include<QDate>
#include<QIntValidator>
#include<QSpinBox>
#include<QSqlQueryModel>
#include<QObject>
employe::employe(QString id,QString nom,QString prenom,int salaire,QDate date,QSpinBox *nb)
{
this->id=id;
this->nom=nom;
this->prenom=prenom;
this->salaire=salaire;
this->dtn=date;
this->nbx=nb;
}
void employe::setid(QString n){id=n;}
void employe::setnom(QString n){nom=n;}
void employe::setprenom(QString n){prenom=n;}
void employe::setsalaire(int n){salaire=n;}
void employe::setdtn(QDate n){dtn=n;}
void employe::setnbx(QSpinBox *n){nbx=n;}


QString employe::get_id(){return id;}
QString employe::get_nom(){return nom;}
QString employe::get_prenom(){return prenom;}
int employe::get_salaire(){return salaire;}
QDate employe::get_dtn(){return dtn;}
QSpinBox* employe:: get_nbx(){return nbx;}

bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe(id,nom,prenom,salaire,daten,nba) VALUES(:id,:nom,:prenom,:salaire,:daten,:nba)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":daten",dtn);;
    query.bindValue(":nba",nbx);

return query.exec();}

QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel*model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM employe");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEN"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBA"));
    return model;
}
bool employe::supprimer(QString id)
{ QSqlQuery query;
    query.prepare("delete from employe where id=:id");
    query.bindValue(":id",id);
    return query.exec();
}



