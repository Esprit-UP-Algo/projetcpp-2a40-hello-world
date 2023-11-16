#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QMap>
#include <QLabel>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include "machine.h"
namespace Ui {
class map;
}

class map :  public QDialog{
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);
    static void qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a);
    static void showMap(QWidget *parent = nullptr);

    void setupUi();
   void updateLabelFromMachine(const QString &machinePosition, const QString &machineSerie);

    ~map();

private:
    QMap<QString, QLabel*> blockLabels;
    Ui::map *ui;
};

#endif // MAP_H
