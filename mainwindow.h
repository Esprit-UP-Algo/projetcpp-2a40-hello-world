#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QObject>
#include <QMainWindow>
#include"machine.h"
#include"maintenance.h"
#include"map.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    static void qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a);
    ~MainWindow();

public slots:

    void on_ajouter_clicked();

    void on_clients_clicked();

    void on_machines_clicked();

    void on_employes_clicked();

    void on_animaux_clicked();

    void on_agri_clicked();



    void on_modifier_clicked();


    void on_pushButton_3_clicked();
    void showMachineStatistics();
    void updateStatistics();
    void on_rechercher_clicked();

    void on_supp_clicked();

   // void on_alerte_clicked();


private slots:
    void on_pushButton_clicked();


    void on_map_clicked();

private:
    Ui::MainWindow *ui;
    machine m;
    machine m1;
     maintenance *fenetreMaintenance;
     map *fenetremap;
     machine *currentmachine;
};
#endif // MAINWINDOW_H
