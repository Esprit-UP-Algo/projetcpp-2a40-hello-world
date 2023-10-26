#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include "affichage.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton button;
    button.setIcon(QIcon("home.png"));
    button.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    machine m;
    m.setserie(ui->serie->text());
     m.setetat(ui->etat->text());
      m.setfonction(ui->fonction->text());
       m.setemploye(ui->employe->text());
        m.setposition(ui->position->text());
        QString p=ui->depenses->text();
        bool ok;
        float pfloat=p.toFloat(&ok);
        if (ok)
        {
            m.setdepenses(pfloat);

        }
        else
        {  qDebug() <<"convertion en float a echoué";}


    affichage a;
    a.setmachine(m);
    a.exec();
}


void MainWindow::on_clients_clicked()
{
        ui->animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
        ui->clients->setStyleSheet(" QPushButton { background-color:#84B7A4  ;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E ;}");
        ui->machines->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
        ui->employes->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
        ui->agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_machines_clicked()
{
    ui->animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->machines->setStyleSheet(" QPushButton { background-color:#7DB5A2;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E ;}");
    ui->employes->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_employes_clicked()
{   ui->animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ; }");
    ui->employes->setStyleSheet(" QPushButton { background-color:#73B19B;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");

}

void MainWindow::on_animaux_clicked()
{
    ui->animaux->setStyleSheet(" QPushButton { background-color:#64A991;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
        ui->clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
        ui->machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E   ;}");
        ui->employes->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E ; }");
        ui->agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_agri_clicked()
{
    ui->animaux->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
        ui->clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
        ui->machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E   ;}");
        ui->employes->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E ; }");
        ui->agri->setStyleSheet(" QPushButton { background-color:#519B80;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}


