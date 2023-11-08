#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QIntValidator>
#include<QDate>
#include<QSpinBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
class employe
{
private:
    QString id,nom,prenom,poste;
    int salaire;
    QDate dtn;
    int nbx;
public:
    employe(){};
    employe (QString ,QString ,QString,int,QDate ,int);
    void setid(QString n);
    void setnom(QString n);
    void setprenom(QString n);
    void setsalaire(int  n);
    void setdtn(QDate n);
    void setnbx(int);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    int get_salaire();
    QDate get_dtn();
    int get_nbx();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel* afficher1();
    bool supprimer(QString);
    void mettreAJour();
    bool update();
    bool idExists(int id);

};

#endif // EMPLOYE_H
