#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setclient(Client c)
{
    ui->lineEdit_nomD->setText(c.get_nom());
    ui->lineEdit_prenomD->setText(c.get_prenom());
    ui->lineEdit_idD->setText(c.get_id());
    ui->lineEdit_mailD->setText(c.get_mail());
    ui->dateEditD->setDate(c.get_date());
    ui->lineEdit_telD->setText(c.get_tel());


}
