#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsDropShadowEffect>
#include<QStackedWidget>
#include"login.h"
#include <QApplication>
#include <QLineEdit>
#include <QWidget>
#include <QPropertyAnimation>
#include <QPalette>
#include "employe.h"
#include<QMessageBox>
#include<QObject>
#include<QIntValidator>
#include<employe.h>
#include<QSqlTableModel>
#include <iostream>
#include <QTableView>
#include <QLinearGradient>
#include <QBrush>
#include<QAbstractTableModel>
#include <cstdlib>
#include <QPrinter>
#include <QTextDocument>
#include<iostream>
#include<QChar>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include"arduino.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //ARDUINO
    int ret=A.connect_arduino();
        switch(ret)
        {
        case (0):qDebug()<<"arduino is avilble and connected to :"<<A.getarduino_port_name();
            break;
        case (1):qDebug()<<"arduino is avilble but not connected to :"<<A.getarduino_port_name();
            break;
        case (-1):qDebug()<<"arduino is not avilble ";
        }

        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_test_clicked()));
    on_notification_system();
    //GROUPEBOX_1
    //ui->lineEdit->setPlaceholderText("Utilisateur");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit_3->setClearButtonEnabled(true);
    ui->lineEdit_3->setPlaceholderText("Rechercher");
    QIcon user("/Users/LENOVO/employe/profile.png");
    QIcon pass("/Users/LENOVO/employe/pass.png");
    ui->lineEdit->addAction(user,QLineEdit::LeadingPosition);
    ui->lineEdit_5->addAction(user,QLineEdit::LeadingPosition);
    ui->lineEdit_2->addAction(pass,QLineEdit::LeadingPosition);
    ui->lineEdit_4->addAction(pass,QLineEdit::LeadingPosition);
    ui->lineEdit_6->addAction(pass,QLineEdit::LeadingPosition);
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
     ui->label_28->hide();
     ui->label_28->setStyleSheet("QLabel { background:#73B19B;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI; }");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QIntValidator *intValidator = new QIntValidator();
    ui->lineEdit_id->setValidator(intValidator);
    ui->lineEdit_salaire->setValidator(intValidator);
    ui->lineEdit_nbx->setValidator(intValidator);
    QRegExp regex("[A-Z]+", Qt::CaseInsensitive);
    QRegExpValidator* validator = new QRegExpValidator(regex, this);
    ui->lineEdit_nom->setValidator(validator);
    ui->lineEdit_prenom->setValidator(validator);
    QIcon rech("/Users/LENOVO/employe/—Pngtree—vector search icon_3783210");
    ui->lineEdit_3->addAction(rech,QLineEdit::LeadingPosition);
    ui->lineEdit_8->addAction(rech,QLineEdit::LeadingPosition);
    ui->lineEdit_9->addAction(rech,QLineEdit::LeadingPosition);
    ui->lineEdit_10->addAction(rech,QLineEdit::LeadingPosition);
    ui->lineEdit_11->addAction(rech,QLineEdit::LeadingPosition);
    ui->lineEdit_8->setClearButtonEnabled(true);
    ui->lineEdit_9->setClearButtonEnabled(true);
    ui->lineEdit_10->setClearButtonEnabled(true);
    ui->lineEdit_11->setClearButtonEnabled(true);
    ui->lineEdit_id->setPlaceholderText("Votre Identifiant");
    ui->lineEdit_nom->setPlaceholderText("Votre Nom");
    ui->lineEdit_prenom->setPlaceholderText("Votre Prenom");
    ui->lineEdit_id->setClearButtonEnabled(true);
    ui->lineEdit_nom->setClearButtonEnabled(true);
    ui->lineEdit_prenom->setClearButtonEnabled(true);
    ui->lineEdit_salaire->setClearButtonEnabled(true);
    ui->lineEdit_nbx->setClearButtonEnabled(true);
    connect(ui->lineEdit_3, &QLineEdit::returnPressed, this, &MainWindow::chargerDonneesUtilisateur);

    QTimer *animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::animateTableBorderGradient);
    animationTimer->start(60);

    QGraphicsDropShadowEffect *shadow40=new QGraphicsDropShadowEffect;
    shadow40->setBlurRadius(10);
    shadow40->setColor(QColor(0,0,0,100));
    shadow40->setOffset(5,5);
    ui->lineEdit_3->setGraphicsEffect(shadow40);
    QGraphicsDropShadowEffect *shadow41=new QGraphicsDropShadowEffect;
    shadow41->setBlurRadius(10);
    shadow41->setColor(QColor(0,0,0,100));
    shadow41->setOffset(5,5);
    ui->pushButton_14->setGraphicsEffect(shadow41);
    QGraphicsDropShadowEffect *shadow43=new QGraphicsDropShadowEffect;
    shadow43->setBlurRadius(10);
    shadow43->setColor(QColor(0,0,0,100));
    shadow43->setOffset(5,5);
    ui->label_31->setGraphicsEffect(shadow43);
    QGraphicsDropShadowEffect *shadow23=new QGraphicsDropShadowEffect;
    shadow23->setBlurRadius(10);
    shadow23->setColor(QColor(187,93,87,100));
    shadow23->setOffset(5,5);
    ui->label_20->setGraphicsEffect(shadow23);
    ui->tableView->setModel(e.afficher());
    ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section { color:transparent; background-color:transparent; }");
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::RechercheID);
    QGraphicsDropShadowEffect *shadow24=new QGraphicsDropShadowEffect;
    shadow24->setBlurRadius(10);
    shadow24->setColor(QColor(255,255,255,80));
    shadow24->setOffset(5,5);
    ui->tableView->setGraphicsEffect(shadow24);
    QGraphicsDropShadowEffect *shadow25=new QGraphicsDropShadowEffect;
    shadow25->setBlurRadius(10);
    shadow25->setColor(QColor(0,0,0,80));
    shadow25->setOffset(5,5);
    ui->label_32->setGraphicsEffect(shadow25);
    QGraphicsDropShadowEffect *shadow26=new QGraphicsDropShadowEffect;
    shadow26->setBlurRadius(10);
    shadow26->setColor(QColor(187,93,87,100));
    shadow26->setOffset(5,5);
    ui->pushButton_2->setGraphicsEffect(shadow26);
    QGraphicsDropShadowEffect *shadow27=new QGraphicsDropShadowEffect;
    shadow27->setBlurRadius(10);
    shadow27->setColor(QColor(187,93,87,100));
    shadow27->setOffset(5,5);
    ui->pushButton_4->setGraphicsEffect(shadow27);
    QGraphicsDropShadowEffect *shadow28=new QGraphicsDropShadowEffect;
    shadow28->setBlurRadius(10);
    shadow28->setColor(QColor(187,93,87,100));
    shadow28->setOffset(5,5);
    ui->pushButton_13->setGraphicsEffect(shadow28);
    QGraphicsDropShadowEffect *shadow29=new QGraphicsDropShadowEffect;
    shadow29->setBlurRadius(10);
    shadow29->setColor(QColor(0,0,0,60));
    shadow29->setOffset(5,5);
    ui->lineEdit_id->setGraphicsEffect(shadow29);
    QGraphicsDropShadowEffect *shadow30=new QGraphicsDropShadowEffect;
    shadow30->setBlurRadius(10);
    shadow30->setColor(QColor(0,0,0,60));
    shadow30->setOffset(5,5);
    ui->lineEdit_nom->setGraphicsEffect(shadow30);
    QGraphicsDropShadowEffect *shadow31=new QGraphicsDropShadowEffect;
    shadow31->setBlurRadius(10);
    shadow31->setColor(QColor(0,0,0,60));
    shadow31->setOffset(5,5);
    ui->lineEdit_prenom->setGraphicsEffect(shadow31);
    QGraphicsDropShadowEffect *shadow32=new QGraphicsDropShadowEffect;
    shadow32->setBlurRadius(10);
    shadow32->setColor(QColor(0,0,0,60));
    shadow32->setOffset(5,5);
    ui->lineEdit_salaire->setGraphicsEffect(shadow32);
    QGraphicsDropShadowEffect *shadow33=new QGraphicsDropShadowEffect;
    shadow33->setBlurRadius(10);
    shadow33->setColor(QColor(0,0,0,60));
    shadow33->setOffset(5,5);
    ui->dateEdit->setGraphicsEffect(shadow33);
    QGraphicsDropShadowEffect *shadow34=new QGraphicsDropShadowEffect;
    shadow34->setBlurRadius(10);
    shadow34->setColor(QColor(0,0,0,60));
    shadow34->setOffset(5,5);
    ui->lineEdit_nbx->setGraphicsEffect(shadow34);
    QGraphicsDropShadowEffect *shadow35=new QGraphicsDropShadowEffect;
    shadow35->setBlurRadius(10);
    shadow35->setColor(QColor(0,0,0,60));
    shadow35->setOffset(5,5);
    ui->pushButton_12->setGraphicsEffect(shadow35);
    QGraphicsDropShadowEffect *shadow36=new QGraphicsDropShadowEffect;
    shadow36->setBlurRadius(10);
    shadow36->setColor(QColor(0,0,0,80));
    shadow36->setOffset(5,5);
    ui->label_29->setGraphicsEffect(shadow36);
    QGraphicsDropShadowEffect *shadow50=new QGraphicsDropShadowEffect;
    shadow50->setBlurRadius(10);
    shadow50->setColor(QColor(0,0,0,80));
    shadow50->setOffset(5,5);
    ui->label_40->setGraphicsEffect(shadow50);
    QGraphicsDropShadowEffect *shadow44=new QGraphicsDropShadowEffect;
    shadow44->setBlurRadius(10);
    shadow44->setColor(QColor(187,93,87,100));
    shadow44->setOffset(5,5);
    ui->label_5->setGraphicsEffect(shadow44);
    QDate date = QDate::currentDate();
    QString date1 =date.toString("dd/MM/yyyy");
    int jour= date.day();
    if(jour==1)
    ui->label_5->setText("Aujourd'hui on a Fête de la récolte ");
    if(jour==2)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==3)
    ui->label_5->setText("Aujourd'hui on a Visites de la ferme ");
    if(jour==4)
    ui->label_5->setText("Aujourd'hui Aucun événement ");
    if(jour==5)
    ui->label_5->setText("Aujourd'hui on a Vente de produits de la ferme  ");
    if(jour==6)
    ui->label_5->setText("Aujourd'hui Aucun événement ");
    if(jour==7)
    ui->label_5->setText("Aujourd'hui on a Cueillette de fruits ");
    if(jour==8)
    ui->label_5->setText("Aujourd'hui Aucun événement ");
    if(jour==9)
    ui->label_5->setText("Aujourd'hui on a Ferme à la table ");
    if(jour==10)
    ui->label_5->setText("Aujourd'hui Aucun événement ");
    if(jour==11)
    ui->label_5->setText("Aujourd'hui on Ateliers de jardinage ");
    if(jour==12)
    ui->label_5->setText("Aujourd'hui Aucun événement ");
    if(jour==13)
    ui->label_5->setText("Aujourd'hui on a Courses de charrettes");
    if(jour==14)
    ui->label_5->setText("Aujourd'hui Aucun événement ");
    if(jour==15)
    ui->label_5->setText("Aujourd'hui on a Spectacles d'animaux ");
    if(jour==16)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==17)
    ui->label_5->setText("Aujourd'hui on a Concours de sculptures de citrouilles ");
    if(jour==18)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==19)
    ui->label_5->setText("Aujourd'hui on a Marchés fermiers");
    if(jour==20)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==21)
    ui->label_5->setText("Aujourd'hui on a Cours d'équitation");
    if(jour==22)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==23)
    ui->label_5->setText("Aujourd'hui on a Fêtes d'anniversaire à la ferme");
    if(jour==24)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==25)
    ui->label_5->setText("Aujourd'hui on a Événements de tonte de moutons ");
    if(jour==26)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==27)
    ui->label_5->setText("Aujourd'hui on a Ferme pédagogique");
    if(jour==28)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==29)
    ui->label_5->setText("Aujourd'hui on a Festivals saisonniers");
    if(jour==30)
    ui->label_5->setText("Aujourd'hui Aucun événement");
    if(jour==31)
    ui->label_5->setText("Aujourd'hui on a Spectacles d'animaux ");


    cout << date1.toStdString() <<endl;

    QPropertyAnimation* animation = new QPropertyAnimation(ui->label_5, "geometry", this);
            animation->setDuration(16000);
            animation->setStartValue(QRect(30, 70, 1840, 60));
            animation->setEndValue(QRect(950, 70, 1700, 60));
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->setLoopCount(100);
            animation->start();



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
    QGraphicsDropShadowEffect *shadow13=new QGraphicsDropShadowEffect;
    shadow13->setBlurRadius(10);
    shadow13->setColor(QColor(0,0,0,100));
    shadow13->setOffset(5,5);
    ui->pushButton_6->setGraphicsEffect(shadow13);

    ui->lineEdit_4->setClearButtonEnabled(true);
    ui->lineEdit_5->setClearButtonEnabled(true);
    ui->lineEdit_6->setClearButtonEnabled(true);


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
    //GROUPBOX_5
    ui->groupBox_5->hide();
    //GROUPBOX_6
    ui->groupBox_6->hide();
    //GROUPBOX_7
    ui->groupBox_7->hide();
    //GROUPBOX_8
    ui->groupBox_8->hide();

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::animateTableBorderGradient() {
    QTableView *tableView = ui->tableView;

    if (tableView) {
        QString styleSheet = QString("QTableView {"
            "border-radius: 36px;"
            "border: 3px solid qlineargradient(spread:pad, x1:%1, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%), stop:1 rgba(132,183,164,90%));"
            "gridline-color: #BB5D57;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%), stop:1 rgba(132,183,164,90%));"

            "}" "QHeaderView {"
                                         "background-color: transparent;"
                                         "color:#BB5D57;"
                                         "border-radius: 1px;"
                                     "}"
                                     "QHeaderView::section {"
                                         "background-color: transparent;"
                                         "border:0.5px solid  transparent;"
                                      "border-radius:1px;"
                                    " }"
                                     "QTableView QTableCornerButton::section {"
                                         "background-color: transparent;"
                                         "border: none;"
                                     "}").arg(animationPosition);

        tableView->setStyleSheet(styleSheet);

        animationPosition = (animationPosition + 1) % 101;
    }
}

