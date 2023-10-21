#include "mainwindow.h"
#include <QApplication>
#include<connection.h>
#include<QMessageBox>
#include<QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {
    w.show();
    QMessageBox::information(nullptr,QObject::tr("data base is open"),QObject::tr("connexion avec succes \n"
                                                                                  "click cancal to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("data base is not open"),QObject::tr("connection failed\n"
                                                                                       "click cancel to exit"),QMessageBox::Cancel);
    return a.exec();
}
