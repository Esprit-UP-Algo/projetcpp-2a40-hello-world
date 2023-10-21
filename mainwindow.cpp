#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsDropShadowEffect>
#include<QStackedWidget>
#include<login.h>
#include <QApplication>
#include <QLineEdit>
#include <QWidget>
#include <QPropertyAnimation>
#include <QPalette>
#include <employe.h>
#include<QMessageBox>
#include<QObject>
#include<QIntValidator>
#include<employe.h>
#include<QSqlTableModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //GROUPEBOX_1
    ui->setupUi(this);
    //ui->lineEdit->setPlaceholderText("Utilisateur");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit_3->setClearButtonEnabled(true);
    ui->lineEdit_3->setPlaceholderText("Rechercher");
    QIcon user("/Users/LENOVO/test/profile.png");
    QIcon pass("/Users/LENOVO/test/pass.png");
    ui->lineEdit->addAction(user,QLineEdit::LeadingPosition);
    ui->lineEdit_2->addAction(pass,QLineEdit::LeadingPosition);
    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0,0,0,100));
    shadow->setOffset(5,5);
    ui->label_2->setGraphicsEffect(shadow);
    QGraphicsDropShadowEffect *shadow3=new QGraphicsDropShadowEffect;
    shadow3->setBlurRadius(10);
    shadow3->setColor(QColor(0,0,0,100));
    shadow3->setOffset(5,5);
    ui->pushButton_3->setGraphicsEffect(shadow3);
    QGraphicsDropShadowEffect *shadow4=new QGraphicsDropShadowEffect;
    shadow4->setBlurRadius(10);
    shadow4->setColor(QColor(0,0,0,100));
    shadow4->setOffset(5,5);
    ui->lineEdit_2->setGraphicsEffect(shadow4);
    QGraphicsDropShadowEffect *shadow5=new QGraphicsDropShadowEffect;
    shadow5->setBlurRadius(10);
    shadow5->setColor(QColor(0,0,0,100));
    shadow5->setOffset(5,5);
    ui->lineEdit->setGraphicsEffect(shadow5);
    QGraphicsDropShadowEffect *shadow6=new QGraphicsDropShadowEffect;
    shadow6->setBlurRadius(10);
    shadow6->setColor(QColor(0,0,0,100));
    shadow6->setOffset(5,5);
    ui->label_6->setGraphicsEffect(shadow6);
    QGraphicsDropShadowEffect *shadow7=new QGraphicsDropShadowEffect;
    shadow7->setBlurRadius(10);
    shadow7->setColor(QColor(0,0,0,100));
    shadow7->setOffset(5,5);
    ui->label->setGraphicsEffect(shadow7);
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    //GROUPEBOX_2
    QIcon rech("/Users/LENOVO/test/—Pngtree—vector search icon_3783210");
    ui->lineEdit_3->addAction(rech,QLineEdit::LeadingPosition);
    //ui->lineEdit_3->addAction(rech,QLineEdit::TrailingPosition);
    ui->lineEdit_id->setPlaceholderText("Votre Identifiant");
    ui->lineEdit_nom->setPlaceholderText("Votre Nom");
    ui->lineEdit_prenom->setPlaceholderText("Votre Prenom");
    ui->lineEdit_id->setClearButtonEnabled(true);
    ui->lineEdit_nom->setClearButtonEnabled(true);
    ui->lineEdit_prenom->setClearButtonEnabled(true);
    /*
    QGraphicsDropShadowEffect *shadow21=new QGraphicsDropShadowEffect;
    shadow21->setBlurRadius(10);
    shadow21->setColor(QColor(0,0,0,100));
    shadow21->setOffset(5,5);
    ui->pushButton_agriculture->setGraphicsEffect(shadow21);
    QGraphicsDropShadowEffect *shadow2=new QGraphicsDropShadowEffect;
    shadow2->setBlurRadius(10);
    shadow2->setColor(QColor(0,0,0,100));
    shadow2->setOffset(5,5);
    ui->pushButton_client->setGraphicsEffect(shadow2);
    QGraphicsDropShadowEffect *shadow20=new QGraphicsDropShadowEffect;
    shadow20->setBlurRadius(10);
    shadow20->setColor(QColor(0,0,0,100));
    shadow20->setOffset(5,5);
    ui->pushButton_animaux->setGraphicsEffect(shadow20);

    QGraphicsDropShadowEffect *shadow19=new QGraphicsDropShadowEffect;
    shadow19->setBlurRadius(10);
    shadow19->setColor(QColor(0,0,0,100));
    shadow19->setOffset(5,5);
    ui->pushButton_employes->setGraphicsEffect(shadow19);
    QGraphicsDropShadowEffect *shadow22=new QGraphicsDropShadowEffect;
    shadow22->setBlurRadius(10);
    shadow22->setColor(QColor(0,0,0,100));
    shadow22->setOffset(5,5);
    ui->pushButton_machines->setGraphicsEffect(shadow22);
    */
    ui->label_15->hide();
    ui->tableView->setModel(e.afficher());
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { color: white; background-color: #BB5D57; border-style: solid;border-radius: 10;padding: 1px;font-size: 17px;padding-left: 10px;padding-right: 10px;font-weight: bold;font-size: 12px;color: #FFFFF;font-family: Tahoma; }");
    ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section { color:transparent; background-color:transparent; border-style: solid;padding: 1px;font-size: 10px;padding-right: 10px;font-weight: bold;font-size: 12px;color:transparent;font-family: Tahoma;padding-bottom:1px; }");


    //GROUPBOX_3
    QGraphicsDropShadowEffect *shadow1=new QGraphicsDropShadowEffect;
    shadow1->setBlurRadius(10);
    shadow1->setColor(QColor(0,0,0,100));
    shadow1->setOffset(5,5);
    ui->label_17->setGraphicsEffect(shadow1);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    QGraphicsDropShadowEffect *shadow8=new QGraphicsDropShadowEffect;
    shadow8->setBlurRadius(10);
    shadow8->setColor(QColor(0,0,0,100));
    shadow8->setOffset(5,5);
    ui->label_16->setGraphicsEffect(shadow8);
    QGraphicsDropShadowEffect *shadow9=new QGraphicsDropShadowEffect;
    shadow9->setBlurRadius(10);
    shadow9->setColor(QColor(0,0,0,100));
    shadow9->setOffset(5,5);
    ui->lineEdit_4->setGraphicsEffect(shadow9);
    QGraphicsDropShadowEffect *shadow10=new QGraphicsDropShadowEffect;
    shadow10->setBlurRadius(10);
    shadow10->setColor(QColor(0,0,0,100));
    shadow10->setOffset(5,5);
    ui->lineEdit_5->setGraphicsEffect(shadow10);
    QGraphicsDropShadowEffect *shadow11=new QGraphicsDropShadowEffect;
    shadow11->setBlurRadius(10);
    shadow11->setColor(QColor(0,0,0,100));
    shadow11->setOffset(5,5);
    ui->lineEdit_6->setGraphicsEffect(shadow11);
    QGraphicsDropShadowEffect *shadow12=new QGraphicsDropShadowEffect;
    shadow12->setBlurRadius(10);
    shadow12->setColor(QColor(0,0,0,100));
    shadow12->setOffset(5,5);
    ui->lineEdit_7->setGraphicsEffect(shadow12);
    QGraphicsDropShadowEffect *shadow13=new QGraphicsDropShadowEffect;
    shadow13->setBlurRadius(10);
    shadow13->setColor(QColor(0,0,0,100));
    shadow13->setOffset(5,5);
    ui->pushButton_6->setGraphicsEffect(shadow13);
    ui->lineEdit_4->setClearButtonEnabled(true);
    ui->lineEdit_5->setClearButtonEnabled(true);
    ui->lineEdit_6->setClearButtonEnabled(true);
    ui->lineEdit_7->setClearButtonEnabled(true);

    //GROUPEBOX_4

    QGraphicsDropShadowEffect *shadow14=new QGraphicsDropShadowEffect;
    shadow14->setBlurRadius(10);
    shadow14->setColor(QColor(0,0,0,100));
    shadow14->setOffset(5,5);
    ui->pushButton_7->setGraphicsEffect(shadow14);
    QGraphicsDropShadowEffect *shadow15=new QGraphicsDropShadowEffect;
    shadow15->setBlurRadius(10);
    shadow15->setColor(QColor(0,0,0,100));
    shadow15->setOffset(5,5);
    ui->pushButton_8->setGraphicsEffect(shadow15);
    QGraphicsDropShadowEffect *shadow16=new QGraphicsDropShadowEffect;
    shadow16->setBlurRadius(10);
    shadow16->setColor(QColor(0,0,0,100));
    shadow16->setOffset(5,5);
    ui->pushButton_9->setGraphicsEffect(shadow16);
    QGraphicsDropShadowEffect *shadow17=new QGraphicsDropShadowEffect;
    shadow17->setBlurRadius(10);
    shadow17->setColor(QColor(0,0,0,100));
    shadow17->setOffset(5,5);
    ui->pushButton_10->setGraphicsEffect(shadow17);
    QGraphicsDropShadowEffect *shadow18=new QGraphicsDropShadowEffect;
    shadow18->setBlurRadius(10);
    shadow18->setColor(QColor(0,0,0,100));
    shadow18->setOffset(5,5);
    ui->pushButton_11->setGraphicsEffect(shadow18);




}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::animateLineEdit() {
    ui->lineEdit->setStyleSheet("QLineEdit { background-color:grey; border-color:blue;padding: 1px;border: 2px solid;border-radius: 8px; ; }");
    ui->lineEdit_2->setStyleSheet("QLineEdit { background-color: white; border-color:blue;padding: 1px;border: 2px solid;border-radius: 8px; ; }");

}
void MainWindow::animateLineEdit2() {
    ui->lineEdit_2->setStyleSheet("QLineEdit { background-color: grey; border-color:blue;padding: 1px;border: 2px solid;border-radius: 8px; ; }");
    ui->lineEdit->setStyleSheet("QLineEdit { background-color: white; border-color:blue;padding: 1px;border: 2px solid;border-radius: 8px; ; }");
}

