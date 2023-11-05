#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>
class Connexion
{
    QSqlDatabase db;
public:
    Connexion();
    bool createconnect();
    void closeconnexion();
};

#endif // CONNEXION_H
