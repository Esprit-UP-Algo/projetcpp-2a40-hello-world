#include "animaux.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QSqlQueryModel>
animaux::animaux(int identifiant, QString categorie, float masse, float taille,QString etat,QString ida) {
    this->identifiant= identifiant; // Assuming identifiant corresponds to the 'nom' field.
    this->categorie = categorie; // Assuming categorie corresponds to the 'emplacement' field.
    this->masse = masse; // Assuming masse corresponds to the 'capacite' field.
    this->taille = taille; // Assuming taille corresponds to the 'saisons' field.
    this->etat=etat;
    this->ida=ida;

}

bool animaux::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO ANNIMAUX(IDENTIFIANT, CATEGORIE, MASSE, TAILLE, ETAT , IDA) VALUES (:IDENTIFIANT, :CATEGORIE, :MASSE, :TAILLE, :ETAT, :IDA)");
    query.bindValue(":IDENTIFIANT", identifiant);
    query.bindValue(":CATEGORIE", categorie);
    query.bindValue(":MASSE", masse);
    query.bindValue(":TAILLE", taille);
    query.bindValue(":ETAT", etat);
    query.bindValue(":IDA", ida);
    return query.exec();
}

bool animaux::supprimer(int identifiant) {
    QSqlQuery query;
    query.prepare("DELETE FROM ANNIMAUX WHERE IDENTIFIANT = :IDENTIFIANT");
    query.bindValue(":IDENTIFIANT", identifiant);

    if (query.exec() && query.numRowsAffected() > 0) {
        // The query was successful, and at least one record was deleted.
        return true;
    } else {
        // No matching records were deleted.
        return false;
    }
}

QSqlQueryModel* animaux::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT IDENTIFIANT, CATEGORIE, MASSE, TAILLE, ETAT, IDA ,VACCINATION FROM ANNIMAUX");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MASSE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TAILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("IDA"));
    return model;
}

bool animaux::Modifier(int identifiant, QString categorie, float masse, float taille,QString etat,QString ida)
{


    QSqlQuery query;
    QString identifiant_string= QString(identifiant);
          query.prepare("UPDATE ANNIMAUX SET CATEGORIE=:CATEGORIE,MASSE=:MASSE,TAILLE=:TAILLE,ETAT=:ETAT,IDA=:IDA WHERE IDENTIFIANT=:IDENTIFIANT;");
          query.bindValue(":IDENTIFIANT", identifiant);
          query.bindValue(":CATEGORIE", categorie);
          query.bindValue(":MASSE", masse);
          query.bindValue(":TAILLE", taille);
          query.bindValue(":ETAT", etat);
           query.bindValue(":IDA",ida);
          return query.exec();
}
QSqlQueryModel* animaux::chercher(QString critere, QString rech) {
    QSqlQueryModel *model = new QSqlQueryModel();

    QString querystr = "SELECT * FROM  ANNIMAUX WHERE " + critere + " LIKE :rech";
    QSqlQuery query;
    query.prepare(querystr);
    query.bindValue(":rech", rech);

    if (query.exec()) {
        model->setQuery(query);
    }

    // Définissez les en-têtes ici...

    return model;
}
QSqlQueryModel* animaux::tri()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM ANNIMAUX ORDER BY IDENTIFIANT");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("masse"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("taille"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("ida"));

   return  model;

}
QSqlQueryModel* animaux::trinom()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM ANNIMAUX ORDER BY MASSE ");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("masse"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("taille"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("ida"));
   return  model;
}
QSqlQueryModel* animaux::tricapacite()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM ANNIMAUX ORDER BY TAILLE ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("masse"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("taille"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("etat"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("ida"));

   return  model;

}
