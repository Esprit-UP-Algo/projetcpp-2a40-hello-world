#ifndef AGRI_H
#define AGRI_H
#include<QString>
#include<QDate>
#include<qsqlquerymodel.h>
class agri
{
private:
  QString type, tdp, ida;
  QDate datep;
  float pda, pdv;
  int quantite;
public:
    agri();
    agri (QString, QString, QString, QDate,float, float, int);
    void settype(QString n);
    void settdp(QString n1);
    void setida(QString n2);
    void setdatep(QDate n3);
    void setpda(float n4);
    void setpdv(float n5);
    void setquantite(int n6);
    QString gettype();
    QString getida();
    QString gettdp();
    QDate getdatep();
    float getpda();
    float getpdv();
    int getquantite();
    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel *afficher();
    bool updateData(QString);
    QSqlQueryModel* rechercherPartype(QString);
    bool exporterPdf(const QString &nomFichier);
    float calculbenefice();
};

#endif // AGRI_H
