#ifndef AGRI_H
#define AGRI_H
#include<QString>
#include<QDate>
#include<QSqlQuery>


class agri
{
private:
  QString type, tdp;
  QDate date;
  float pda, pdv;
  int quantite;
public:
    agri();
    void settype(QString n);
    void settdp(QString n);
    void setdate(QDate n);
    void setpda(float n);
    void setpdv(float n);
    void setquantite(int n);
    QString gettype();
    QString gettdp();
    QDate getdate();
    float getpda();
    float getpdv();
    int getquantite();

};

#endif // AGRI_H
