#include "map.h"
#include "ui_map.h"

map::map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
}

map::~map()
{
    delete ui;
}
/*void map::showMap(QWidget *parent) {
    map *mapWindow = new map(parent);
    mapWindow->show();
}
void map::setupUi() {  qDebug() << "Setting up UI...";
    blockLabels["bloc1"] = findChild<QLabel*>("bloc1");
    blockLabels["bloc2"] = findChild<QLabel*>("bloc2");
    blockLabels["bloc3"] = findChild<QLabel*>("bloc3");
    blockLabels["bloc4"] = findChild<QLabel*>("bloc4");
}*/
void map::updateLabelFromMachine(const QString &machinePosition, const QString &machineSerie) {
    qDebug() << "Updating label for machine...";

    if (blockLabels.contains(machinePosition)) {
        // Récupérer le pointeur vers la QLabel associée à cette position
        QLabel *label = blockLabels.value(machinePosition);

        // Mettre à jour le texte de la QLabel avec la série de la machine
        label->setText(machineSerie);
    }
}
