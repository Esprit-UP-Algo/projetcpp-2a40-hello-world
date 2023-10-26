#ifndef MACHINE_H
#define MACHINE_H
#include<QString>

class machine
{
private:
    QString serie,etat,employe,fonction,position;
    float depenses;
public:
    machine();
    void setserie(QString s);
    void setetat(QString t);
    void setemploye(QString e);
    void setfonction(QString f);
    void setposition(QString p);
    void setdepenses(float px);
    QString getserie();
    QString getetat();
    QString getemploye();
    QString getfonction();
    QString getposition();
    float getdepenses();
};

#endif // MACHINE_H
