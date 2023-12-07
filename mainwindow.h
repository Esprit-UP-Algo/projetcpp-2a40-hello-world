#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"animaux.h"
#include"arduino.h"
#include <QMainWindow>
#include<QTableWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void on_pushButton_valider_clicked();



    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_refresh_clicked();
    void on_pb_recherche_ich_clicked();

    void on_pushButton_stat_ich_clicked();


    void on_pushButton_trierid_ich_clicked();

    void on_pushButton_triernom_ich_clicked();

    void on_pushButton_triernom_ich_2_clicked();




    void on_pb_valider_pdf_clicked();

    void on_pushButton_annuler_ich_clicked();


    void on_pushButton_modifier_2_clicked();

    void on_pushButton_modifier_3_clicked();

    void on_pushButton_stat_ich_2_clicked();
    void update_label();

private:
    Ui::MainWindow *ui;
   animaux A;
   Arduino AA;
   QByteArray data;
};

#endif // MAINWINDOW_H
