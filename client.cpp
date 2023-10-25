#include "client.h"

Client::Client()
{
    nom="";
    prenom="";
    id="";
    mail="";
    //date
    tel="";

}
void Client::setnom(QString n){nom=n;}
void Client::setprenom(QString n){prenom=n;}
void Client::setid(QString n){id=n;}
void Client:: setrech(QString n) {rech=n;}
void Client::setmail(QString n){mail=n;}
void Client::setdate(QDate n){date=n;}
void Client::settel(QString n){tel=n;}

QString Client::get_nom(){return nom;}
QString Client::get_prenom(){return prenom;}
QString Client::get_id(){return id;}
QString Client::get_mail(){return mail;}
QDate Client::get_date(){return date;}
QString Client::get_tel(){return tel;}
QString Client:: get_rech(){return rech;}
