#include "maintenance.h"
#include "ui_maintenance.h"
#include"machine.h"
#include <QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QSqlQueryModel>
maintenance::maintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maintenance)
{
    ui->setupUi(this);
    ui->date->setDisplayFormat("dd-MM-yyyy");

}
maintenance::maintenance()
{
    serie="";
    date=QDate::currentDate();
    cout=0.0;
}
maintenance::maintenance(QString seri,QDate date,double cout)
{

    this->serie=seri;
    this->date=date;
    this->cout=cout;
};
maintenance::~maintenance()
{
    delete ui;
}
void maintenance::setserie(QString s){serie=s;}
void maintenance::setdate(QDate d){date=d;}
void maintenance::setcout(double c){cout=c;}
QString maintenance::getserie(){return serie;}
QDate maintenance::getdate(){return date;}
double maintenance::getcout(){return cout;}

void maintenance::enregistrerEtAfficher()
{
    QString serie = ui->serie->text();
    QDate date = ui->date->date();
    bool conversionReussie;
    double cout = ui->cout->text().toDouble(&conversionReussie);

    if (!conversionReussie || cout < 0.0)
    {
        QMessageBox::warning(this, "Erreur", "Le coût doit être un nombre valide et positif.");
        return; // Sortir de la fonction en cas d'erreur
    }

    // Ajout d'une nouvelle requête SQL pour vérifier si la série existe
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM machines WHERE serie = :serie");
    query.bindValue(":serie", serie);

    if (query.exec() && query.next())
    {
        int rowCount = query.value(0).toInt();
        if (rowCount > 0)
        {
            // Si la série existe, procédez à l'enregistrement dans le fichier
            QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer le fichier texte", "", "Fichiers texte (*.txt)");

            QFile fichier(cheminFichier);
            if (fichier.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream flux(&fichier);
                flux << "Série : " << serie << "\n";
                flux << "Date : " << date.toString("dd-MM-yyyy") << "\n";
                flux << "Coût : " << cout << "\n\n";

                fichier.close();

                QMessageBox::information(this, "Enregistrement réussi", "Données enregistrées avec succès dans le fichier : " + cheminFichier);
            }
            else
            {
                QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier pour l'enregistrement de maintenance.");
            }

            show();
        }
        else
        {
            // Si la série n'existe pas, affichez un message d'erreur
            QMessageBox::warning(this, "Erreur", "La série n'existe pas dans la base de données.");
        }
    }
    else
    {
        // Gestion de l'erreur d'exécution de la requête
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête SQL.");
    }
}

void maintenance::on_save_clicked()
{
    enregistrerEtAfficher();

}

