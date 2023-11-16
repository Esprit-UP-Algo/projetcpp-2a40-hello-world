#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include"connexion.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    machine m;
     //m.enregistrerHistoriqueReparationManuelle();
   Connexion c;
    bool test=c.createconnect();
    MainWindow w;
    if (test)
    {
    w.show();
    QMessageBox::information(nullptr,QObject::tr("database is open"),QObject::tr("connexion seccessuful.\n""click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),QObject::tr("connexion failed.\n""click cancel to exit."),QMessageBox::Cancel);
    return a.exec();
}

