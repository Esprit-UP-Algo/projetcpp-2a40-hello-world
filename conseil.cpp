#include "conseil.h"
#include "ui_conseil.h"

conseil::conseil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::conseil)
{
    ui->setupUi(this);
}

conseil::~conseil()
{
    delete ui;
}
void conseil::setLabelText(const QString &text)
{
    ui->type->setText(text);
    QFont font("Tahoma", 12);
    font.setItalic(true); // Modifier la police selon vos préférences
    ui->type->setFont(font);
    ui->type->setAlignment(Qt::AlignCenter);

}
void conseil::setLabelTextm(const QString &text)
{
    ui->maladie->setText(text);
    QFont font("Tahoma", 12);
    font.setItalic(true); // Modifier la police selon vos préférences
    ui->maladie->setFont(font);
    ui->maladie->setAlignment(Qt::AlignCenter);

}
void conseil::setLabelTextp(const QString &text)
{
    ui->pesticide->setText(text);
    QFont font("Tahoma", 12);
    font.setItalic(true); // Modifier la police selon vos préférences
    ui->pesticide->setFont(font);
    ui->pesticide->setAlignment(Qt::AlignCenter);

}
void conseil::setLabelText1(const QString &text)
{
    ui->label1->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label1->setFont(font);
}
void conseil::setLabelText2(const QString &text)
{
    ui->label2->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label2->setFont(font);
}
void conseil::setLabelText3(const QString &text)
{
    ui->label3->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label3->setFont(font);
}
void conseil::setLabelText4(const QString &text)
{
    ui->label4->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label4->setFont(font);
}
void conseil::setLabelText5(const QString &text)
{
    ui->label5->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label5->setFont(font);
}
void conseil::setLabelText6(const QString &text)
{
    ui->label6->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label6->setFont(font);
}
void conseil::setLabelText7(const QString &text)
{
    ui->attention->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->attention->setFont(font);

}
void conseil::setLabelText8(const QString &text)
{
    ui->label7->setText(text);
    QFont font("candara", 10);
    font.setItalic(true);
    ui->label7->setFont(font);
}
