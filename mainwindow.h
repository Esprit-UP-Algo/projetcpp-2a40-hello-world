#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QRegExpValidator>
#include <QMainWindow>
#include "client.h"
#include <QPushButton>
#include <QCalendarWidget>
#include <QDateTime>
#include "review.h"
#include <QLabel>
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace Ui { class Client; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_modif_clicked();
    void on_pb_ajouter_clicked();
    void on_pb_supp_clicked();
    void on_pb_afficher_clicked();
    void on_pb_tri_clicked();
    void on_pb_cherch_clicked();
    void on_pb_pdf_clicked();
    void on_pb_stat_clicked();
    void on_pb_review_clicked();
    void on_pb_rdv_clicked();
    void on_pushButton_2_clicked();
    void on_pb_rdvv_clicked();
    void on_retour_clicked();
    void on_appo_clicked();
    void on_pb_fact_clicked();
    void on_pb_factoo_clicked();
    void on_retourr_clicked();
    void processSerialData();
private:
    Ui::MainWindow *ui;
    Client C;
    bool chercher(int id);
     void openReviewWindow();
     void addToExcel(int id, const QString& produit, double prix);
     void addToCSV(int id, const QString& produit, double prix);
     void displayTableView();
     void displayStatistics();
     QSerialPort *serial;



};
#endif // MAINWINDOW_H
