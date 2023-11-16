#include "benefice.h"
#include "ui_benefice.h"

benefice::benefice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::benefice)
{
    ui->setupUi(this);
}

benefice::~benefice()
{
    delete ui;
}
void benefice::setLabelText(const QString &text)
{
    ui->ben->setText(text);
    QFont font("Tahoma", 10, QFont::Bold);
    ui->ben->setFont(font);
    ui->ben->setAlignment(Qt::AlignCenter);

}
/*void benefice::setLabelText1(const QString &text)
{
    ui->c->setText(text);
    QFont font("Tahoma", 8, QFont::Bold);
    ui->c->setFont(font);
    ui->c->setAlignment(Qt::AlignCenter);

}*/
void benefice::setBeneficeTotalText(const QString& text)
{
    ui->res->setText(text);
    QFont font("Tahoma", 10, QFont::Bold);
    ui->res->setFont(font);
    ui->res->setAlignment(Qt::AlignCenter);

}
