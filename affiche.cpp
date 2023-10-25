#include "affiche.h"
#include "ui_affiche.h"

affiche::affiche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affiche)
{
    ui->setupUi(this);
}

affiche::~affiche()
{
    delete ui;
}
void affiche::setagri(agri a)
{
    ui->type->setText(a.gettype());
    ui->type_p->setText(a.gettdp());
    QString text= QString::number(a.getpda());
    ui->prix_achat->setText(text);
    QString text1= QString::number(a.getpdv());
    ui->prix_vente->setText(text1);
    QString text2= QString::number(a.getquantite());
    ui->quantite_p->setText(text2);
    QString date2= (a.getdate()).toString("dd/mm/yyyy");
    ui->datede->setText(date2);
}

