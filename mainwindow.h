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
#include"arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


      MainWindow(QWidget *parent = nullptr);


      ~MainWindow();
signals:


private slots:
      void animateTableBorderGradient();
      int count0();
      int count1();
      int count2();
      int count3();
      int count4();
      int count5();
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


    void on_pushButton_13_clicked();
    void RechercheID();


    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();
    void chargerDonneesUtilisateur();

    void on_pushButton_home_2_clicked();

    void on_pushButton_home_3_clicked();

    void on_pushButton_home_4_clicked();

    void on_pushButton_home_5_clicked();
    void on_pushButton_16_clicked();

    void on_notification_system();
    //void sendFingerprintDataToArduino(char command, int id);
    //bool initialize();
    bool modifier_presence_login(QString ,QString PRECENSE);
    void on_test_clicked();
    void closeEvent(QCloseEvent *event) override;


private:
    Ui::MainWindow *ui;
    bool icon;
    QLabel *resultLabel;
    employe e;
    int animationPosition=0;
    QPropertyAnimation *buttonAnimation;
    QByteArray data;
    Arduino A;


};
#endif // MAINWINDOW_H
