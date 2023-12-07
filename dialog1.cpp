#include "dialog1.h"
#include "ui_dialog1.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_pushButton_valider_clicked()
{
    // Obtenez la date actuelle
    QDate currentDate = QDate::currentDate();

    // Ajoutez un jour à la date actuelle
    QDate newDate = currentDate.addDays(1);
    QDate newDate1 = currentDate.addDays(30);

    // Récupérez l'identifiant depuis l'interface utilisateur
    int identifiant = ui->lineEdit_id->text().toInt();

    // Mettez à jour la base de données avec la première date
    QSqlQuery queryUpdate1;
    queryUpdate1.prepare("UPDATE ANNIMAUX SET DATE_1=:DATE_1 WHERE VACCINATION=:identifiant");
    queryUpdate1.bindValue(":DATE_1", newDate);
    queryUpdate1.bindValue(":identifiant", "non");

    if (!queryUpdate1.exec()) {
        qDebug() << "Erreur de mise à jour 1:";
        return;
    }

    // Mettez à jour la base de données avec la deuxième date
    QSqlQuery queryUpdate2;
    queryUpdate2.prepare("UPDATE ANNIMAUX SET DATE_2=:DATE_2 WHERE VACCINATION=:identifiant");
    queryUpdate2.bindValue(":DATE_2", newDate1);
    queryUpdate2.bindValue(":identifiant", "non");

    if (!queryUpdate2.exec()) {
        qDebug() << "Erreur de mise à jour 2:" ;
        return;
    }

    // Sélectionnez les données mises à jour
    QSqlQuery querySelect;
    querySelect.prepare("SELECT * FROM ANNIMAUX WHERE IDENTIFIANT = :identifiant");
    querySelect.bindValue(":identifiant", identifiant);

    if (querySelect.exec() && querySelect.next()) {
        // Affichage du tableau
        QTableWidget *tableWidget = new QTableWidget(1, 9, this);
        tableWidget->resize(800, 600);
        tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État" << "IDA"<<"VACCINATION"<<"DATE_1"<<"DATE_2");

        // Remplissez le tableau avec les données sélectionnées
        tableWidget->setItem(0, 0, new QTableWidgetItem(querySelect.value("IDENTIFIANT").toString()));
        tableWidget->setItem(0, 1, new QTableWidgetItem(querySelect.value("CATEGORIE").toString()));
        tableWidget->setItem(0, 2, new QTableWidgetItem(querySelect.value("MASSE").toString()));
        tableWidget->setItem(0, 3, new QTableWidgetItem(querySelect.value("TAILLE").toString()));
        tableWidget->setItem(0, 4, new QTableWidgetItem(querySelect.value("ETAT").toString()));
        tableWidget->setItem(0, 5, new QTableWidgetItem(querySelect.value("IDA").toString()));
        tableWidget->setItem(0, 6, new QTableWidgetItem(querySelect.value("VACCINATION").toString()));

        // Utilisez toString avec le format "yyyy-MM-dd" pour afficher seulement la date
        QString formattedDate = querySelect.value("DATE_1").toDate().toString("yyyy-MM-dd");

        tableWidget->setItem(0, 7, new QTableWidgetItem(formattedDate));
        tableWidget->setItem(0, 8, new QTableWidgetItem(querySelect.value("DATE_2").toDate().toString("yyyy-MM-dd")));

        tableWidget->show();
    }
}