int MainWindow::count0()
{
    int s = 0;

        QSqlQuery query;
        query.prepare("SELECT COUNT(nba) FROM employe WHERE nba = 0");

        if (query.exec()) {
            if (query.next()) {
                s = query.value(0).toInt();

                std::cout << "La valeur s0 est : " << s << std::endl;
            } else {
                std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
            }
        } else {
            std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
        }

        return s;
}
int MainWindow::count1()
{   int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(nba) FROM employe WHERE nba = 1");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s1 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
}
int MainWindow::count2()
{   int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(nba) FROM employe WHERE nba = 2");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s2 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
}
int MainWindow::count3()
{   int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(nba) FROM employe WHERE nba = 3");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s3 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
}
int MainWindow::count4()
{  int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(nba) FROM employe WHERE nba = 4");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s4 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
}
int MainWindow::count5()
{  int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(nba) FROM employe WHERE nba = 5");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s5 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
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
    QPixmap image("/Users/LENOVO/employe/i1.png");
    ui->label_open->setPixmap(image);
    ui->label_6->clear();


    }

    else
    {   icon=false;
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        QPixmap image("/Users/LENOVO/employe/I2.png");
        ui->label_6->setPixmap(image);
        ui->label_open->clear();

    }
}


//LOGIN
void MainWindow::on_pushButton_3_clicked()
{   QString user, mdp;
    user=ui->lineEdit->text();
    mdp=ui->lineEdit_2->text();
    QSqlQuery query1;
    query1.prepare("SELECT COUNT(*) FROM login WHERE  utilisateur=:id or utilisateur='' ");
    query1.bindValue(":id",user);
    if (query1.exec()) {
        if (query1.next()) {
            int count = query1.value(0).toInt();
            if (count > 0) {

            } else {

                QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Utilisateur incorrect"), QObject::tr("Utilisateur incorrect\nCliquez sur OK pour quitter."), QMessageBox::Ok);
                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
                    }
        }
    }
    QSqlQuery query2;
    query2.prepare("SELECT COUNT(*) FROM login WHERE  mot_de_passe =:mdp");
    query2.bindValue(":mdp",mdp);
    if (query2.exec()) {
        if (query2.next()) {
            int count = query2.value(0).toInt();
            if (count > 0) {

            } else {

                QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Mot de passe incorrect"), QObject::tr("Mot de passe incorrect\nCliquez sur OK pour quitter."), QMessageBox::Ok);
                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
            }

        }
    }
    QSqlQuery query;
    query.prepare("SELECT utilisateur, mot_de_passe FROM login WHERE utilisateur = :user AND mot_de_passe = :mdp");
    query.bindValue(":user", user);
    query.bindValue(":mdp", mdp);
    if (user.isEmpty()) {


        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer l'utilisateur."), QMessageBox::Ok);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();


        return;
    }

    if (mdp.isEmpty()) {

        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer votre mot de passe."), QMessageBox::Ok);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";
        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        return;
    }

    if ((query.exec() && query.next()) || data=="0") {
        QString user;

        user=ui->lineEdit->text();
        QString message = QObject::tr("Bonjour ") + user.toUpper() + QObject::tr(". \nCliquez sur OK pour quitter.");
        QMessageBox msgBox(QMessageBox::Information, QObject::tr("Login avec succès"), message, QMessageBox::Ok);
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        ui->groupBox_4->show();
        ui->groupBox->hide();
    } else {

        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("nope"), QObject::tr("Login non réussi\nCliquez sur Annuler pour quitter"), QMessageBox::Cancel);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->groupBox_3->show();
    ui->groupBox->hide();
}
//AJOUTER
void MainWindow::on_pushButton_2_clicked()
{
    QString id=ui->lineEdit_id->text();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    QDate date=ui->dateEdit->date();
    int nb=ui->lineEdit_nbx->text().toInt();
    int c=0;
    int s=ui->lineEdit_salaire->text().toInt();
    int x=ui->lineEdit_nbx->text().toInt();
    QString salaireQ=ui->lineEdit_salaire->text();
    QString nbQ=ui->lineEdit_nbx->text();
    QString n=ui->lineEdit_nom->text();
    QString upper1 = n.toUpper();
    bool test1 = (n == upper1);
    QString p=ui->lineEdit_prenom->text();
    QString upper2 = p.toUpper();
    bool test2 = (p == upper2);
    employe e(id,nom,prenom,salaire,date,nb);
    if(test1==false)
    {QMessageBox msgBox(QMessageBox::Warning, QObject::tr("ERREUR"), QObject::tr("Le NOM contient que des MAJUSCULES!!!\nCliquez sur OK pour quitter."), QMessageBox::Ok);
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        c++;

    }
    if(test2==false)
    {QMessageBox msgBox(QMessageBox::Warning, QObject::tr("ERREUR"), QObject::tr("Le PRENOM contient que des MAJUSCULES!!!\nCliquez sur OK pour quitter."), QMessageBox::Ok);
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        c++;

    }
    if(s<0 || s>10000)
    {QMessageBox msgBox(QMessageBox::Warning, QObject::tr("ERREUR"), QObject::tr("Le salaire entre 0 et 10000\nCliquez sur OK pour quitter."), QMessageBox::Ok);
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        c++;

    }
    if(x<0 || x>5)
    {
        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("ERREUR"), QObject::tr("Le nombre de l année d éxperience entre 0 et 5\nCliquez sur OK pour quitter."), QMessageBox::Ok);
                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
                c++;

    }
    if (id.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer un ID."), QMessageBox::Ok);

        // Appliquer un stylesheet
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        c++;
        return;
    }
    if(nom.isEmpty())
    {
            QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer votre NOM!!."), QMessageBox::Ok);

            // Appliquer un stylesheet
            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();
            c++;
            return;
        }
    if(prenom.isEmpty())
    {
            QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer votre PRENOM!!."), QMessageBox::Ok);

            // Appliquer un stylesheet
            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();
            c++;
            return;
        }

    if(salaireQ.isEmpty())
    {
            QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer votre SALAIRE!!."), QMessageBox::Ok);

            // Appliquer un stylesheet
            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();
            c++;
            return;
        }
    if(nbQ.isEmpty())
    {
            QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Manque"), QObject::tr("S'il vous plaît entrer votre NOMBRE D ANNEES D EXPERIENCE!!."), QMessageBox::Ok);

            // Appliquer un stylesheet
            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();
            c++;
            return;
        }

    if(c==0)
    {
    bool test=e.ajouter();
    int id1=id.toInt();
    if (!e.idExists(id1)){
        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Existe déjà"), QObject::tr("L'ID que vous voulez entrer existe déjà."), QMessageBox::Ok);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();

        return;
    }
     if(test)
    {
        QMessageBox msgBox(QMessageBox::Information, QObject::tr("OK"), QObject::tr("Ajout avec succès\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();

    }

    else
    {QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Nope"), QObject::tr("Ajout non réussi\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
        }
    }
}

void MainWindow::on_pushButton_client_clicked()
{   QString user;
    user=ui->lineEdit->text();

    if(user=="admin" || user=="responsable client" )
    {
    QGraphicsDropShadowEffect *shadow50=new QGraphicsDropShadowEffect;
      shadow50->setBlurRadius(1);
      shadow50->setColor(QColor(132,183,164,100));
      shadow50->setOffset(5,0);
      ui->label_28->setGraphicsEffect(shadow50);
    ui->label_28->setStyleSheet("QLabel { background:#84B7A4;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI ; }");
    ui->label_28->show();
    QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
            animation->setDuration(1000);
             QPoint initialPosition =ui->label_28->pos();
             int initialX = initialPosition.x();
             int initialY = initialPosition.y();
            animation->setStartValue(QRect(initialX,initialY,111,51));
            animation->setEndValue(QRect(587, 15, 111, 51));
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->start();
     ui->groupBox_5->show();
     ui->groupBox_8->hide();
     ui->groupBox_7->hide();
     ui->groupBox_6->hide();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
    }


}

void MainWindow::on_pushButton_machines_clicked()
{
    QString user;
    user=ui->lineEdit->text();
    if(user=="admin" || user=="ingenieur mecanique")
    {
    QGraphicsDropShadowEffect *shadow50=new QGraphicsDropShadowEffect;
      shadow50->setBlurRadius(1);
      shadow50->setColor(QColor(125,181,162,100));
      shadow50->setOffset(5,0);
      ui->label_28->setGraphicsEffect(shadow50);
    ui->label_28->setStyleSheet("QLabel { background:#7DB5A2;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI ; }");
    ui->label_28->show();
    QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
            animation->setDuration(1000);
             QPoint initialPosition =ui->label_28->pos();


             int initialX = initialPosition.x();
             int initialY = initialPosition.y();
            animation->setStartValue(QRect(initialX,initialY,121,51));
            animation->setEndValue(QRect(705, 15, 121, 51));
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->start();
            ui->groupBox_6->show();
            ui->groupBox_8->hide();
            ui->groupBox_7->hide();
            ui->groupBox_5->hide();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
    }


}

void MainWindow::on_pushButton_employes_clicked()
{   QString user;
    user=ui->lineEdit->text();
    if(user=="admin" || user=="chef personel")
    {QGraphicsDropShadowEffect *shadow50=new QGraphicsDropShadowEffect;
    shadow50->setBlurRadius(1);
    shadow50->setColor(QColor(115,177,155,100));
    shadow50->setOffset(5,0);
    ui->label_28->setGraphicsEffect(shadow50);
    ui->label_28->setStyleSheet("QLabel { background:#73B19B;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI; }");
    ui->label_28->show();

    QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
            animation->setDuration(1000);
             QPoint initialPosition =ui->label_28->pos();
             int initialX = initialPosition.x();
             int initialY = initialPosition.y();
            animation->setStartValue(QRect(initialX,initialY,131,51));
            animation->setEndValue(QRect(837, 15, 131, 51));
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->start();
            ui->groupBox_8->hide();
            ui->groupBox_7->hide();
            ui->groupBox_6->hide();
            ui->groupBox_5->hide();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous n savez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
    }




 }

void MainWindow::on_pushButton_animaux_clicked()
{
    QString user;
    user=ui->lineEdit->text();
    if(user=="admin" || user=="berger")
    {
    QGraphicsDropShadowEffect *shadow50=new QGraphicsDropShadowEffect;
    shadow50->setBlurRadius(1);
    shadow50->setColor(QColor(81,160,133,100));
    shadow50->setOffset(5,0);
    ui->label_28->setGraphicsEffect(shadow50);
    ui->label_28->setStyleSheet("QLabel { background:#6aac95;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI ; }");
    ui->label_28->show();
    QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
            animation->setDuration(1000);
             QPoint initialPosition =ui->label_28->pos();
             int initialX = initialPosition.x();
             int initialY = initialPosition.y();
            animation->setStartValue(QRect(initialX,initialY,131,51));
            animation->setEndValue(QRect(971, 15, 131, 51));
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->start();
            ui->groupBox_7->show();
            ui->groupBox_8->hide();
            ui->groupBox_6->hide();
            ui->groupBox_5->hide();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
    }

}

void MainWindow::on_pushButton_agriculture_clicked()
{
    QString user;
      user=ui->lineEdit->text();
    if(user=="admin" || user=="chef de production")
    {ui->label_28->setStyleSheet("QLabel { background:#84B7A4;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI;}");
    ui->label_28->show();
    QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
            animation->setDuration(1000);
             QPoint initialPosition =ui->label_28->pos();

             int initialX = initialPosition.x();
             int initialY = initialPosition.y();
            animation->setStartValue(QRect(initialX,initialY,141,51));
            animation->setEndValue(QRect(440, 15, 141, 51));
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->start();
    ui->groupBox_8->show();
    ui->groupBox_7->hide();
    ui->groupBox_6->hide();
    ui->groupBox_5->hide();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
    }

}
//INSERTION LOGIN
void MainWindow::on_pushButton_6_clicked()
{
        QString user = ui->lineEdit_5->text();
        QString pass = ui->lineEdit_4->text();

        QSqlQuery query;

            query.prepare("INSERT INTO login (utilisateur,mot_de_passe) VALUES (:user, :mdp)");
            query.bindValue(":user", user);
            query.bindValue(":mdp", pass);

            if (query.exec()) {

                QMessageBox msgBox(QMessageBox::Information, QObject::tr("Succes"), QObject::tr("Votre compte est ajouter.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
                        QString styleSheet = "QMessageBox {"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                            "border: 2px outset grey;"
                            "}"
                            "QMessageBox QPushButton {"
                            "color: rgba(52,90,105,100%);"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                            "border-style: solid;"
                            "border: 2px solid transparent;"
                            "border-radius: 5px;"
                            "padding: 1px;"
                            "}"
                            "QMessageBox QPushButton:hover {"
                            "color: #B200ED ;"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                            "border-style: solid;"
                            "border: 2px solid transparent;"
                            "border-radius: 5px;"
                            "padding: 1px;"
                            "}";

                        msgBox.setStyleSheet(styleSheet);

                        msgBox.exec();
                        ui->groupBox_3->hide();
                        ui->groupBox->show();
                        }
             else {
                QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Non succes"), QObject::tr("Compte n est pas ajouter.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
                        QString styleSheet = "QMessageBox {"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                            "border: 2px outset grey;"
                            "}"
                            "QMessageBox QPushButton {"
                            "color: rgba(52,90,105,100%);"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                            "border-style: solid;"
                            "border: 2px solid transparent;"
                            "border-radius: 5px;"
                            "padding: 1px;"
                            "}"
                            "QMessageBox QPushButton:hover {"
                            "color: #B200ED ;"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                            "border-style: solid;"
                            "border: 2px solid transparent;"
                            "border-radius: 5px;"
                            "padding: 1px;"
                            "}";

                        msgBox.setStyleSheet(styleSheet);

                        msgBox.exec();
            }



    }



void MainWindow::on_pushButton_9_clicked()
{   QString user;
    user=ui->lineEdit->text();
    if(user=="admin" || user=="chef personel")
    {
        ui->label_28->show();

        QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
                animation->setDuration(1000);
                 QPoint initialPosition =ui->label_28->pos();
                 int initialX = initialPosition.x();
                 int initialY = initialPosition.y();
                animation->setStartValue(QRect(initialX,initialY,131,51));
                animation->setEndValue(QRect(837, 15, 131, 51));
                animation->setEasingCurve(QEasingCurve::Linear);
                animation->start();
    ui->groupBox_4->hide();
    ui->groupBox_2->show();
    QList<QWidget*> childWidgets = ui->label_32->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();
        }
    ui->label_32->hide();
    int s0,s1,s2,s3,s4,s5;
    s0=count0();
    s1=count1();
    s2=count2();
    s3=count3();
    s4=count4();
    s5=count5();
    cout<<s0;
    float stat=s0+s1+s2+s3+s4+s5;
    float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
    float y = (stat != 0) ? (s1 * 100) / stat : 0.0;
    float z = (stat != 0) ? (s2 * 100) / stat : 0.0;
    float d = (stat != 0) ? (s3 * 100) / stat : 0.0;
    float w = (stat != 0) ? (s4 * 100) / stat : 0.0;
    float p = (stat != 0) ? (s5 * 100) / stat : 0.0;


    QString ch1=QString("0 nba:%1%").arg(x);
    QString ch2=QString("1 nba:%1%").arg(y);
    QString ch3=QString("2 nba:%1%").arg(z);
    QString ch4=QString("3 nba:%1%").arg(d);
    QString ch5=QString("4 nba:%1%").arg(w);
    QString ch6=QString("5 nba:%1%").arg(p);
    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.39);
    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setBrush(QColor(187,93,87));
    QPieSlice *slice1= series->append(ch2,y);
    slice1->setLabelVisible();
    slice1->setBrush(QColor(255,186,186));
    QPieSlice *slice2= series->append(ch3,z);
    slice2->setLabelVisible();
    slice2->setBrush(QColor(255,123,123));
    slice2->setLabelColor(QColor(Qt::black));
    QPieSlice *slice3= series->append(ch4,d);
    slice3->setLabelVisible();
    slice3->setBrush(QColor(255,82,82));
    QPieSlice *slice4= series->append(ch5,w);
    slice4->setLabelVisible();
    slice4->setBrush(QColor(255,0,0,100));
    QPieSlice *slice5= series->append(ch6,p);
    slice5->setLabelVisible();
    slice5->setBrush(QColor(167,0,0,100));
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle("Statistique Pour Nombre D'année D'experience");
    //chart->setTheme(QChart::ChartThemeHighContrast);
    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->label_32->size());
    chartview->setParent(ui->label_32);
    ui->label_32->show();
    //ui->->setStyleSheet("QPushButton {background:#73B19B;border-top-left-radius:20px;border-top-right-radius:20px;color:#28322E;font-size:20px;font: 18pt Yu Gothic UI }");
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();
    }


}
//HOME
void MainWindow::on_pushButton_home_clicked()
{
    ui->groupBox_2->hide();
    ui->groupBox_5->hide();
    ui->groupBox_6->hide();
    ui->groupBox_7->hide();
    ui->groupBox_8->hide();
    ui->groupBox_4->show();
}