void MainWindow::on_pushButton_clicked()
{   MainWindow m;
    if (icon==false)
    {
    icon=true;
    ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    QPixmap image("/Users/LENOVO/test/i1.png");
    ui->label_open->setPixmap(image);
    ui->label_6->clear();


    }

    else
    {   icon=false;
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        QPixmap image("/Users/LENOVO/test/I2.png");
        ui->label_6->setPixmap(image);
        ui->label_open->clear();

    }
}



void MainWindow::on_pushButton_3_clicked()
{

    ui->groupBox_4->show();
    ui->groupBox->hide();

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->groupBox_3->show();
    ui->groupBox->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString id=ui->lineEdit_id->text();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    QDate date=ui->dateEdit->date();
    QSpinBox *nb=ui->spinBox;
    employe e(id,nom,prenom,salaire,date,nb);
    bool test=e.ajouter();
    if(test)
    {QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout avec succes \n"
                                                                    "click cancel to exit"),QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr,QObject::tr("nope"),QObject::tr("ajout non succes \n"
                                                                    "click cancel to exit"),QMessageBox::Cancel);}
    ui->label_15->show();

}

void MainWindow::on_pushButton_client_clicked()
{
    ui->pushButton_client->setStyleSheet("QPushButton { background-color:#84B7A4;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_machines->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_employes->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_animaux->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_agriculture->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");

}

