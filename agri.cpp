#include "agri.h"

agri::agri()
{
    type="";
    date= QDate :: currentDate();
    tdp="";
    pda=0;
    pdv=0;
    quantite=0;
}


void agri:: settype(QString n){type=n;}
void agri:: settdp(QString n){tdp=n;}
void agri:: setdate(QDate n){date=n;}
void agri:: setpda(float n){pda=n;}
void agri:: setpdv(float n){pdv=n;}
void agri:: setquantite(int n){quantite=n;}


QString agri:: gettype(){return type;}
QString agri:: gettdp(){return tdp;}
QDate agri:: getdate(){return date;}
float agri:: getpda(){return pda;}
float agri:: getpdv(){return pdv;}
int agri:: getquantite(){return quantite;}
