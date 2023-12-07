#include "dialog.h"
#include "ui_dialog.h"
#include "animaux.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include"mainwindow.h"
#include <QVBoxLayout>
#include<QCompleter>
#include<QPushButton>
#include<QTableWidget>
#include<QSqlQuery>
#include<QTableView>
#include <QStandardItemModel>
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


#include<QDateTime>
void Dialog::on_pushButton_valider_clicked()
{
    float coefficient_taille = 10.0;
    float coefficient_masse = 0.2;

    int identifiant = ui->lineEdit_id->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ANNIMAUX WHERE IDENTIFIANT = :identifiant");
    query.bindValue(":identifiant", identifiant);

    if (query.exec() && query.next()) {
        int masse = query.value("MASSE").toInt();
        int taille = query.value("TAILLE").toInt();
        QString categorie = query.value("CATEGORIE").toString();
        float score = (coefficient_taille * taille) + (coefficient_masse * masse);
        if (categorie == "Oiseaux") {
            QString etat = (score >= 50) ? "MALADE" : "SAIN";
            QString vaccination = (etat == "MALADE") ? "NON VACCINE" : "VACCINE";
            QString tempsVaccination = (etat == "SAIN") ? QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") : "";

            // Mise à jour de l'état dans la base de données
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat, TEMPS_VACCINATION = :tempsVaccination WHERE IDENTIFIANT = :identifiant");
            updateQuery.bindValue(":etat", etat);
            updateQuery.bindValue(":tempsVaccination", tempsVaccination);
            updateQuery.bindValue(":identifiant", identifiant);
            updateQuery.exec();

            // Affichage du tableau
            QTableWidget *tableWidget = new QTableWidget(1, 7, this);  // Ajoutez deux colonnes pour la vaccination et le temps de vaccination
            tableWidget->resize(800, 600);
            tableWidget->show();
            tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État" << "Vaccination" << "Temps de vaccination");

            tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
            tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
            tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
            tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
            tableWidget->setItem(0, 4, new QTableWidgetItem(etat));
            tableWidget->setItem(0, 5, new QTableWidgetItem(vaccination));
            tableWidget->setItem(0, 6, new QTableWidgetItem(tempsVaccination));  // Ajoutez la colonne "Temps de vaccination"

            tableWidget->show();
        }
  else  if (categorie == "ane") {
      float coefficient_taille_ane = 8.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_ane = 0.3;

      // Calcul du score pour un âne
      float score_ane = (coefficient_taille_ane * taille) + (coefficient_masse_ane * masse);

      QString etat_ane = (score_ane >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_ane);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();


      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_ane));

      tableWidget->show();
  }
 else if (categorie == "mouton") {
      float coefficient_taille_mouton = 5.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_mouton = 0.5;

      // Calcul du score pour les moutons
      float score_mouton = (coefficient_taille_mouton * taille) + (coefficient_masse_mouton * masse);

      QString etat_mouton = (score_mouton >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_mouton);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();

      // Affichage du tableau
      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_mouton));

      tableWidget->show();
  }
  else if (categorie == "cheval") {
      float coefficient_taille_cheval = 8.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_cheval = 0.4;

      // Calcul du score pour les chevaux
      float score_cheval = (coefficient_taille_cheval * taille) + (coefficient_masse_cheval * masse);

      QString etat_cheval = (score_cheval >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_cheval);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();

      // Affichage du tableau
      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_cheval));

      tableWidget->show();
  }
  else if (categorie == "Mammifères") {
      float coefficient_taille_mammiferes = 7.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_mammiferes = 0.3;

      // Calcul du score pour les mammifères
      float score_mammiferes = (coefficient_taille_mammiferes * taille) + (coefficient_masse_mammiferes * masse);

      QString etat_mammiferes = (score_mammiferes >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_mammiferes);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();

      // Affichage du tableau
      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_mammiferes));

      tableWidget->show();
  }
 else if (categorie == "chien") {
      float coefficient_taille_chien = 6.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_chien = 0.4;

      // Calcul du score pour les chiens
      float score_chien = (coefficient_taille_chien * taille) + (coefficient_masse_chien * masse);

      QString etat_chien = (score_chien >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_chien);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();

      // Affichage du tableau
      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_chien));

      tableWidget->show();
  }
  else if (categorie == "Reptiles") {
      float coefficient_taille_reptile = 12.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_reptile = 0.1;

      // Calcul du score pour les reptiles
      float score_reptile = (coefficient_taille_reptile * taille) + (coefficient_masse_reptile * masse);

      QString etat_reptile = (score_reptile >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_reptile);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();

      // Affichage du tableau
      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_reptile));

      tableWidget->show();
  }

    } else {
        // Si l'identifiant n'existe pas, affichez un message d'erreur
        QMessageBox::warning(this, "Erreur", "Identifiant non trouvé dans la table ANIMAUX.");
    }
}


