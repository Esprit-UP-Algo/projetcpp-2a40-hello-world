
#include "connexion.h"

Connexion::Connexion()
{
}

bool Connexion::createconnect()
{
 QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;

db.setDatabaseName("source_Projet2A");
db.setUserName("ranim");//inserer nom de l'utilisateur
db.setPassword("ranim");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connexion::closeconnexion(){db.close();}
