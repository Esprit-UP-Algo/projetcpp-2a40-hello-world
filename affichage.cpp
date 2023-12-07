#include "affichage.h"
#include "ui_affichage.h"
affichage::affichage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affichage)
{
    ui->setupUi(this);
    MainWindow mainWindow; // Créez une instance de la fenêtre d'origine

}
QTableWidget* affichage::getTabWidget() {
    return ui->tab_affichage;
}
affichage::~affichage()
{

    delete ui;
}
