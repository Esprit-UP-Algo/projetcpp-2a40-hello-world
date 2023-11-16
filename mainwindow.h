#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QString>
#include <QMainWindow>
#include <QDateEdit>
#include "agri.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_ajouter_clicked();

    void on_button_clients_clicked();

    void on_button_machines_clicked();

    void on_button_employ_clicked();

    void on_button_animaux_clicked();

    void on_button_agri_clicked();

    void on_suppression_clicked();

    void on_modifier_clicked();

    void on_pdf_clicked();

    void on_rech_clicked();

    void showstat();


    void on_calculbenefice_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    agri a;
};
#endif // MAINWINDOW_H
