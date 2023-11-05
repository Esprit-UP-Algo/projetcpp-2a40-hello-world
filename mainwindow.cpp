#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agri.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include<iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString pattern = "^[a-zA-Z\\s]*$";
    QRegularExpression regex(pattern);
    ui->setupUi(this);
    ui->table->setModel(a.afficher());
    ui->quantite->setValidator(new QIntValidator (0,300,this));
    ui->id->setValidator(new QRegularExpressionValidator(regex,this));
    ui->type->setValidator(new QRegularExpressionValidator(regex,this));
    ui->pesticide->setValidator(new QRegularExpressionValidator(regex,this));
    ui->prix_achat->setValidator(new QDoubleValidator(this));
    ui->prix_vente->setValidator(new QDoubleValidator(this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    bool test;
    QString type=ui->type->text();
    QString tdp=ui->pesticide->text();
    QString ida=ui->id->text();
    float pdv=ui->prix_vente->text().toFloat();
    float pda=ui->prix_achat->text().toFloat();
    int quantite=ui->quantite->text().toInt();
    QDate datep = ui->date->date();
    agri a(ida,type,tdp,datep,pda,pdv,quantite);
    test=a.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
        ui->table->setModel(a.afficher());
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("ajout non effectué.\n "
                                        "click cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_button_clients_clicked()
{
    ui->button_animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet(" QPushButton { background-color:#84B7A4  ;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E ;}");
    ui->button_machines->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_machines_clicked()
{
    ui->button_animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet(" QPushButton { background-color:#7DB5A2;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E ;}");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_employ_clicked()
{
    ui->button_animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ; }");
    ui->button_employ->setStyleSheet(" QPushButton { background-color:#73B19B;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_animaux_clicked()
{
    ui->button_animaux->setStyleSheet(" QPushButton { background-color:#64A991;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E   ;}");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E ; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_agri_clicked()
{
    ui->button_animaux->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E   ;}");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E ; }");
    ui->button_agri->setStyleSheet(" QPushButton { background-color:#519B80;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_suppression_clicked()
{
    agri a1;
    a1.setida(ui->idsupp->text());
        bool test=a1.supprimer(a1.getida());
        if(test){
            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\nClick Cancel to exit."),QMessageBox::Cancel);
        }
        else {
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Suppression non effectuée.\nClick Cancel to exit."),QMessageBox::Cancel);
        }
        ui->table->setModel(a.afficher());
}

void MainWindow::on_modifier_clicked()
{
    agri a;
        a.setida(ui->id->text());
        a.settype(ui->type->text());
        a.settdp(ui->pesticide->text());
        a.setpda( ui->prix_achat->text().toFloat());
        a.setpdv( ui->prix_vente->text().toFloat());
        a.setquantite(ui->quantite->text().toInt());
        a.setdatep(ui->date->date());

            bool success = a.updateData(a.getida());

            if (success)
            {
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("mise a jour  effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
                 ui->table->setModel(a.afficher());
            }
            else
            {

                    QMessageBox::critical(this, tr("Échec de l'update"), tr("La mise à jour des données a échoué."));
            }
}
