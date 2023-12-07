#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QLabel>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include "machine.h"
namespace Ui {
class map;
}

class map : public QDialog
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);
    ~map();
        static void showMap(QWidget *parent = nullptr);

        void setupUi();
       void updateLabelFromMachine(const QString &machinePosition, const QString &machineSerie);

private:
    QMap<QString, QLabel*> blockLabels;
    Ui::map *ui;
};

#endif // MAP_H
