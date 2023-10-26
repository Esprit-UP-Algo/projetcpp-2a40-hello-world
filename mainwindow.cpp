#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agri.h"
#include "affiche.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    agri a;
    a.settype(ui->type->text());
    a.settdp(ui->pesticide->text());
    QString p=ui->prix_vente->text();
    QString p1=ui->prix_achat->text();
    QString p2=ui->quantite->text();
    bool ok;
    float pfloat=p.toFloat(&ok);
    float pfloat1=p1.toFloat(&ok);
    int pint=p2.toInt(&ok);
    if(ok)
    {
        a.setpdv(pfloat);
        a.setpda(pfloat1);
        a.setquantite(pint);
    }
    QString datetext = ui->date->text();
    QDate date = QDate::fromString(datetext, "dd/mm/yyyy");
    if(date.isValid())
        a.setdate(date);
    affiche f;
    f.setagri(a);
    f.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->button_agri->setStyleSheet(
}
