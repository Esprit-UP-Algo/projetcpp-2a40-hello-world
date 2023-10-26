#include "machine.h"

machine::machine()
{
  serie="";
  etat="";
  employe="";
  fonction="";
  position="";
  depenses=0;
}
void machine::setserie(QString s){serie=s;}
void machine::setetat(QString t){etat=t;}
void machine::setemploye(QString e){employe=e;}
void machine::setfonction(QString f){fonction=f;}
void machine::setposition(QString p){position=p;}
void machine::setdepenses(float px){depenses=px;}


QString machine::getserie(){return serie;}
QString machine::getetat(){return etat;}
QString machine::getemploye(){return employe;}
QString machine::getfonction(){return fonction;}
QString machine::getposition(){return position;}
float machine::getdepenses(){return depenses;}
