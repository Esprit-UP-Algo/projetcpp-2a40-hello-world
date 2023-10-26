#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "dialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_id->setValidator(new QIntValidator(0,999999, this));
    ui->lineEdit_id->setPlaceholderText("000000"); //placeholder
    ui->lineEdit_nom->setPlaceholderText("Nom"); //placeholder
    ui->lineEdit_prenom->setPlaceholderText("Prenom"); //placeholder
    ui->lineEdit_mail->setPlaceholderText("foulen@gmail.com"); //placeholder
     ui->lineEdit_tel->setPlaceholderText("00 000 000"); //placeholder
     ui->lineEdit_rech->setPlaceholderText("Rechercher"); //placeholder
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Client c;
    c.setnom(ui->lineEdit_nom->text());
    c.setprenom(ui->lineEdit_prenom->text());
    c.setid(ui->lineEdit_id->text());
    c.setmail(ui->lineEdit_mail->text());
    c.setdate(ui->dateEdit->date());
    c.settel(ui->lineEdit_tel->text());
    c.setrech(ui->lineEdit_rech->text());

    Dialog d;
    d.setclient(c);
    d.exec();
}
