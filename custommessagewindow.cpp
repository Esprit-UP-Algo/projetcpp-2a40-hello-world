#include "custommessagewindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QCheckBox>

CustomMessageWindow::CustomMessageWindow(QWidget *parent)
    : QMainWindow(parent), currentSeason("Été"), currentType("Ouverte") {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Ajouter un label pour afficher "Hello World"
    QLabel *label = new QLabel("Hello World", this);
    layout->addWidget(label);

    // Ajouter un QTableWidget personnalisé
    QTableWidget *tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4);  // 4 colonnes : Identifiant, Zones, Ouverte (case à cocher), Fermée (case à cocher)

    // Remplir les en-têtes de colonne
    QStringList headerLabels;
    headerLabels << "Identifiant" << "Zones" << "Ouverte" << "Fermée";
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    // Ajuster la taille de la fenêtre
    resize(600, 400);

    layout->addWidget(tableWidget);

    // Mettre à jour le tableau avec les données de la table SQL
    updateTableDataFromSQL(tableWidget);
}

void CustomMessageWindow::updateTableDataFromSQL(QTableWidget *tableWidget) {
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM ZONES");

    // Ajouter la vérification des erreurs SQL
    if (model->lastError().isValid()) {
        qDebug() << "SQL error:" << model->lastError().text();
        return;
    }

    // Remplir le tableau avec les données de la table SQL
    tableWidget->setRowCount(model->rowCount());
    for (int row = 0; row < model->rowCount(); ++row) {
        // Récupérer les données de la ligne courante
        QString zoneId = model->data(model->index(row, model->record().indexOf("IDENTIFIANT"))).toString();
        QString zoneName = model->data(model->index(row, model->record().indexOf("NOM"))).toString();
        QString zoneType = model->data(model->index(row, model->record().indexOf("TYPE"))).toString();

        // Créer les cases à cocher en fonction du type de zone
        QCheckBox *checkBoxOpen = new QCheckBox();
        QCheckBox *checkBoxClosed = new QCheckBox();

        checkBoxOpen->setCheckState((zoneType != "Zone touristique") ? Qt::Checked : Qt::Unchecked);
        checkBoxClosed->setCheckState((zoneType == "Zone touristique") ? Qt::Checked : Qt::Unchecked);

        // Rendre les cases à cocher non modifiables
        checkBoxOpen->setDisabled(true);
        checkBoxClosed->setDisabled(true);

        // Ajouter les cases à cocher à la cellule appropriée
        tableWidget->setCellWidget(row, 2, checkBoxOpen);
        tableWidget->setCellWidget(row, 3, checkBoxClosed);

        // Remplir la ligne du tableau avec les données
        QTableWidgetItem *idItem = new QTableWidgetItem(zoneId);
        QTableWidgetItem *zonesItem = new QTableWidgetItem(zoneName);
        tableWidget->setItem(row, 0, idItem);
        tableWidget->setItem(row, 1, zonesItem);
    }

    // Ajuster la hauteur des lignes en fonction du contenu
    tableWidget->resizeRowsToContents();
}
