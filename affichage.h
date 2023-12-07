#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include"zone.h"
#include <QDialog>
#include <QLineEdit>
#include "mainwindow.h"
#include <QTableWidget>
namespace Ui {
class affichage;
}

class affichage : public QDialog
{
    Q_OBJECT

public:
    explicit affichage(QWidget *parent = nullptr);
    ~affichage();
public:
 QTableWidget* getTabWidget();
private:
    Ui::affichage *ui;
    Zone z;
};

#endif // AFFICHAGE_H
