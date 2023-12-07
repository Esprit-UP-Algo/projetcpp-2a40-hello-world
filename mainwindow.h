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
#include"animaux.h"
#include"agri.h"
#include"machine.h"
#include"client.h"
#include"map.h"
#include"maintenance.h"
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


    void on_pushButton_31_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_30_clicked();
    void RechercheID1();

    void on_pushButton_32_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();
    void on_rech_clicked();
    void showstat();


    void on_pushButton_41_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_20_clicked();
    void updateStatistics();
    void RechercheID2();
    void showMachineStatistics();
    void on_pushButton_39_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_27_clicked();
    void RechercheID4();

    void on_pushButton_29_clicked();

    void on_pushButton_21_clicked();

   // void on_pushButton_22_clicked();

   // void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_26_clicked();

    void on_pb_rdvv_clicked();
    bool chercher(int id);




    void on_pushButton_49_clicked();
    void addToCSV(int id, const QString& produit, double prix); //teb3a metier2


    void on_pb_fact_clicked();



    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();


    void on_pushButton_51_clicked();

    void on_map_clicked();

    void on_pushButton_50_clicked();

    void on_label_28_linkActivated(const QString &link);

    //void on_pb_rechhhh_clicked();

private:
    Ui::MainWindow *ui;
    bool icon;
    QLabel *resultLabel;
    employe e;
    int animationPosition=0;
    QPropertyAnimation *buttonAnimation;
    QByteArray data;
    Arduino A;
    animaux a;
    agri ag;
    machine m;
    Client C;
    map *fenetremap;
    maintenance *fenetreMaintenance;
    machine *currentmachine;






};
#endif // MAINWINDOW_H
