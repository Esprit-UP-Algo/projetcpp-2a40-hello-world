#include "employe.h"
#include<QDate>
#include<QIntValidator>
#include<QSpinBox>
#include<QSqlQueryModel>
#include<QObject>
employe::employe(QString id,QString nom,QString prenom,int salaire,QDate date,int nb)
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
void employe::setnbx(int n){nbx=n;}


QString employe::get_id(){return id;}
QString employe::get_nom(){return nom;}
QString employe::get_prenom(){return prenom;}
int employe::get_salaire(){return salaire;}
QDate employe::get_dtn(){return dtn;}
int employe:: get_nbx(){return nbx;}

bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe(ide,nom,prenom,salaire,daten,nba) VALUES(:id,:nom,:prenom,:salaire,:daten,:nbx)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":daten",dtn);
    query.bindValue(":nbx",nbx);

return query.exec();}

QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel*model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM employe");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBA"));
    return model;
}
bool employe::supprimer(QString id)
{ QSqlQuery query;
    query.prepare("delete from employe where ide=:id");
    query.bindValue(":id",id);
    return query.exec();
}
bool employe::update()
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET ide=:id,nom=:nom,prenom=:prenom,salaire=:salaire,daten=:daten,nba=:nbx WHERE ide=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":daten",dtn);
    query.bindValue(":nbx",nbx);
    return query.exec();
}
bool employe::idExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employe WHERE ide= :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}
QSqlQueryModel* employe::afficher1()

{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY daten ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBA"));
    return model;
}






