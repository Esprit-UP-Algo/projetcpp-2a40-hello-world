#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include "connection.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if (test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
        QObject::tr("Connection successful. \n Click Ok to exit."), QMessageBox::Ok);

    }

    else
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed. \n"
                                          "Click Ok to exit"), QMessageBox::Ok);

    return a.exec();

}