//SUPPRIMER
void MainWindow::on_pushButton_4_clicked()
{
    employe e;
    bool test;
    e.setid(ui->lineEdit_id->text());
    QString idString = ui->lineEdit_id->text();
    int id = idString.toInt();
    if (idString.isEmpty()) {

                QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Existe déjà"), QObject::tr("Saisie l ID s'il vous plait."), QMessageBox::Ok);

                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);

                msgBox.exec();

        return;
    }

    if (!e.idExists(id)) {
        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("N existe pas"), QObject::tr("L'ID que vous voulez n'existe pas."), QMessageBox::Ok);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();        return;
    }
    else
    test=e.supprimer(e.get_id());
    if(test)
    {
        QMessageBox msgBox(QMessageBox::Information, QObject::tr("OK"), QObject::tr("L'employé est supprimé\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
    }

        else
        {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Nope"), QObject::tr("L'employé n'est pas supprimé\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
    }






}

//AFFICHAGE TABLEVIEW
void MainWindow::on_pushButton_12_clicked()
{

       ui->tableView->setModel(e.afficher());
       QList<QWidget*> childWidgets = ui->label_32->findChildren<QWidget*>();
           for (QWidget* childWidget : childWidgets) {
               childWidget->deleteLater();
           }
       ui->label_32->hide();
       int s0,s1,s2,s3,s4,s5;
       s0=count0();
       s1=count1();
       s2=count2();
       s3=count3();
       s4=count4();
       s5=count5();
       cout<<s0;
       float stat=s0+s1+s2+s3+s4+s5;
       float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
       float y = (stat != 0) ? (s1 * 100) / stat : 0.0;
       float z = (stat != 0) ? (s2 * 100) / stat : 0.0;
       float d = (stat != 0) ? (s3 * 100) / stat : 0.0;
       float w = (stat != 0) ? (s4 * 100) / stat : 0.0;
       float p = (stat != 0) ? (s5 * 100) / stat : 0.0;

       QString ch1=QString("0 nba:%1%").arg(x);
       QString ch2=QString("1 nba:%1%").arg(y);
       QString ch3=QString("2 nba:%1%").arg(z);
       QString ch4=QString("3 nba:%1%").arg(d);
       QString ch5=QString("4 nba:%1%").arg(w);
       QString ch6=QString("5 nba:%1%").arg(p);
       QPieSeries *series=new QPieSeries();
       series->setHoleSize(0.39);
       QPieSlice *slice= series->append(ch1,x);
       slice->setLabelVisible();
       slice->setBrush(QColor(187,93,87));
       QPieSlice *slice1= series->append(ch2,y);
       slice1->setLabelVisible();
       slice1->setBrush(QColor(255,186,186));
       QPieSlice *slice2= series->append(ch3,z);
       slice2->setLabelVisible();
       slice2->setBrush(QColor(255,123,123));
       slice2->setLabelColor(QColor(Qt::black));
       QPieSlice *slice3= series->append(ch4,d);
       slice3->setLabelVisible();
       slice3->setBrush(QColor(255,82,82));
       QPieSlice *slice4= series->append(ch5,w);
       slice4->setLabelVisible();
       slice4->setBrush(QColor(255,0,0,100));
       QPieSlice *slice5= series->append(ch6,p);
       slice5->setLabelVisible();
       slice5->setBrush(QColor(167,0,0,100));
       QChart *chart=new QChart();
       chart->addSeries(series);
       chart->setAnimationOptions(QChart::AllAnimations);
       chart->setTitle("Statistique Pour Nombre D'année D'experience");
       //chart->setTheme(QChart::ChartThemeHighContrast);
       QBrush backgroundBrush(QColor(187,93,87,0));
       chart->setBackgroundBrush(backgroundBrush);
       QChartView *chartview=new QChartView(chart);
       chartview->setRenderHint(QPainter::Antialiasing);
       chartview->setFixedSize(ui->label_32->size());
       chartview->setParent(ui->label_32);
       ui->label_32->show();

}
//UPDATE
void MainWindow::on_pushButton_13_clicked()
{
    QString id=ui->lineEdit_id->text();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    QDate date=ui->dateEdit->date();
    int nb=ui->lineEdit_nbx->text().toInt();
    employe e(id,nom,prenom,salaire,date,nb);
    int c=0;
    int id1=id.toInt();
    if (!e.idExists(id1)){
        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("N'existe Pas"), QObject::tr("L'ID que vous voulez entrer n'existe pas dans la base de donnée."), QMessageBox::Ok);

        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();

        return;
        c++;
    }
    if(c==0)
    {

    bool test=e.update();


    if(test)
    {QMessageBox msgBox(QMessageBox::Information, QObject::tr("Succes"), QObject::tr("Update avec succes\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);

        msgBox.exec();
    }
    else
    {QMessageBox msgBox(QMessageBox::Information, QObject::tr("Non Succes"), QObject::tr("Update non succes\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    QString styleSheet = "QMessageBox {"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
        "border: 2px outset grey;"
        "}"
        "QMessageBox QPushButton {"
        "color: rgba(52,90,105,100%);"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
        "border-style: solid;"
        "border: 2px solid transparent;"
        "border-radius: 5px;"
        "padding: 1px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "color: #B200ED ;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
        "border-style: solid;"
        "border: 2px solid transparent;"
        "border-radius: 5px;"
        "padding: 1px;"
        "}";

    msgBox.setStyleSheet(styleSheet);

    msgBox.exec();
       }
    }
}
//BARRE RECHERCHER
void MainWindow::RechercheID() {
    QString searchText = ui->lineEdit_3->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE ide LIKE :id");
    query.bindValue(":id", "%" + searchText + "%");

    if (query.exec()) {
        QSqlQueryModel *searchModel = new QSqlQueryModel(this);
        searchModel->setQuery(query);
        ui->tableView->setModel(searchModel);
    }
}



//AFFICHAGE
void MainWindow::on_pushButton_14_clicked()
{
    ui->tableView->setModel(e.afficher1());

}
//PDF
void MainWindow::on_pushButton_15_clicked()
{


    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE salaire >= 5000");
    query.exec();
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());
    model->setQuery(query);

    if (model) {
        QString content;


                for (int col = 0; col < model->columnCount(); ++col) {

                     content += model->headerData(col, Qt::Horizontal).toString();
                     if (col < model->columnCount() - 2) {

                                 content += "\t";
                             } else {

                                 content += "\t \t";
                             }
                        }
                content += "\n";

                for (int row = 0; row < model->rowCount(); ++row) {
                    for (int col = 0; col < model->columnCount(); ++col) {
                        content += model->data(model->index(row, col)).toString() + "\t";
                    }
                    content += "\n";
                }


        QTextDocument document;
        document.setPlainText(content);

        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "C:/Users/LENOVO/Desktop", "Fichiers PDF (*.pdf)");

        if (!fileName.isEmpty()) {

            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);


            document.print(&printer);

            QMessageBox msgBox(QMessageBox::Information, QObject::tr("Export PDF"), QObject::tr("Le PDF a été créé avec succès\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();
        }
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    QString user;
        user=ui->lineEdit->text();
        if(user=="admin" || user=="responsable client")
        {
            ui->label_28->show();

            QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
                    animation->setDuration(1000);
                     QPoint initialPosition =ui->label_28->pos();
                     int initialX = initialPosition.x();
                     int initialY = initialPosition.y();
                    animation->setStartValue(QRect(initialX,initialY,111,51));
                    animation->setEndValue(QRect(587, 15, 111, 51));
                    animation->setEasingCurve(QEasingCurve::Linear);
                    animation->start();
            ui->groupBox_5->show();
            ui->groupBox_2->show();
            ui->groupBox_4->hide();

        }
        else
        {QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();}
}


void MainWindow::on_pushButton_8_clicked()
{
    QString user;
        user=ui->lineEdit->text();
        if(user=="admin" || user=="ingenieur mecanique")
        {ui->groupBox_6->show();
            ui->groupBox_4->hide();
            ui->label_28->show();

            QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
                    animation->setDuration(1000);
                     QPoint initialPosition =ui->label_28->pos();
                     int initialX = initialPosition.x();
                     int initialY = initialPosition.y();
                    animation->setStartValue(QRect(initialX,initialY,121,51));
                    animation->setEndValue(QRect(705, 15, 121, 51));
                    animation->setEasingCurve(QEasingCurve::Linear);
                    animation->start();
            ui->groupBox_2->show();
            }
        else
        {QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();}
}


void MainWindow::on_pushButton_10_clicked()
{
    QString user;
        user=ui->lineEdit->text();
        if(user=="admin" || user=="berger")
        {ui->groupBox_7->show();
            ui->label_28->show();

            QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
                    animation->setDuration(1000);
                     QPoint initialPosition =ui->label_28->pos();
                     int initialX = initialPosition.x();
                     int initialY = initialPosition.y();
                    animation->setStartValue(QRect(initialX,initialY,131,51));
                    animation->setEndValue(QRect(971, 15, 131, 51));
                    animation->setEasingCurve(QEasingCurve::Linear);
                    animation->start();
            ui->groupBox_4->hide();
            ui->groupBox_2->show();
           }
        else
        {QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();}
}

void MainWindow::on_pushButton_11_clicked()
{
    QString user;
        user=ui->lineEdit->text();
        if(user=="admin" || user=="chef production")
        {
            ui->label_28->show();

            QPropertyAnimation* animation = new QPropertyAnimation(ui->label_28, "geometry", this);
                    animation->setDuration(1000);
                     QPoint initialPosition =ui->label_28->pos();
                     int initialX = initialPosition.x();
                     int initialY = initialPosition.y();
                    animation->setStartValue(QRect(initialX,initialY,151,51));
                    animation->setEndValue(QRect(440, 15, 151, 51));
                    animation->setEasingCurve(QEasingCurve::Linear);
                    animation->start();ui->groupBox_8->show();
            ui->groupBox_4->hide();
            ui->groupBox_2->show();
           }
        else
        {QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Pas D'accés"), QObject::tr("Vous navez pas d accés pour cette gestion\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

            QString styleSheet = "QMessageBox {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border: 2px outset grey;"
                "}"
                "QMessageBox QPushButton {"
                "color: rgba(52,90,105,100%);"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "color: #B200ED ;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                "border-style: solid;"
                "border: 2px solid transparent;"
                "border-radius: 5px;"
                "padding: 1px;"
                "}";

            msgBox.setStyleSheet(styleSheet);

            msgBox.exec();}
}
//CHARGER DONNER L HORS DE SAISIE DE RECHERCHER ET CLIQUER ENTRER
void MainWindow::chargerDonneesUtilisateur() {

    QString idUtilisateur = ui->lineEdit_3->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE ide = :id");
    query.bindValue(":id", idUtilisateur);

    if (query.exec() && query.next()) {

        QString id=query.value("ide").toString();
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        float salaire=query.value("salaire").toFloat();
        QDate date=query.value("daten").toDate();
        int nba=query.value("nba").toInt();
        ui->lineEdit_nom->setText(nom);
        ui->lineEdit_prenom->setText(prenom);
        ui->lineEdit_id->setText(id);
        QString nbaString = QString::number(nba);
        ui->lineEdit_nbx->setText(nbaString);
        ui->dateEdit->setDate(date);
        QString salaireString = QString::number(salaire);
        ui->lineEdit_salaire->setText(salaireString);
    }
}




void MainWindow::on_pushButton_home_2_clicked()
{
    ui->groupBox_5->hide();
    ui->groupBox_4->show();
}

void MainWindow::on_pushButton_home_3_clicked()
{
    ui->groupBox_6->hide();
    ui->groupBox_4->show();
}

void MainWindow::on_pushButton_home_4_clicked()
{
    ui->groupBox_7->hide();
    ui->groupBox_4->show();
}

void MainWindow::on_pushButton_home_5_clicked()
{
    ui->groupBox_8->hide();
    ui->groupBox_4->show();
}


void MainWindow::on_pushButton_16_clicked()
{
    //ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->groupBox_4->hide();
    ui->groupBox_2->hide();
    ui->groupBox_5->hide();
    ui->groupBox_6->hide();
    ui->groupBox_7->hide();
    ui->groupBox_8->hide();
    ui->groupBox->show();
    QString user=ui->lineEdit->text();
    QString message = QObject::tr("Au Revoir ") + user.toUpper() + QObject::tr(" a La Prochaine. \nCliquez sur OK pour quitter.");
    QMessageBox msgBox(QMessageBox::Information, QObject::tr("A bientot"),message, QMessageBox::Ok);
                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);
                msgBox.exec();
                ui->lineEdit->clear();
                modifier_presence_login("admin", "ABSENT");

}
void MainWindow::on_notification_system()
    {



        // Send a Windows notification
        NOTIFYICONDATA nid;
        ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = reinterpret_cast<HWND>(this->winId());
        nid.uID = 1;  // Unique ID for the notification icon
        nid.uFlags = NIF_INFO;
        nid.dwInfoFlags = NIIF_INFO;
        nid.uTimeout = 3000;  // Display time in milliseconds

        wcscpy_s(nid.szInfoTitle, L"Notification");
        wcscpy_s(nid.szInfo, L"Bievenue dans SMART FARM");

        Shell_NotifyIcon(NIM_ADD, &nid);
        Shell_NotifyIcon(NIM_DELETE, &nid);
    }


bool MainWindow::modifier_presence_login(QString admin,QString PRECENSE)
{
    QSqlQuery query;


    query.prepare("UPDATE login SET etat=:PRECENSE where utilisateur=:admin");
    query.bindValue(":PRECENSE",PRECENSE);
    query.bindValue(":admin",admin);



      if (query.exec()) {
          // Commit the transaction
          QSqlDatabase::database().commit();
          return true;
      } else {
          // Rollback the transaction in case of an error
          QSqlDatabase::database().rollback();
          return false;
      }




}
void MainWindow::on_test_clicked()
{
    bool test;
    A.write_to_arduino("1");
    data=A.read_from_arduino();
    qDebug()<<"data="<< data;
    if(data=="0")
    {
        ui->lineEdit->setText("admin");
        ui->lineEdit_2->setText("123");
        test=modifier_presence_login("admin","present");
            if(test)
               {
                QMessageBox msgBox(QMessageBox::Information, QObject::tr("Empreinte avec Succés"), QObject::tr("Empreinte Match \nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
                QString styleSheet = "QMessageBox {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border: 2px outset grey;"
                    "}"
                    "QMessageBox QPushButton {"
                    "color: rgba(52,90,105,100%);"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}"
                    "QMessageBox QPushButton:hover {"
                    "color: #B200ED ;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
                    "border-style: solid;"
                    "border: 2px solid transparent;"
                    "border-radius: 5px;"
                    "padding: 1px;"
                    "}";

                msgBox.setStyleSheet(styleSheet);
                msgBox.exec();
                on_pushButton_3_clicked();

                }

            }
    else if(data=="2")
    {
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Empreinte Non match"), QObject::tr("Empreinte Non Match \nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        QString styleSheet = "QMessageBox {"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border: 2px outset grey;"
            "}"
            "QMessageBox QPushButton {"
            "color: rgba(52,90,105,100%);"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 90%), stop:1 rgba(132,183,164,90%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}"
            "QMessageBox QPushButton:hover {"
            "color: #B200ED ;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(245, 245, 220, 70%));"
            "border-style: solid;"
            "border: 2px solid transparent;"
            "border-radius: 5px;"
            "padding: 1px;"
            "}";

        msgBox.setStyleSheet(styleSheet);
        msgBox.exec();
    }

}


void MainWindow::closeEvent(QCloseEvent *event) {
    modifier_presence_login("admin", "absent");
    QMainWindow::closeEvent(event);
}

