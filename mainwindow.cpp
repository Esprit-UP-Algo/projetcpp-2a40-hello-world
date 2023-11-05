include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include<QDebug>
#include<QApplication>
#include<QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabm->setModel(m.afficher());
     ui->q_carburant->setValidator( new QIntValidator(0,200, this));
     ui->nb_heures->setValidator(new QIntValidator(0,1000, this));
    QRegExp regex("[A-Za-z0-9]+");
     QRegExpValidator *validator = new QRegExpValidator(regex, this);
     ui->serie->setValidator(validator);

     QRegExp reg("^(en panne|fonctionnelle)$");
     QRegExpValidator *valid = new QRegExpValidator(reg, this);
     ui->etat->setValidator(valid);
     //Tracteur,Moissonneuse,Épandeur d'engrais,Pulvérisateur,Semoir

    QRegExp re("^(labourage|recolte|fertilisation|semis|pulverisation)$");
     QRegExpValidator *vali = new QRegExpValidator(re, this);
     ui->fonction->setValidator(vali);


     ui->chercher_2->setIcon(QIcon("///C:/Users/HP/Desktop/gestiondesmachines/chercher.png"));


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_ajouter_clicked()
{

    QString serie=ui->serie->text();
    QString etat=ui->etat->text();
    QString fonction=ui->fonction->text();
    QString position=ui->position->text();
     int nb_heures=ui->nb_heures->text().toInt();
      int q_carburant=ui->q_carburant->text().toInt();
      machine m (serie,etat,fonction,position,nb_heures,q_carburant);
      bool test=m.ajouter();
      if (test)
      {
       QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
                ui->tabm->setModel(m.afficher());


      }
      else
          QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectuer.\n""click cancel to exit."),QMessageBox::Cancel);


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






void MainWindow::on_supprimer_clicked()
{

    QString serie=(ui->supp->text());
    bool test=m1.supprimer(serie);
    if (test)
    {
     QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("suppression effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
     ui->tabm->setModel(m.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("suppression non effectuer.\n""click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_modifier_clicked()
{
    machine m;
    m.setserie(ui->serie->text());
       m.setetat (ui->etat->text());
        m.setfonction( ui->fonction->text());
        m.setposition ( ui->position->text());
        m.setq_carburant( ui->q_carburant->text().toInt());
       m.setnb_heures( ui->nb_heures->text().toInt());

        bool success = m.updateData(m.getserie());

        if (success)
        {
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("mise a jour  effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
             ui->tabm->setModel(m.afficher());
        }
        else
        {

                QMessageBox::critical(this, tr("Échec de l'update"), tr("La mise à jour des données a échoué."));
        }
}

void MainWindow::on_chercher_2_clicked()
{
    machine m;
    m.setserie(ui->serie->text());


   QSqlQueryModel *result = m.rechercherParSerie(m.getserie());

    if (result) {
        ui->tabm->setModel(result);
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("recherche effectuer.\n""click cancel to exit."),QMessageBox::Cancel);

    } else {
        QMessageBox::critical(this, tr("Échec de la recherche"), tr("La recherche a échoué."));
    }
}