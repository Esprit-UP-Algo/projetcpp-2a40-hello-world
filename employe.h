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
    QSpinBox *nbx;
public:
    employe(){};
    employe (QString ,QString ,QString,int,QDate ,QSpinBox *);
    void setid(QString n);
    void setnom(QString n);
    void setprenom(QString n);
    void setsalaire(int  n);
    void setdtn(QDate n);
    void setnbx(QSpinBox *n);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    int get_salaire();
    QDate get_dtn();
    QSpinBox* get_nbx();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
};

#endif // EMPLOYE_H
