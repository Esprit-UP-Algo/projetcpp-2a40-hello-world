#ifndef MACHINE_H
#define MACHINE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtWidgets>
#include <QtSql>

class machine
{
private:
    QString serie,etat,fonction,position;
    int q_carburant,nb_heures;


public:
    machine();
    machine(QString,QString,QString,QString,int,int);
    void setserie(QString s);
    void setetat(QString t);
    void setfonction(QString f);
    void setposition(QString p);
    void setnb_heures(int nb);
    void setq_carburant(int qc);
    QString getserie();
    QString getetat();
    QString getfonction();
    QString getposition();
    int getnb_heures();
    int getq_carburant();
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(const QString &seri);
    bool updateData( QString seri);
   QSqlQueryModel*rechercherParSerie(QString);
  bool exporterMachinesEnPannePdf(const QString &nomFichier);


};



#endif // MACHINE_H
