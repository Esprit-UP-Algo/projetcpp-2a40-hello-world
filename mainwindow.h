#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QList>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include<employe.h>
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
    void on_pushButton_clicked();
    void animateLineEdit();
    void animateLineEdit2();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_client_clicked();

    void on_pushButton_machines_clicked();

    void on_pushButton_employes_clicked();

    void on_pushButton_animaux_clicked();

    void on_pushButton_agriculture_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_home_clicked();




    void on_pushButton_4_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    bool icon;
    QLabel *resultLabel;
    employe e;
};
#endif // MAINWINDOW_H
