#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_clients_clicked();

    void on_machines_clicked();

    void on_employes_clicked();

    void on_animaux_clicked();

    void on_agri_clicked();

    void on_home_toggled(bool checked);

    void on_home_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
