#ifndef ANIMAUX_H
#define ANIMAUX_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>
class animaux

{ int identifiant,masse,taille;
   QString  categorie, etat,vaccination,nourriture;
   QDate date_vaccination;

public:
   animaux() {}
   animaux(int,QString,float,float,QString,QString);
   int get_identifiant() { return identifiant; }
   QString get_categorie() { return categorie; }
   float get_masse() { return masse; }
   float get_taille() { return taille; }
   QString get_etat() { return etat; }

   void setidentifiant(int n) { identifiant = n; }
   void setcategorie(QString n) { categorie= n; }
   void setmasse(float n) { masse = n; }
   void settaille(float n) { taille = n; }
   void setetat(QString n) { etat = n; }

   bool ajouter();
   QSqlQueryModel *afficher();
   bool supprimer(int identifiant);
   bool Modifier(int  identifiant,QString categorie, float masse, float taille,QString etat,QString nourriture);
   QSqlQueryModel* affichernom();
   QSqlQueryModel* chercher(QString critere, QString rech);
   QSqlQueryModel* tri();
   QSqlQueryModel* trinom();
   QSqlQueryModel* tricapacite();
};




#endif // ANIMAUX_H