void MainWindow::on_pushButton_machines_clicked()
{
    ui->pushButton_machines->setStyleSheet("QPushButton { background-color:#7DB5A2 ;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_client->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_employes->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_animaux->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_agriculture->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");

}

void MainWindow::on_pushButton_employes_clicked()
{
    ui->pushButton_employes->setStyleSheet("QPushButton { background-color:#73B19B ;border: 1px white;border-radius: 10px;border-bottom-color:transparent;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_client->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_machines->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_animaux->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_agriculture->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");

}

void MainWindow::on_pushButton_animaux_clicked()
{
    ui->pushButton_animaux->setStyleSheet("QPushButton { background-color:#6aac95 ;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_client->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_machines->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_employes->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_agriculture->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_pushButton_agriculture_clicked()
{
    ui->pushButton_agriculture->setStyleSheet("QPushButton { background-color:#84B7A4 ;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_client->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_machines->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_animaux->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->pushButton_employes->setStyleSheet(" border-radius: 10px; font: 20pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->groupBox_3->hide();
    ui->groupBox->show();
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->groupBox_4->hide();
    ui->groupBox_2->show();

    ui->label_32->hide();
    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.39);
    QPieSlice *slice= series->append("Femme 40%",40);
    //slice->setExploded();
    slice->setLabelVisible();
    QPieSlice *slice1= series->append("Homme 60%",60);
    //slice1->setExploded();
    slice1->setLabelVisible();
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //chart->setTitle("Statistique entre l homme et la femme");
    chart->setTheme(QChart::ChartThemeQt);
    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->label_32->size());
    chartview->setParent(ui->label_32);
    ui->label_32->show();
    ui->pushButton_employes->setStyleSheet("QPushButton { background-color:#84B7A4;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");



}

void MainWindow::on_pushButton_home_clicked()
{
    ui->groupBox_2->hide();
    ui->groupBox_4->show();
}



void MainWindow::on_pushButton_4_clicked()
{
    employe e;
    bool test;
    e.setid(ui->lineEdit_id_2->text());
    test=e.supprimer(e.get_id());
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("l employe est supprimé \n"
                                                                        "click cancel to exit"),QMessageBox::Cancel);}

        else
        {
        QMessageBox::critical(nullptr,QObject::tr("nope"),QObject::tr("l employe n est pas supprimé \n"
                                                                        "click cancel to exit"),QMessageBox::Cancel);}


}


void MainWindow::on_pushButton_12_clicked()
{

       ui->tableView->setModel(e.afficher());

}
