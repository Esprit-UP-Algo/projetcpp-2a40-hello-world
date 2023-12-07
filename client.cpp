#include "client.h"
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QSqlError>
#include <QDebug>

Client::Client()
{
    nom = "";
    prenom = "";
    mail = "";
    id = 0;
    tel ="";
    date = QDate();
    rech = "";
}
Client::Client (QString nom, QString prenom, QString mail, int id , QString tel, QDate date )
{
    this->nom=nom;
    this->prenom=prenom;
    this->id=id;
    this->mail=mail;
    this->date=date;
    this->tel=tel;
}

void Client::setnom(QString n){nom=n;}
void Client::setprenom(QString n){prenom=n;}
void Client::setid(int n){id=n;}
void Client:: setrech(QString n) {rech=n;}
void Client::setmail(QString n){mail=n;}
void Client::setdate(QDate n){date=n;}
void Client::settel(QString n){tel=n;}

QString Client::get_nom(){return nom;}
QString Client::get_prenom(){return prenom;}
int Client::get_id(){return id;}
QString Client::get_mail(){return mail;}
QDate Client::get_date(){return date;}
QString Client::get_tel(){return tel;}
QString Client:: get_rech(){return rech;}

bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (idc, nom, prenom, date_a, adresse_mail, tel) "
                  "VALUES (:id, :nom, :prenom, :date, :mail, :tel)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date", date);
    query.bindValue(":mail", mail);
    query.bindValue(":tel", tel);


    return query.exec();
}
QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from client");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("date"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("tel"));
    return model;
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("delete from client where idc= :id");
    query.bindValue(":id",id);
    return query.exec();
}
bool Client::update()
{
    QSqlQuery query;
    query.prepare("UPDATE client SET idc=:id, nom=:nom, prenom=:prenom, date_a=:date, adresse_mail=:mail, tel=:tel WHERE idc=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date", date);
    query.bindValue(":mail", mail);
    query.bindValue(":tel", tel);



    if (query.exec()) {
        qDebug() << "Update successful";
        return true;
    } else {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }
}


bool Client::trier()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT ORDER BY date_a ASC");

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("tel"));

        return true;
    } else {
        return false;
    }
}

QSqlQueryModel *Client::chercher(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE idc = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        model->setQuery(query);
        return model;
    } else {
        delete model; // Supprimez le modèle si la recherche n'a pas abouti
        return nullptr;
    }
}

bool Client::exporterPdf(const QString &nomFichier)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nomFichier);

    QTextDocument document;
    QSqlQueryModel *model = afficher();

    QString html = "<html><body><table border='1'>";
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        html += "<tr>";
        for (int col = 0; col < columnCount; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            html += "<td>" + data + "</td>";
        }
        html += "</tr>";
    }
    html += "</table></body></html>";

    document.setHtml(html);
    document.print(&printer);

    return true; // L'exportation PDF a réussi
}

int Client::getNombreClientsParMois(int mois) //teb3a statistiques
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE EXTRACT(MONTH FROM date_a) = :mois");
    query.bindValue(":mois", mois);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
