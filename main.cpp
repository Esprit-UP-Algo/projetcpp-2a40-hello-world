#include "mainwindow.h"
#include <QApplication>
#include"connection.h"
#include<QMessageBox>
#include<QObject>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;


    w.show();

    if(test)
    {

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle(QObject::tr("Bienvenue"));
        msgBox.setText(QObject::tr("Connextion avec succès"));
        msgBox.setInformativeText(QObject::tr("Cliquez sur OK pour quitter."));

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();



    }

    else{



        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("La base de données n'est pas ouverte"), QObject::tr("Cliquez sur OK pour quitter."), QMessageBox::Ok);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();

    }



    return a.exec();


}
