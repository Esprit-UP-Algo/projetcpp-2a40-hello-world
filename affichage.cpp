#include "affichage.h"
#include "ui_affichage.h"

affichage::affichage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affichage)
{
    ui->setupUi(this);
}

affichage::~affichage()
{
    delete ui;
}
void affichage::setmachine(machine m)
{
 ui->serie->setText(m.getserie());
 ui->etat->setText(m.getetat());
 ui->employe->setText(m.getemploye());
 ui->fonction->setText(m.getfonction());
 ui->position->setText(m.getposition());
 QString text= QString::number(m.getdepenses());
 ui->depenses->setText(text);

}

