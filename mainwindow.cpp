#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include "map.h"
#include "maintenance.h"
#include<QDebug>
#include<QApplication>
#include<QMessageBox>
#include <QIntValidator>
#include<QtCharts>
#include<QtSql>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->position->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->position->addItem("");
    ui->position->addItem("bloc1");
    ui->position->addItem("bloc2");
    ui->position->addItem("bloc3");
    ui->position->addItem("bloc4");

    ui->etat->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->etat->addItem("");
    ui->etat->addItem("fonctionelle");
    ui->etat->addItem("en panne");

    ui->fonction->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->fonction->addItem("");
    ui->fonction->addItem("labourage");
    ui->fonction->addItem("récolte");
     ui->fonction->addItem("fèrtilisation");
      ui->fonction->addItem("semis");
      ui->fonction->addItem("pulvérisation");

      fenetreMaintenance = nullptr;
    fenetremap=nullptr;
    currentmachine=nullptr;

    connect(ui->map, &QPushButton::clicked, this, &MainWindow::on_map_clicked);
    ui->tabm->setModel(m.afficher());
    showMachineStatistics();



     ui->q_carburant->setValidator( new QIntValidator(0,200, this));
     ui->nb_heures->setValidator(new QIntValidator(0,1000, this));
     QRegExp regex("\\d{3}tunisie\\d{4}");
     QRegExpValidator *validator = new QRegExpValidator(regex, this);
     ui->serie->setValidator(validator);

updateStatistics();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_ajouter_clicked()
{

    QString serie=ui->serie->text();
    QString etat=ui->etat->currentText();
    QString fonction=ui->fonction->currentText();
    QString position=ui->position->currentText();
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








void MainWindow::on_modifier_clicked()
{
    machine m;
    m.setserie(ui->serie->text());
       m.setetat (ui->etat->currentText());
        m.setfonction( ui->fonction->currentText());
        m.setposition ( ui->position->currentText());
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



void MainWindow::on_pushButton_3_clicked()
{
    QString nomFichierPdf = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "Fichiers PDF (*.pdf)");

        if (!nomFichierPdf.isEmpty()) {
            machine m; // Créez une instance de la classe machine
            bool exportReussi = m.exporterMachinesEnPannePdf(nomFichierPdf);

            if (exportReussi) {
                QMessageBox::information(this, "Exportation PDF réussie", "Les données des machines en panne ont été exportées en PDF.");
            } else {
                QMessageBox::critical(this, "Échec de l'exportation PDF", "L'exportation des données en PDF a échoué.");
            }
        }
}
void MainWindow::showMachineStatistics()
{
    QString sqlQuery = "SELECT serie, SUM(nombre_heure) AS heures_totales FROM machines GROUP BY serie";
    QSqlQuery query;
    query.prepare(sqlQuery);

    QBarSeries *series = new QBarSeries();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    if (query.exec()) {
        while (query.next()) {
            QString serie = query.value(0).toString();
            double heuresTotales = query.value(1).toDouble();
            QBarSet *barSet = new QBarSet(serie);
            *barSet << heuresTotales;
            series->append(barSet);
            axisX->append(serie);
        }
    } else {
        qDebug() << "Erreur d'exécution de la requête : " << query.lastError().text();
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des machines par serie");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart);

    // Ajoutez le QChartView au widget dans votre interface utilisateur (chartContainer)
    QWidget *chartContainer = ui->chartContainer; // Assurez-vous que le nom correspond à celui dans votre fichier .ui
    QVBoxLayout *layout = new QVBoxLayout(chartContainer);
    layout->addWidget(chartView);
    connect(ui->tabm->model(), &QAbstractItemModel::dataChanged, this, &MainWindow::updateStatistics);
}

void MainWindow::updateStatistics()
{
    QLayout *containerLayout = ui->chartContainer->layout();
    if (containerLayout) {
        // Attempt to find the chart or chart view in the layout
        QChart *chart = nullptr;

        // Check if the widget at index 0 is a QChartView
        if (containerLayout->count() > 0) {
            QWidget *widgetAtIndex0 = containerLayout->itemAt(0)->widget();
            QChartView *chartView = dynamic_cast<QChartView*>(widgetAtIndex0);

            if (chartView) {
                chart = chartView->chart();
            }
        }

        // If not found, check if the widget itself is a QChart
        if (!chart) {
            QChart *chartWidget = dynamic_cast<QChart*>(ui->chartContainer);
            if (chartWidget) {
                chart = chartWidget;
            }
        }

        if (chart) {
            QBarSeries *series = dynamic_cast<QBarSeries*>(chart->series().at(0));

            if (series) {
                // Rest of your update logic here
                QString sqlQuery = "SELECT serie, SUM(nombre_heure) AS heures_totales FROM machines GROUP BY serie";
                QSqlQuery query;
                query.prepare(sqlQuery);

                // Rest of your update logic here...

                qDebug() << "Chart updated successfully.";
                return;
            } else {
                qDebug() << "Series not found in the chart.";
            }
        } else {
            qDebug() << "Chart not found in the layout.";
        }
    } else {
        qDebug() << "No layout in the chartContainer.";
    }
}


void MainWindow::on_rechercher_clicked()
{
    machine m;
    m.setserie(ui->chercher->text());

    QSqlQueryModel *result = m.rechercherParSerie(m.getserie());

    if (result && result->rowCount() > 0) {
        ui->tabm->setModel(result);
        QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("Recherche effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, tr("Échec de la recherche"), tr("La recherche a échoué ou la série n'existe pas."));
    }
}

void MainWindow::on_supp_clicked()
{ QString serie=(ui->chercher->text());
    bool test=m1.supprimer(serie);
    if (test)
    {
     QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("suppression effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
     ui->tabm->setModel(m.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("suppression non effectuer.\n""click cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_pushButton_clicked()
{
    if (fenetreMaintenance)
    {
        // Assurez-vous que la fenêtre maintenance existe
        fenetreMaintenance->enregistrerEtAfficher();
        fenetreMaintenance->show();

    }
    else
    {
        // Si la fenêtre maintenance n'existe pas, créez-la et affichez-la
        fenetreMaintenance = new maintenance(this);
        fenetreMaintenance->show();
    }
}

void MainWindow::on_map_clicked()
{

    if (!fenetremap) {
            fenetremap = new map(this);
        }
        fenetremap->show();
        QString machinePosition = ui->position->currentText();
            QString machineSerie = ui->serie->text();
            fenetremap->updateLabelFromMachine(machinePosition, machineSerie);
}
