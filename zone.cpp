 #include "zone.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
Zone::Zone(int  identifiant, QString nom,QString emplacement,int capacite,QString etat,QString jour) {
this->identifiant=identifiant;this->nom=nom;this->emplacement=emplacement;this->capacite=capacite;this->etat=etat;this->jour=jour;}
Zone::Zone(QString nom,QString emplacement,int capacite,QString etat,QString jour) {
this->nom=nom;this->emplacement=emplacement;this->capacite=capacite;this->etat=etat;this->jour=jour;}
bool Zone::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ZONES(IDENTIFIANT, NOM, EMPLACEMENT, CAPACITE, ETAT, TYPE) VALUES (:IDENTIFIANT, :NOM, :EMPLACEMENT, :CAPACITE, :ETAT, :TYPE)");
    query.bindValue(":IDENTIFIANT", identifiant);
    query.bindValue(":NOM", nom);
    query.bindValue(":EMPLACEMENT",emplacement);
    query.bindValue(":CAPACITE",capacite);
    query.bindValue(":ETAT", etat);
    query.bindValue(":TYPE", jour);

    return query.exec();
}
bool Zone::supprimer(int identifiant) {
    QSqlQuery query;
    query.prepare("DELETE FROM ZONES WHERE IDENTIFIANT=:IDENTIFIANT");
    query.bindValue(":IDENTIFIANT", identifiant);

    if (query.exec() && query.numRowsAffected() > 0) {
        // La requête a réussi et au moins un enregistrement a été supprimé
        return true;
    } else {
        // Aucun enregistrement correspondant n'a été supprimé
        return false;
    }
}

QSqlQueryModel* Zone:: afficher(){
 QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM  ZONES");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMPLACEMENT"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("CAPACITE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));
       return model;
}
bool Zone::Modifier(int identifiant)
{


    QSqlQuery query;
    QString identifiant_string= QString::number(identifiant);
          query.prepare("UPDATE ZONES SET NOM=:NOM,EMPLACEMENT=:EMPLACEMENT,CAPACITE=:CAPACITE,ETAT=:ETAT,TYPE=:TYPE WHERE IDENTIFIANT=:IDENTIFIANT;");
          query.bindValue(":IDENTIFIANT", identifiant);
          query.bindValue(":NOM", nom);
          query.bindValue(":EMPLACEMENT", emplacement);
          query.bindValue(":CAPACITE", capacite);
          query.bindValue(":ETAT", etat);
          query.bindValue(":TYPE", jour);
          return query.exec();
}
