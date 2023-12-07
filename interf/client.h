#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlQuery>
class Client
{
private:
    QString nom, prenom, mail,tel, rech;
    int id;
    QDate date;

public:

    //constructeurs
    Client();
    Client(QString, QString, QString, int, QString, QDate );

   //setters
    void setnom(QString n);
    void setprenom(QString n);
    void setid(int n);
    void setmail(QString n);
    void setdate(QDate n);
    void settel(QString n);
    void setrech (QString n);
    //getters
    QString get_nom();
    QString get_prenom();
    int get_id();
    QString get_mail();
    QDate get_date();
    QString get_tel();
    QString get_rech();

    //Fonctionalites
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer (int id);
    bool update();
    bool trier();
    QSqlQueryModel* chercher(int id);
    bool exporterPdf(const QString &nomFichier);
    int getNombreClientsParMois(int mois);




};

#endif // CLIENTT_H
