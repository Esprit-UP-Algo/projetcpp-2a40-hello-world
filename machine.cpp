#include "machine.h"
#include<QSqlQuery>
#include<QDebug>
#include<QObject>
#include <QPrinter>
#include <QTextDocument>
#include<QtCharts>
#include<QtSql>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <iostream>

machine::machine()
{
  serie="";
  etat="";
  fonction="";
  position="";
  nb_heures=0;
  q_carburant=0;
}
machine::machine(QString serie,QString etat,QString fonction,QString position,int nb_heures,int q_carburant)
{
    this->serie=serie;
    this->etat=etat;
    this->fonction=fonction;
    this->position=position;
    this->nb_heures=nb_heures;
    this->q_carburant=q_carburant;
}
void machine::setserie(QString s){serie=s;}
void machine::setetat(QString t){etat=t;}
void machine::setnb_heures(int nb){nb_heures=nb;}
void machine::setfonction(QString f){fonction=f;}
void machine::setposition(QString p){position=p;}
void machine::setq_carburant(int qc){q_carburant=qc;}


QString machine::getserie(){return serie;}
QString machine::getetat(){return etat;}
int machine::getnb_heures(){return nb_heures;}
QString machine::getfonction(){return fonction;}
QString machine::getposition(){return position;}
int machine::getq_carburant(){return q_carburant;}
//crud
//fonction ajouter
bool machine::ajouter()
{

    QSqlQuery query;
         query.prepare("INSERT INTO machines (serie, etatm, fonction,position,qnt_carburant,nombre_heure) "
                       "VALUES (:serie, :etatm, :fonction,:position,:qnt_carburant,:nombre_heure)");
         query.bindValue(":serie", serie);
         query.bindValue(":etatm", etat);
         query.bindValue(":fonction", fonction);
         query.bindValue(":position", position);
         QString qnt_string=QString::number(q_carburant);
         query.bindValue(":qnt_carburant", qnt_string);
         QString nb_string=QString::number(nb_heures);
         query.bindValue(":nombre_heure", nb_string);
         return query.exec();


}
//afficher
QSqlQueryModel* machine::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
      model->setQuery("SELECT serie,etatm,fonction,position,qnt_carburant,nombre_heure FROM machines ORDER BY fonction ASC");
          //model->setQuery("SELECT *  FROM MACHINES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("serie"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("fonction"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("position"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("qnt_carburant"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb_heure"));

return model;
}
//supprimer
bool machine::supprimer(const QString &seri)
{
    QSqlQuery checkQuery;

         checkQuery.prepare("SELECT SERIE FROM machines where SERIE= :seri");
        checkQuery.bindValue(0, seri);
        if (checkQuery.exec()&&checkQuery.next())
        {QSqlQuery deleteQuery;
            deleteQuery.prepare("Delete from machines where SERIE= :seri");
            deleteQuery.bindValue(0, seri);
            return deleteQuery.exec();
        }
        else
            return false;
}
//modifier
bool machine::updateData( QString seri)
{
    QSqlQuery query;
    query.prepare("UPDATE machines SET ETATM = :etat, FONCTION = :fonction, POSITION = :position, QNT_CARBURANT = :q_carburant, NOMBRE_HEURE = :nb_heures WHERE SERIE = :serie");
    query.bindValue(":etat", etat);
    query.bindValue(":fonction", fonction);
    query.bindValue(":position", position);
    query.bindValue(":q_carburant", q_carburant);
    query.bindValue(":nb_heures", nb_heures);
    query.bindValue(":serie", seri);


      return (query.exec());

}
//chercher
QSqlQueryModel* machine::rechercherParSerie(QString seri)
{


    QSqlQuery query;
    query.prepare("SELECT * FROM machines WHERE serie = :serie");
    query.bindValue(":serie", seri);

    if (query.exec())
    {
        QSqlQueryModel *searchResultModel = new QSqlQueryModel();
        searchResultModel->setQuery(query);
        return searchResultModel;

    }
    else
        return nullptr;
    }
//exportation pdf
bool machine::exporterMachinesEnPannePdf(const QString &nomFichier)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nomFichier);

    QTextDocument document;
    QSqlQueryModel *model = afficher(); // Assurez-vous que cette fonction renvoie le modèle de toutes les machines.

    QString html = "<html><body><table border='1'>";
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        QString etat = model->data(model->index(row, 1)).toString();

        if (etat.toLower() == "en panne") {
            html += "<tr>";
            for (int col = 0; col < columnCount; ++col) {
                QString data = model->data(model->index(row, col)).toString();
                html += "<td>" + data + "</td>";
            }
            html += "</tr>";
        }
    }

    html += "</table></body></html>";

    document.setHtml(html);
    document.print(&printer);

    return true; // L'exportation PDF a réussi
}

//chercher pour laison arduino
QString machine::rechercherParSerieFormat()
{
    QString serie;

    QSqlQuery query;
    query.prepare("SELECT serie FROM machines WHERE serie LIKE '000tunisie%'");

    if (query.exec() && query.next()) {
        serie = query.value(0).toString();
    } else {
        qDebug() << "Échec de l'exécution de la requête SQL : " << query.lastError().text();
    }

    return serie;
}
