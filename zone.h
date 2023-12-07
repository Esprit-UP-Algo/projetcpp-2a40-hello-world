#ifndef ZONE_H
#define ZONE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class Zone
{
    int identifiant,capacite;
   QString nom,emplacement,etat,jour;

public:
   Zone (QString,QString,int,QString,QString);
   Zone(){}
   Zone(int,QString,QString,int,QString,QString);
    int  get_identifinat(){return identifiant;}
   QString get_nom(){return nom;}
   QString get_emplacement(){return emplacement;}
   int get_capacite(){return capacite;}
   QString get_etat(){return etat;}
   QString get_jour(){return jour;}
   void setidentifiant (int n){identifiant =n;}
   void setnom (QString n){nom=n;}
   void setemplacement (QString n){emplacement=n;}
   void setcapacite (int n){capacite=n;}
   void setetat (QString n){etat =n;}
   void setjour (QString n){jour =n;}
   bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int identifiant );
   bool Modifier(int identifiant);
   QSqlQueryModel* affichernom();
};

#endif // ZONE_H
