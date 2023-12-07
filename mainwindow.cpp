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
#include "benefice.h"
#include "conseil.h"
#include"dialog.h"
#include"dialog1.h"
#include "map.h"
#include"maintenance.h"
//#include"machine.h"
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
        case (-1):qDebug()<<"arduino is not availble ";
        }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_test_clicked()));
    on_notification_system();
    //affichage
    ui->tableView_4->setModel(a.afficher());
    ui->tableView_3->setModel(C.afficher());
    ui->tableView_5->setModel(m.afficher());
    ui->tableView_6->setModel(ag.afficher());




    //fenetremap=nullptr;
    on_pushButton_48_clicked();
    //MARIEM
    ui->rdv->hide();
    ui->facture->hide();
    QRegularExpression regex1("^agri\\d+");
    ui->quantite->setValidator(new QIntValidator (0,300,this));
    ui->lineEdit_id_6->setValidator(new QRegularExpressionValidator(regex1,this));
    ui->prix_achat->setValidator(new QDoubleValidator(this));
    ui->prix_vente->setValidator(new QDoubleValidator(this));
    // lahna khtr khadma b groupbox fil type w pesticide
    ui->pesticide->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->type->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->type->addItem("");
    ui->pesticide->addItem("");


    ui->type->addItem("fruits");
    ui->type->addItem("legumes");
    ui->type->addItem("ornement");
    ui->type->addItem("aromatique");
    ui->type->addItem("cereale");
    ui->type->addItem("fourrage");
    ui->type->addItem("oleagineux");

    ui->pesticide->addItem("inesticide");
    ui->pesticide->addItem("forgicide");
    ui->pesticide->addItem("herbicide");
    //RANIM
    fenetreMaintenance = nullptr;
 fenetremap=nullptr;
  currentmachine=nullptr;

    //connect(ui->map, &QPushButton::clicked, this, &MainWindow::on_map_clicked);
    ui->position->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->position->addItem("");
    ui->position->addItem("bloc1");
    ui->position->addItem("bloc2");
    ui->position->addItem("bloc3");
    ui->position->addItem("bloc4");

    ui->etat->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->etat->addItem("");
    ui->etat->addItem("fonctionelle");
    ui->etat->addItem("en panne");

    ui->fonction->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->fonction->addItem("");
    ui->fonction->addItem("labourage");
    ui->fonction->addItem("récolte");
     ui->fonction->addItem("fèrtilisation");
      ui->fonction->addItem("semis");
      ui->fonction->addItem("pulvérisation");
      ui->fonction->addItem("arrosage");
      ui->q_carburant->setValidator( new QIntValidator(0,200, this));
      ui->nb_heures->setValidator(new QIntValidator(0,1000, this));
      QRegExp regex("\\d{3}tunisie\\d{4}");
      QRegExpValidator *validator = new QRegExpValidator(regex, this);
      ui->serie->setValidator(validator);


  //connect(ui->map, &QPushButton::clicked, this, &MainWindow::on_map_clicked);
   // ui->tabm->setModel(m.afficher());
    showMachineStatistics();
      //FARAH

      ui->lineEdit_id_2->setPlaceholderText("xxxxxx");
       ui->lineEdit_nom_2->setPlaceholderText("Nom");
       ui->lineEdit_prenom_2->setPlaceholderText("Prenom");
      ui->lineEdit_tel->setPlaceholderText("xx xxx xxx");
       ui->lineEdit_mail->setPlaceholderText("email@adresse.com");

       // Contrôle le champ de téléphone
       QRegExp rxTelephone("^(2|4|5|7|9)[0-9]{1} [0-9]{3} [0-9]{3}$");
       QValidator *telValidator = new QRegExpValidator(rxTelephone, this);
       ui->lineEdit_tel->setValidator(telValidator);

       // Controle le champ d'identifiant
           QIntValidator *intValidator = new QIntValidator(0, 999999, this);
           ui->lineEdit_id_2->setValidator(intValidator);

       // Controle le champ de nom et prenom
           QRegExp rxNom("^[A-Z][a-zA-Z ]*$");  // Expression régulière pour le nom avec espaces
           QRegExp rxPrenom("^[A-Z][a-zA-Z ]*$");  // Expression régulière pour le prénom avec espaces

           QValidator *nomValidator = new QRegExpValidator(rxNom, this);
           QValidator *prenomValidator = new QRegExpValidator(rxPrenom, this);

           ui->lineEdit_nom_2->setValidator(nomValidator);
           ui->lineEdit_prenom_2->setValidator(prenomValidator);

       // Controle le champ de mail
           QRegExp rxEmail("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");
           QValidator *emailValidator = new QRegExpValidator(rxEmail, this);
           ui->lineEdit_mail->setValidator(emailValidator);
           ui->tableView_3->setModel(C.afficher());



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
     ui->label_28->setStyleSheet("QLabel {border-radius: 25px; background: #E2D5BC; }");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QIntValidator *intValidator4 = new QIntValidator();
    ui->lineEdit_id->setValidator(intValidator4);
    ui->lineEdit_salaire->setValidator(intValidator4);
    ui->lineEdit_nbx->setValidator(intValidator4);
    QRegExp regex3("[A-Z]+", Qt::CaseInsensitive);
    QRegExpValidator* validator3 = new QRegExpValidator(regex3, this);
    ui->lineEdit_nom->setValidator(validator3);
    ui->lineEdit_prenom->setValidator(validator3);
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

    //QTimer *animationTimer = new QTimer(this);
    //connect(animationTimer, &QTimer::timeout, this, &MainWindow::animateTableBorderGradient);
    //animationTimer->start(60);

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
    //ui->label_31->setGraphicsEffect(shadow43);
    QGraphicsDropShadowEffect *shadow23=new QGraphicsDropShadowEffect;
    shadow23->setBlurRadius(10);
    shadow23->setColor(QColor(187,93,87,100));
    shadow23->setOffset(5,5);
    //ui->label_20->setGraphicsEffect(shadow23);
    ui->tableView->setModel(e.afficher());
    ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section { color:transparent; background-color:transparent; }");
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::RechercheID);
    connect(ui->lineEdit_9, &QLineEdit::textChanged, this, &MainWindow::RechercheID1);
    connect(ui->lineEdit_10, &QLineEdit::textChanged, this, &MainWindow::RechercheID2);
    connect(ui->lineEdit_8, &QLineEdit::textChanged, this, &MainWindow::RechercheID4);
    connect(ui->lineEdit_11, &QLineEdit::textChanged, this, &MainWindow::on_rech_clicked);



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


/*void MainWindow::animateTableBorderGradient() {
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
*/
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
    ui->label_28->setStyleSheet("QLabel { border-radius: 25px; background: #E2D5BC;  ; }");
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
    ui->label_28->setStyleSheet("QLabel { border-radius: 25px; background: #E2D5BC; }");
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
    ui->label_28->setStyleSheet("QLabel { border-radius: 25px; background: #E2D5BC;  }");
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
    ui->label_28->setStyleSheet("QLabel { border-radius: 25px; background: #E2D5BC;  }");
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
            ui->tableView_4->setModel(a.afficher());
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
    {ui->label_28->setStyleSheet("QLabel {border-radius: 25px; background: #E2D5BC; }");
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
    showstat();
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
            ui->tableView_6->setModel(ag.afficher());

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
    data=A.read_from_arduino();
    qDebug()<<"data="<< data;
    if(data=="1")
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
        ui->lineEdit->setText("chef personel");
        ui->lineEdit_2->setText("123");
        test=modifier_presence_login("chef personel","present");
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
    else if(data=="3")
    {
        ui->lineEdit->setText("berger");
        ui->lineEdit_2->setText("123");
        test=modifier_presence_login("berger","present");
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
    else if(data=="4")
    {
        ui->lineEdit->setText("responsable client");
        ui->lineEdit_2->setText("123");
        test=modifier_presence_login("responsable client","present");
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
    else if(data=="5")
    {
        ui->lineEdit->setText("chef production");
        ui->lineEdit_2->setText("123");
        test=modifier_presence_login("chef production","present");
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
    else if(data=="6")
    {
        ui->lineEdit->setText("ingenieur mecanique");
        ui->lineEdit_2->setText("123");
        test=modifier_presence_login("ingenieur mecanique","present");
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
    else
    {QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Empreinte Avec Non Succés"), QObject::tr("Empreinte Non Match \nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
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


void MainWindow::closeEvent(QCloseEvent *event) {
    modifier_presence_login("admin", "absent");
    modifier_presence_login("chef personel", "absent");
    modifier_presence_login("responsable client", "absent");
    modifier_presence_login("chef production", "absent");
    modifier_presence_login("ingenieur mecanique", "absent");
    modifier_presence_login("berger", "absent");

    QMainWindow::closeEvent(event);
}

//AHMED
void MainWindow::on_pushButton_31_clicked()
{
    int identifiant=ui->lineEdit_id_1->text().toInt();
    QString categorie=ui->lineEdit_ca->text();
    float masse=ui->lineEdit_ma->text().toFloat();
    float taille=ui->lineEdit_taille->text().toFloat();
    QString etat=ui->lineEdit_etat->text();
    QString nourriture=ui->lineEdit_nourriture->text();
    //controle de saisie


    QStringList test = {"malade", "sain"};  bool estDifferent = true;
     foreach (const QString &element, test) {
         if (element == etat) {
             estDifferent = false;
             break;
         }
     }if(estDifferent)
    {

        QMessageBox::critical(nullptr, QObject::tr("problem"),
                    QObject::tr("ajout failed.\n"
                                "vérifier ETAT/etat=malade/sain\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_etat->setStyleSheet("QLineEdit { border: 2px solid red; }");

    }
     else {
         ui->lineEdit_etat->setStyleSheet("");
     }


     if (categorie.length() < 3 || categorie.length() > 13){
         QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("categorie doit contenir minimum 4 lettres et maximum 13 lettres.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->lineEdit_ca->setStyleSheet("QLineEdit { border: 2px solid red; }");
         return;

     }
     else{
         ui->lineEdit_ca->setStyleSheet("");
     }

     if (nourriture.isEmpty()){ QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ida ne doit pas etre vide .\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->lineEdit_nourriture->setStyleSheet("QLineEdit { border: 2px solid red; }");
         return;

     }
     else{
         ui->lineEdit_nourriture->setStyleSheet("");
     }


int nbr=0;
    QSqlQuery query;
     query.prepare("SELECT * FROM ANIMAUX WHERE IDAN=:IDENTIFIANT");
     query.bindValue(":IDENTIFIANT",ui->lineEdit_id_1->text());
     query.exec();

     while(query.next())
     {
         nbr++;
     }
     if(nbr!=0)
     {
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
                     QObject::tr("ajout failed.\n"
                                 "IDENTIFIANT existe deja.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_id_1->setStyleSheet("QLineEdit { border: 2px solid red; }");
     }
     else{

    animaux a(identifiant,categorie,masse,taille,nourriture,etat);
      bool test =a.ajouter();
      if (test)

      {
          QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("ajout effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tableView_4->setModel(a.afficher());
    }
      else
          QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                      QObject::tr("Ajout non effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_33_clicked()
{
    a.setidentifiant(ui->lineEdit_id_1->text().toInt());
   bool test=a.supprimer(a.get_identifiant());
   if (test)
   {
       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("Suppression effectué avec succés.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableView_4->setModel(a.afficher());
  }
   else{
       QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                   QObject::tr("Suppression non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_35_clicked()
{
    int identifiant=ui->lineEdit_id_1->text().toInt();
    QString categorie=ui->lineEdit_ca->text();
    float masse=ui->lineEdit_ma->text().toFloat();
    float taille=ui->lineEdit_taille->text().toFloat();
    QString etat=ui->lineEdit_etat->text();
    QString nourriture=ui->lineEdit_nourriture->text();

    QStringList test = {"malade", "sain"};  bool estDifferent = true;
     foreach (const QString &element, test) {
         if (element == etat) {
             estDifferent = false;
             break;
         }
     }if(estDifferent)
    {

        QMessageBox::critical(nullptr, QObject::tr("problem"),
                    QObject::tr("ajout failed.\n"
                                "vérifier ETAT/etat=malade/sain\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_etat->setStyleSheet("QLineEdit { border: 2px solid red; }");

    }
     else {
         ui->lineEdit_etat->setStyleSheet("");
     }


     if (categorie.length() < 4 || categorie.length() > 13){
         QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("categorie doit contenir minimum 4 lettres et maximum 13 lettres.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->lineEdit_ca->setStyleSheet("QLineEdit { border: 2px solid red; }");
         return;

     }
     else{
         ui->lineEdit_ca->setStyleSheet("");
     }

     if (nourriture.isEmpty()){ QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ida ne doit pas etre vide .\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->lineEdit_nourriture->setStyleSheet("QLineEdit { border: 2px solid red; }");
         return;

     }
     else{
         ui->lineEdit_nourriture->setStyleSheet("");
     }


    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM ANIMAUX WHERE IDAN=:IDENTIFIANT");
       query.bindValue(":IDENTIFIANT", identifiant);
       query.exec();

       if (query.next()) {
           int count = query.value(0).toInt();
           if (count > 0) {
      animaux a(identifiant,categorie,masse,taille,nourriture,etat);
      a.Modifier(identifiant,categorie,masse,taille,etat,nourriture);
        ui->tableView_4->setModel(a.afficher());

            }
           else {
                   QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                               QObject::tr("ID N'EXISTE PAS.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}

    }
}

void MainWindow::on_pushButton_30_clicked()
{
    ui->tableView_4->setModel(a.afficher());

}
void MainWindow::RechercheID1()
{

    QString searchText =ui->lineEdit_9->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM animaux WHERE IDAN LIKE :id");
    query.bindValue(":id", "%" + searchText + "%");

    if (query.exec()) {
        QSqlQueryModel *searchModel = new QSqlQueryModel(this);
        searchModel->setQuery(query);
        ui->tableView_4->setModel(searchModel);
    }

    }

void MainWindow::on_pushButton_32_clicked()
{
    ui->tableView_4->setModel(a.tri());

    bool test=a.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_48_clicked()
{

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

    QSqlQueryModel model;
    model.setQuery("SELECT * FROM ANIMAUX WHERE CATEGORIE='cheval'");
    int number1 = model.rowCount();
    series->append("cheval", number1);
    series->setHoleSize(0.39);
    series->setLabelsVisible(true);
    series->slices().at(0)->setLabel("Mammifères");

    model.setQuery("SELECT * FROM ANIMAUX WHERE CATEGORIE='Oiseaux'");
    int number2 = model.rowCount();
    series->append("Oiseaux", number2);
    series->setLabelsVisible(true);
    series->slices().at(1)->setLabel("Oiseaux");

    model.setQuery("SELECT * FROM ANIMAUX WHERE CATEGORIE='Reptiles'");
    int number3 = model.rowCount();
    series->append("Reptiles", number3);
    series->setLabelsVisible(true);
    series->slices().at(2)->setLabel("Reptiles");

    model.setQuery("SELECT * FROM ANIMAUX WHERE CATEGORIE='mouton'");
    int number4 = model.rowCount();
    series->append("mouton", number4);
    series->setLabelsVisible(true);
    series->slices().at(3)->setLabel("mouton");

int total = number1 + number2 + number3 + number4;

QString a = QString("cheval" + QString::number((number1 * 100) / total, 'f', 2) + "%");
QString b = QString("Oiseaux " + QString::number((number2 * 100) / total, 'f', 2) + "%");
QString c = QString("Reptiles" + QString::number((number3 * 100) / total, 'f', 2) + "%");
QString d = QString("mouton" + QString::number((number4 * 100) / total, 'f', 2) + "%");



QtCharts::QChart *chart = new QtCharts::QChart();
chart->addSeries(series);
chart->setTitle("Pourcentage des Animaux selon la Catégorie");
chart->legend()->setFont(QFont("Arial", 10));


chart->setBackgroundBrush(QColor("#80b2a0"));

QtCharts::QChart::AnimationOptions options = QtCharts::QChart::AllAnimations;
chart->setAnimationOptions(options);

//jdida1
QChartView *chartview = new QChartView(chart);
chartview->setRenderHint(QPainter::Antialiasing);

QVBoxLayout *layout = new QVBoxLayout(ui->label_44);
layout->addWidget(chartview); // Ajout du QChartView au layout
ui->label_44->setLayout(layout);
// Vous pouvez afficher le chartView dans votre interface utilisateur
ui->label_44->show();
}

void MainWindow::on_pushButton_34_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM animaux ");
    query.exec();
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_4->model());
    model->setQuery(query);

    if (model) {
        QString content;


                for (int col = 0; col < model->columnCount(); ++col) {

                     content += model->headerData(col, Qt::Horizontal).toString();

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
}}
}
void MainWindow::on_pushButton_22_clicked()
{
    Dialog d;
    d.exec();
}
void MainWindow::on_pushButton_23_clicked()
{
    Dialog1 d;
    d.exec();
}
/*void MainWindow::on_pushButton_22_clicked()
{
    float coefficient_taille = 10.0;
    float coefficient_masse = 0.2;

    int identifiant = ui->lineEdit_id->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ANIMAUX WHERE IDAN = :identifiant");
    query.bindValue(":identifiant", identifiant);

    if (query.exec() && query.next()) {
        int masse = query.value("MASSE").toInt();
        int taille = query.value("TAILLE").toInt();
        QString categorie = query.value("CATEGORIE").toString();
        float score = (coefficient_taille * taille) + (coefficient_masse * masse);
        if (categorie == "Oiseaux") {
            QString etat = (score >= 50) ? "MALADE" : "SAIN";
            QString vaccination = (etat == "MALADE") ? "NON VACCINE" : "VACCINE";
            QString tempsVaccination = (etat == "SAIN") ? QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") : "";

            // Mise à jour de l'état dans la base de données
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE ANIMAUX SET ETAT = :etat, TEMPS_VACCINATION = :tempsVaccination WHERE IDENTIFIANT = :identifiant");
            updateQuery.bindValue(":etat", etat);
            updateQuery.bindValue(":tempsVaccination", tempsVaccination);
            updateQuery.bindValue(":identifiant", identifiant);
            updateQuery.exec();

            // Affichage du tableau
            QTableWidget *tableWidget = new QTableWidget(1, 7, this);  // Ajoutez deux colonnes pour la vaccination et le temps de vaccination
            tableWidget->resize(800, 600);
            tableWidget->show();
            tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État" << "Vaccination" << "Temps de vaccination");

            tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
            tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
            tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
            tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
            tableWidget->setItem(0, 4, new QTableWidgetItem(etat));
            tableWidget->setItem(0, 5, new QTableWidgetItem(vaccination));
            tableWidget->setItem(0, 6, new QTableWidgetItem(tempsVaccination));  // Ajoutez la colonne "Temps de vaccination"

            tableWidget->show();
        }
  else  if (categorie == "ane") {
      float coefficient_taille_ane = 8.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_ane = 0.3;

      // Calcul du score pour un âne
      float score_ane = (coefficient_taille_ane * taille) + (coefficient_masse_ane * masse);

      QString etat_ane = (score_ane >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANIMAUX SET ETAT = :etat WHERE IDAN = :identifiant");
      updateQuery.bindValue(":etat", etat_ane);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();


      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_ane));

      tableWidget->show();
  }
 else if (categorie == "mouton") {
      float coefficient_taille_mouton = 5.0;  // Ajustez ces coefficients en fonction de vos critères
      float coefficient_masse_mouton = 0.5;

      // Calcul du score pour les moutons
      float score_mouton = (coefficient_taille_mouton * taille) + (coefficient_masse_mouton * masse);

      QString etat_mouton = (score_mouton >= 50) ? "MALADE" : "SAIN";

      // Mise à jour de l'état dans la base de données
      QSqlQuery updateQuery;
      updateQuery.prepare("UPDATE ANNIMAUX SET ETAT = :etat WHERE IDENTIFIANT = :identifiant");
      updateQuery.bindValue(":etat", etat_mouton);
      updateQuery.bindValue(":identifiant", identifiant);
      updateQuery.exec();

      // Affichage du tableau
      QTableWidget *tableWidget = new QTableWidget(1, 5, this);
      tableWidget->resize(800, 600);
      tableWidget->show();
      tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État");

      tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(identifiant)));
      tableWidget->setItem(0, 1, new QTableWidgetItem(categorie));
      tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(masse)));
      tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(taille)));
      tableWidget->setItem(0, 4, new QTableWidgetItem(etat_mouton));

      tableWidget->show();
        }
}
}
*/
/*
void MainWindow::on_pushButton_23_clicked()
{
    // Obtenez la date actuelle
    QDate currentDate = QDate::currentDate();

    // Ajoutez un jour à la date actuelle
    QDate newDate = currentDate.addDays(1);
    QDate newDate1 = currentDate.addDays(30);

    // Récupérez l'identifiant depuis l'interface utilisateur
    int identifiant = ui->lineEdit_id->text().toInt();

    // Mettez à jour la base de données avec la première date
    QSqlQuery queryUpdate1;
    queryUpdate1.prepare("UPDATE ANIMAUX SET DATE_1=:DATE_1 WHERE VACCINATION=:identifiant");
    queryUpdate1.bindValue(":DATE_1", newDate);
    queryUpdate1.bindValue(":identifiant", "non");

    if (!queryUpdate1.exec()) {
        qDebug() << "Erreur de mise à jour 1:";
        return;
    }

    // Mettez à jour la base de données avec la deuxième date
    QSqlQuery queryUpdate2;
    queryUpdate2.prepare("UPDATE ANIMAUX SET DATE_2=:DATE_2 WHERE VACCINATION=:identifiant");
    queryUpdate2.bindValue(":DATE_2", newDate1);
    queryUpdate2.bindValue(":identifiant", "non");

    if (!queryUpdate2.exec()) {
        qDebug() << "Erreur de mise à jour 2:" ;
        return;
    }

    // Sélectionnez les données mises à jour
    QSqlQuery querySelect;
    querySelect.prepare("SELECT * FROM ANIMAUX WHERE IDENTIFIANT = :identifiant");
    querySelect.bindValue(":identifiant", identifiant);

    if (querySelect.exec() && querySelect.next()) {
        // Affichage du tableau
        QTableWidget *tableWidget = new QTableWidget(1, 9, this);
        tableWidget->resize(800, 600);
        tableWidget->setHorizontalHeaderLabels(QStringList() << "Identifiant" << "Categorie" << "Masse" << "Taille" << "État" << "IDA"<<"VACCINATION"<<"DATE_1"<<"DATE_2");

        // Remplissez le tableau avec les données sélectionnées
        tableWidget->setItem(0, 0, new QTableWidgetItem(querySelect.value("IDENTIFIANT").toString()));
        tableWidget->setItem(0, 1, new QTableWidgetItem(querySelect.value("CATEGORIE").toString()));
        tableWidget->setItem(0, 2, new QTableWidgetItem(querySelect.value("MASSE").toString()));
        tableWidget->setItem(0, 3, new QTableWidgetItem(querySelect.value("TAILLE").toString()));
        tableWidget->setItem(0, 4, new QTableWidgetItem(querySelect.value("ETAT").toString()));
        tableWidget->setItem(0, 5, new QTableWidgetItem(querySelect.value("IDA").toString()));
        tableWidget->setItem(0, 6, new QTableWidgetItem(querySelect.value("VACCINATION").toString()));

        // Utilisez toString avec le format "yyyy-MM-dd" pour afficher seulement la date
        QString formattedDate = querySelect.value("DATE_1").toDate().toString("yyyy-MM-dd");

        tableWidget->setItem(0, 7, new QTableWidgetItem(formattedDate));
        tableWidget->setItem(0, 8, new QTableWidgetItem(querySelect.value("DATE_2").toDate().toString("yyyy-MM-dd")));

        tableWidget->show();
    }
}
*/
//MARIEM
void MainWindow::on_pushButton_51_clicked()
{
    showstat();
}
void MainWindow::on_pushButton_47_clicked()
{
    bool test;
    QString type=ui->type->currentText();
    QString tdp=ui->pesticide->currentText();
    QString ida=ui->lineEdit_id_6->text();
    float pdv=ui->prix_vente->text().toFloat();
    float pda=ui->prix_achat->text().toFloat();
    int quantite=ui->quantite->text().toInt();
    QDate datep = ui->date->date();
    agri ag(ida,type,tdp,datep,pda,pdv,quantite);
    test=ag.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
        ui->tableView_6->setModel(ag.afficher());
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("ajout non effectué.\n "
                                        "click cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_46_clicked()
{
    ui->tableView_6->setModel(ag.afficher());

}

void MainWindow::on_pushButton_45_clicked()
{

        ag.setida(ui->lineEdit_id_6->text());
            bool test=ag.supprimer(ag.getida());
            if(test)
            {
                QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\nClick Cancel to exit."),QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Suppression non effectuée.\nClick Cancel to exit."),QMessageBox::Cancel);
            }
            ui->tableView_6->setModel(ag.afficher());

    }


void MainWindow::on_pushButton_44_clicked()
{

        ag.setida(ui->lineEdit_id_6->text());
        ag.settype(ui->type->currentText());
        ag.settdp(ui->pesticide->currentText());
        ag.setpda( ui->prix_achat->text().toFloat());
        ag.setpdv( ui->prix_vente->text().toFloat());
        ag.setquantite(ui->quantite->text().toInt());
        ag.setdatep(ui->date->date());

            bool success = ag.updateData(ag.getida());

            if (success)
            {
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("mise a jour  effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
                 ui->tableView_6->setModel(ag.afficher());
            }
            else
            {

                    QMessageBox::critical(this, tr("Échec de l'update"), tr("La mise à jour des données a échoué."));
            }
}


void MainWindow::on_pushButton_42_clicked()
{
    ui->tableView_6->setModel(ag.afficher1());

}

void MainWindow::on_pushButton_43_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM agriculture ");
    query.exec();
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_6->model());
    model->setQuery(query);

    if (model) {
        QString content;


                for (int col = 0; col < model->columnCount(); ++col) {

                     content += model->headerData(col, Qt::Horizontal).toString();

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
                }}
}
void MainWindow::on_rech_clicked()
{
    QString searchText =ui->lineEdit_11->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM agriculture WHERE IDA LIKE :id");
    query.bindValue(":id", "%" + searchText + "%");

    if (query.exec()) {
        QSqlQueryModel *searchModel = new QSqlQueryModel(this);
        searchModel->setQuery(query);
        ui->tableView_6->setModel(searchModel);
    }
}
void MainWindow::showstat() //hedhy fonction mta3 statistiques
{
    QString sqlQuery = "SELECT TYPE, SUM(QUANTITE) AS quantitetotale FROM agriculture GROUP BY TYPE";
       QSqlQuery query;
       query.prepare(sqlQuery);

       QBarSeries *series = new QBarSeries();
       QBarCategoryAxis *axisX = new QBarCategoryAxis();
       if (query.exec()) {
           while (query.next()) {
               QString type = query.value(0).toString();
               double quantitetotale = query.value(1).toDouble();
               QBarSet *barSet = new QBarSet(type);
               *barSet << quantitetotale;
               series->append(barSet);
               axisX->append(type);
           }
       } else {
           qDebug() << "Erreur d'exécution de la requête : " << query.lastError().text();
       }

       // Création du graphique
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques de vente par type");
       chart->setAnimationOptions(QChart::AllAnimations);

       QValueAxis *axisY = new QValueAxis();
       chart->setAxisY(axisY, series);

       QChartView *chartView = new QChartView(chart);

       // Ajoutez le QChartView au widget dans votre interface utilisateur (chartContainer)
          QListWidget *chartContainer = ui->listWidget;
          QVBoxLayout *layout = new QVBoxLayout(chartContainer);
          layout->addWidget(chartView);
}

//Ranim


void MainWindow::on_pushButton_41_clicked()
{
    QString serie=ui->serie->text();
    QString etat=ui->etat->currentText();
    QString fonction=ui->fonction->currentText();
    QString position=ui->position->currentText();
     int nb_heures=ui->nb_heures->text().toInt();
      int q_carburant=ui->q_carburant->text().toInt();
      machine m (serie,nb_heures,etat,fonction,position,q_carburant);
      bool test=m.ajouter();
      if (test)
      {
       QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
                ui->tableView_5->setModel(m.afficher());


      }
      else
          QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectuer.\n""click cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_pushButton_40_clicked()
{
    ui->tableView_5->setModel(m.afficher());

}

void MainWindow::on_pushButton_38_clicked()
{
    machine m;
    m.setserie(ui->serie->text());
       m.setetat (ui->etat->currentText());
        m.setfonction( ui->fonction->currentText());
        m.setposition ( ui->position->currentText());
        m.setq_carburant( ui->q_carburant->text().toInt());
       m.setnb_heures( ui->nb_heures->text().toInt());

        bool success = m.updateData(m.getserie());

        if (success)
        {
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("mise a jour  effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
             ui->tableView_5->setModel(m.afficher());
        }
        else
        {

                QMessageBox::critical(this, tr("Échec de l'update"), tr("La mise à jour des données a échoué."));
        }
}

void MainWindow::on_pushButton_37_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM machines ");
    query.exec();
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_5->model());
    model->setQuery(query);

    if (model) {
        QString content;


                for (int col = 0; col < model->columnCount(); ++col) {

                     content += model->headerData(col, Qt::Horizontal).toString();

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
                }}
}

void MainWindow::showMachineStatistics()
{
   /* QString sqlQuery = "SELECT serie, SUM(nombre_heure) AS heures_totales FROM machines GROUP BY serie";
    QSqlQuery query;
    query.prepare(sqlQuery);

    QBarSeries *series = new QBarSeries();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    if (query.exec()) {
        while (query.next()) {
            QString serie = query.value(0).toString();
            double heuresTotales = query.value(1).toDouble();
            QBarSet *barSet = new QBarSet(serie);
            *barSet << heuresTotales;
            series->append(barSet);
            axisX->append(serie);
        }
    } else {
        qDebug() << "Erreur d'exécution de la requête : " << query.lastError().text();
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des machines par serie");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart);

    // Ajoutez le QChartView au widget dans votre interface utilisateur (chartContainer)
    QWidget *chartContainer = ui->listWidget_2; // Assurez-vous que le nom correspond à celui dans votre fichier .ui
    QVBoxLayout *layout = new QVBoxLayout(chartContainer);
    layout->addWidget(chartView);
    connect(ui->tableView_5->model(), &QAbstractItemModel::dataChanged, this, &MainWindow::updateStatistics);*/
    QString sqlQuery = "SELECT serie, SUM(nombre_heure) AS heures_totales FROM machines GROUP BY serie";
        QSqlQuery query;
        query.prepare(sqlQuery);

        QBarSeries *series = new QBarSeries();
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        if (query.exec()) {
            while (query.next()) {
                QString serie = query.value(0).toString();
                double heuresTotales = query.value(1).toDouble();
                QBarSet *barSet = new QBarSet(serie);
                *barSet << heuresTotales;
                series->append(barSet);
                axisX->append(serie);
            }
        } else {
            qDebug() << "Erreur d'exécution de la requête : " << query.lastError().text();
        }

        // Création du graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des machines par serie");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QValueAxis *axisY = new QValueAxis();
        chart->setAxisY(axisY, series);

        QChartView *chartView = new QChartView(chart);

        // Ajoutez le QChartView au widget dans votre interface utilisateur (chartContainer)
        QWidget *chartContainer = ui->listWidget_2; // Assurez-vous que le nom correspond à celui dans votre fichier .ui
        QVBoxLayout *layout = new QVBoxLayout(chartContainer);
        layout->addWidget(chartView);
        connect(ui->tableView_4->model(), &QAbstractItemModel::dataChanged, this, &MainWindow::updateStatistics);
}
void MainWindow::updateStatistics()
{
    QLayout *containerLayout = ui->listWidget_2->layout();
    if (containerLayout) {
        // Attempt to find the chart or chart view in the layout
        QChart *chart = nullptr;

        // Check if the widget at index 0 is a QChartView
        if (containerLayout->count() > 0) {
            QWidget *widgetAtIndex0 = containerLayout->itemAt(0)->widget();
            QChartView *chartView = dynamic_cast<QChartView*>(widgetAtIndex0);

            if (chartView) {
                chart = chartView->chart();
            }
        }

        // If not found, check if the widget itself is a QChart
        if (!chart) {
            QChart *chartWidget = dynamic_cast<QChart*>(ui->listWidget_2);
            if (chartWidget) {
                chart = chartWidget;
            }
        }

        if (chart) {
            QBarSeries *series = dynamic_cast<QBarSeries*>(chart->series().at(0));

            if (series) {
                // Rest of your update logic here
                QString sqlQuery = "SELECT serie, SUM(nombre_heure) AS heures_totales FROM machines GROUP BY serie";
                QSqlQuery query;
                query.prepare(sqlQuery);

                // Rest of your update logic here...

                qDebug() << "Chart updated successfully.";
                return;
            } else {
                qDebug() << "Series not found in the chart.";
            }
        } else {
            qDebug() << "Chart not found in the layout.";
        }
    } else {
        qDebug() << "No layout in the chartContainer.";
    }
}

void MainWindow::RechercheID2()
{

    QString searchText =ui->lineEdit_10->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM machines WHERE serie LIKE :id");
    query.bindValue(":id", "%" + searchText + "%");

    if (query.exec()) {
        QSqlQueryModel *searchModel = new QSqlQueryModel(this);
        searchModel->setQuery(query);
        ui->tableView_5->setModel(searchModel);
    }

    }
void MainWindow::RechercheID4()
{

    QString searchText =ui->lineEdit_8->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM client WHERE idc LIKE :id");
    query.bindValue(":id", "%" + searchText + "%");

    if (query.exec()) {
        QSqlQueryModel *searchModel = new QSqlQueryModel(this);
        searchModel->setQuery(query);
        ui->tableView_3->setModel(searchModel);
    }

    }
void MainWindow::on_pushButton_39_clicked()
{
    QString serie=(ui->serie->text());
        bool test=m.supprimer(serie);
        if (test)
        {
         QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("suppression effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
         ui->tableView_5->setModel(m.afficher());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("suppression non effectuer.\n""click cancel to exit."),QMessageBox::Cancel);

}
/*void MainWindow::on_pushButton_50_clicked()
{
    if (fenetreMaintenance)
    {
        // Assurez-vous que la fenêtre maintenance existe
        fenetreMaintenance->enregistrerEtAfficher();
        fenetreMaintenance->show();

    }
    else
    {
        // Si la fenêtre maintenance n'existe pas, créez-la et affichez-la
        fenetreMaintenance = new maintenance(this);
        fenetreMaintenance->show();
    }
}*/
/*void MainWindow::on_map_clicked()
{
    if (!fenetremap) {
            fenetremap = new map(this);
        }
        fenetremap->show();
        QString machinePosition = ui->position->currentText();
            QString machineSerie = ui->serie->text();
            fenetremap->updateLabelFromMachine(machinePosition, machineSerie);

}*/
/*
void MainWindow::on_map_clicked()
{

    if (!fenetremap) {
            fenetremap = new map(this);
        }
        fenetremap->show();
        QString machinePosition = ui->position->currentText();
            QString machineSerie = ui->serie->text();
            fenetremap->updateLabelFromMachine(machinePosition, machineSerie);
}
void MainWindow::setDatabase(QSqlDatabase& db) {
    database = db;
}
//bouton arduino
void MainWindow::on_pushButton_2_clicked()
{
    QByteArray dataToSend = "Hello Arduino!";
        machine myMachine; // Remplacez ceci par votre instance de machine réelle
        QByteArray dataFromArduino = myarduino.read_from_arduino();

        // Traitement des données lues depuis l'Arduino
        if (!dataFromArduino.isEmpty()) {
            qDebug() << "Données lues depuis Arduino : " << dataFromArduino;

            int wateringTime = myarduino.getWateringTimeFromData(dataFromArduino);
            qDebug() << "Temps d'arrosage reçu depuis Arduino : " << wateringTime << " secondes";
            if (wateringTime != -1) {


                QString serie = myMachine.rechercherParSerieFormat();
                 qDebug() << "Série trouvée dans la base de données : " << serie;
                if (!serie.isEmpty()) {
                    // Une série valide a été trouvée dans la base de données
                    QSqlQuery updateQuery(database);
                    updateQuery.prepare("UPDATE machines SET nombre_heure = :nb_heures WHERE serie = :serie");
                    updateQuery.bindValue(":nb_heures", wateringTime);
                    updateQuery.bindValue(":serie", serie);

                    if (updateQuery.exec()) {
                        qDebug() << "Heures d'arrosage mises à jour dans la base de données.";
                    } else {
                        qDebug() << "Échec de la mise à jour des heures d'arrosage dans la base de données : " << updateQuery.lastError().text();
                            }
                }
                else {
                    qDebug() << "Aucune machine avec une série valide trouvée dans la base de données.";
                }

            } else {
                qDebug() << "Aucun temps d'arrosage trouvé dans les données lues depuis Arduino.";
            }
        } else {
            qDebug() << "Aucune donnée lue depuis Arduino.";
        }
    }
*/
//FARAH
void MainWindow::on_pushButton_19_clicked()
{
    QString nom = ui->lineEdit_nom_2->text();
    QString prenom = ui->lineEdit_prenom_2->text();
    int id = ui->lineEdit_id_2->text().toInt();
    QString mail = ui->lineEdit_mail->text();
    QDate date = ui->dateEdit_2->date();
    QString tel = ui->lineEdit_tel->text();

    Client C(nom, prenom, mail, id, tel, date);
    bool ajoutReussi = C.ajouter();

    if (ajoutReussi) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué! \nClick cancel to exit."), QMessageBox::Cancel);

        // Refresh the QTableView with the updated data
        ui->tableView_3->setModel(C.afficher());
        ui->tableView_3->resizeColumnsToContents();
        ui->tableView_3->resizeRowsToContents();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajout failed. \nClick cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->tableView_3->setModel(C.afficher());
}
void MainWindow::on_pushButton_17_clicked()
{
    Client C;
    int id = ui->lineEdit_id_2->text().toInt();
    bool test = C.supprimer(id);
    if (test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée! \nClick cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression failed. \nClick cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    QString nom = ui->lineEdit_nom_2->text();
    QString prenom = ui->lineEdit_prenom_2->text();
    int id = ui->lineEdit_id_2->text().toInt();
    QString mail = ui->lineEdit_mail->text();
    QDate date = ui->dateEdit_2->date();
    QString tel = ui->lineEdit_tel->text();
    Client C(nom, prenom, mail, id, tel, date);
    bool test =C.update();
    if (test)
    {
        // Refresh
       // ui->tableView->setModel(C.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Update effectuée! \n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Update failed. \n"
                                          "Click cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_27_clicked()
{
    bool triSuccess = C.trier();

       if (triSuccess) {
           QSqlQueryModel *sortedModel = new QSqlQueryModel();
           sortedModel->setQuery("SELECT * FROM CLIENT ORDER BY date_a ASC");
           sortedModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
           sortedModel->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           sortedModel->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           sortedModel->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
           sortedModel->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
           sortedModel->setHeaderData(5, Qt::Horizontal, QObject::tr("tel"));

           ui->tableView->setModel(sortedModel);

           QMessageBox::information(nullptr, QObject::tr("Tri effectué"),
               QObject::tr("La liste des clients a été triée par date d'achat."), QMessageBox::Ok);
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Erreur de tri"),
               QObject::tr("Échec du tri de la liste des clients."), QMessageBox::Ok);
       }
}
bool MainWindow::chercher(int id)
{
    return C.chercher(id);
}
/*void MainWindow::on_pb_rechhhh_clicked()
{
    int id = ui->lineEdit_8->text().toInt();
    QSqlQueryModel *clientModel = C.chercher(id);

    if (clientModel) {
        // Afficher les données dans la tableView
        ui->tableView->setModel(clientModel);

        QMessageBox::information(nullptr, QObject::tr("Client trouvé"),
            QObject::tr("Le client a été trouvé."), QMessageBox::Ok);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Client non trouvé"),
            QObject::tr("Le client n'a pas été trouvé."), QMessageBox::Ok);
    }

    }
*/
void MainWindow::on_pushButton_29_clicked()
{
    QString nomFichierPdf = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "Fichiers PDF (*.pdf)");

        if (!nomFichierPdf.isEmpty()) {
            bool exportReussi = C.exporterPdf(nomFichierPdf);

            if (exportReussi) {
                QMessageBox::information(this, "Exportation PDF réussie", "Les données ont été exportées en PDF.");
            } else {
                QMessageBox::critical(this, "Échec de l'exportation PDF", "L'exportation des données en PDF a échoué.");
            }
        }
}


void MainWindow::on_pushButton_21_clicked()
{
    // Clear le contenu actuel du listWidget
    ui->listWidget_3->clear();

    // Crée un graphique à colonnes
    QtCharts::QChart *chart = new QtCharts::QChart();
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    // Crée un axe de catégories pour l'axe X
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Crée l'axe Y
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Liste des noms abrégés des mois
    QStringList monthNames = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Pour chaque mois de l'année (de 1 à 12)
    for (int mois = 1; mois <= 12; ++mois) {
        int nombreClients = C.getNombreClientsParMois(mois);

        if (nombreClients != -1) {
            // Ajoute une barre au graphique
            QtCharts::QBarSet *barSet = new QtCharts::QBarSet(monthNames.at(mois - 1));
            *barSet << nombreClients;
            series->append(barSet);
        } else {
            // Affiche une erreur si la requête a échoué
            ui->listWidget_3->addItem(new QListWidgetItem("Erreur lors de la récupération des statistiques"));
            break;
        }
    }

    // Ajoute la série au graphique
    chart->addSeries(series);

    // Définit les catégories sur l'axe X
    axisX->append(monthNames);

    // Définit la taille du graphique en fonction des dimensions du listWidget
    chart->setMinimumSize(650, 240);

    // Les animations
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Crée la vue du graphique et l'ajoute au listWidget
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(650, 240));
    ui->listWidget_3->addItem(item);
    ui->listWidget_3->setItemWidget(item, chartView);
}
void MainWindow::on_pushButton_26_clicked()
{
    ui->rdv->show();
    ui->facture->hide();
    ui->groupBox_5->hide();
    ui->groupBox_2->hide();
    ui->groupBox->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_6->hide();
    ui->groupBox_7->hide();
    ui->groupBox_8->hide();
}
void MainWindow::on_pb_rdvv_clicked()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    QString startTimeStr = ui->start->time().toString("hh:mm");
    int id = ui->lineEdit_8->text().toInt();

    QSqlQuery query;

    // Select the record to check if it exists
    query.prepare("SELECT * FROM client WHERE idc = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Check if the selected date and time are already reserved
        query.prepare("SELECT * FROM client WHERE DATE_RDV = :dateRDV AND TEMPS_RDV = :tempsRDV AND idc != :id");
        query.bindValue(":id", id);
        query.bindValue(":dateRDV", selectedDate);
        query.bindValue(":tempsRDV", startTimeStr);

        if (query.exec() && query.next()) {
            QMessageBox::warning(nullptr, QObject::tr("Error"), QObject::tr("La date et l'heure sont déjà réservées."), QMessageBox::Cancel);
        } else {
            // Update the record with the new date and time
            query.prepare("UPDATE client SET DATE_RDV=:dateRDV, TEMPS_RDV=:tempsRDV WHERE idc=:id");
            query.bindValue(":id", id);
            query.bindValue(":dateRDV", selectedDate);
            query.bindValue(":tempsRDV", startTimeStr);

            if (query.exec()) {
                QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Votre rendez-vous pour le %1 à %2 est enregistré.").arg(selectedDate.toString("dd/MM/yyyy"), startTimeStr), QMessageBox::Cancel);
            }else {
                QMessageBox::warning(nullptr, QObject::tr("Error"), QObject::tr("Failed to update record."), QMessageBox::Cancel);
            }
        }
    } else {
        QMessageBox::warning(nullptr, QObject::tr("Error"), QObject::tr("Veuillez donner l'identifiant du client."), QMessageBox::Cancel);
    }
    ui->rdv->hide();
    ui->facture->hide();
    ui->groupBox_5->show();
    ui->groupBox_2->show();
    ui->groupBox->show();
    ui->groupBox_3->show();
    ui->groupBox_6->show();
    ui->groupBox_7->show();
    ui->groupBox_8->show();
}
void MainWindow::on_pushButton_49_clicked()
{
    ui->facture->show();
    ui->groupBox_5->hide();
    ui->groupBox_2->hide();
    ui->groupBox->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_6->hide();
    ui->groupBox_7->hide();
    ui->groupBox_8->hide();


}
void MainWindow::on_pb_fact_clicked() //metier2
{
    int id = ui->lineEdit_8->text().toInt();
    QSqlQuery query;


    // Assumez que les données du produit et du prix sont dans lineEdit_prod et lineEdit_prix
    QString produit = ui->lineEdit_prod->text();
    double prix = ui->lineEdit_prix->text().toDouble();

    // Ajouter les données dans Excel (CSV format)
    addToCSV(id, produit, prix);
    ui->facture->hide();
    ui->groupBox_5->show();
    ui->groupBox_2->show();
    ui->groupBox_3->show();
    ui->groupBox_6->show();
    ui->groupBox_7->show();
    ui->groupBox_8->show();

}
void MainWindow::addToCSV(int id, const QString& produit, double prix) //teb3a metier2
{
    QSqlQuery query;
    query.prepare("SELECT * FROM client WHERE idc = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Retrieve client data
        QString nomClient = query.value("nom").toString();
        QString prenomClient = query.value("prenom").toString();

        // Prepare the CSV data
        QString csvData = QString("\"ID\",\"Nom\",\"Prénom\",\"Produit\",\"Prix\"\n"
                                  "\"%1\",\"%2\",\"%3\",\"%4\",%5\n")
                              .arg(id)
                              .arg(nomClient)
                              .arg(prenomClient)
                              .arg(produit)
                              .arg(QLocale().toString(prix, 'f', 2));  // Use QLocale to format the double

        // Open the file in append mode
        QFile file("facture.csv");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);

            // Write the CSV data
            out << csvData;

            file.close();

            // Open the CSV file with the default application (Excel)
            QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath() + "/facture.csv"));
        } else {
            // Handle the case where the file cannot be opened for writing
            QMessageBox::warning(this, "Erreur", "Le fichier CSV ne peut pas être ouvert en écriture.");
        }
    } else {
        // Handle the case where the identifier is not found in the database
        QMessageBox::warning(this, "Erreur", "L'identifiant n'a pas été trouvé dans la base de données.");
    }
}
/*

void MainWindow::on_pb_fact_clicked() //metier2
{
    int id = ui->lineEdit_rech->text().toInt();
    QSqlQuery query;


    // Assumez que les données du produit et du prix sont dans lineEdit_prod et lineEdit_prix
    QString produit = ui->lineEdit_prod->text();
    double prix = ui->lineEdit_prix->text().toDouble();

    // Ajouter les données dans Excel (CSV format)
    addToCSV(id, produit, prix);
}

void MainWindow::addToCSV(int id, const QString& produit, double prix) //teb3a metier2
{
    QSqlQuery query;
    query.prepare("SELECT * FROM client WHERE idc = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Retrieve client data
        QString nomClient = query.value("nom").toString();
        QString prenomClient = query.value("prenom").toString();

        // Prepare the CSV data
        QString csvData = QString("\"ID\",\"Nom\",\"Prénom\",\"Produit\",\"Prix\"\n"
                                  "\"%1\",\"%2\",\"%3\",\"%4\",%5\n")
                              .arg(id)
                              .arg(nomClient)
                              .arg(prenomClient)
                              .arg(produit)
                              .arg(QLocale().toString(prix, 'f', 2));  // Use QLocale to format the double

        // Open the file in append mode
        QFile file("facture.csv");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);

            // Write the CSV data
            out << csvData;

            file.close();

            // Open the CSV file with the default application (Excel)
            QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath() + "/facture.csv"));
        } else {
            // Handle the case where the file cannot be opened for writing
            QMessageBox::warning(this, "Erreur", "Le fichier CSV ne peut pas être ouvert en écriture.");
        }
    } else {
        // Handle the case where the identifier is not found in the database
        QMessageBox::warning(this, "Erreur", "L'identifiant n'a pas été trouvé dans la base de données.");
    }
}

//hedhouma ll fenetre li tethall jdida
void MainWindow::on_appo_clicked()
{
    ui->rdv->show();
    ui->facture->hide();
    ui->main->hide();
}

void MainWindow::on_pb_factoo_clicked()
{
    ui->facture->show();
    ui->main->hide();

}

void MainWindow::on_retourr_clicked()
{
    ui->facture->hide();
    ui->main->show();
}

void MainWindow::on_retour_clicked()
{
    ui->rdv->hide();
    ui->main->show();
}

//arduino w me teb3ou
void MainWindow::processSerialData()
{
    // Read data from the serial port
    QByteArray data = serial->readAll();

    // Convert the data to a QString
    QString receivedData = QString::fromUtf8(data).trimmed();  // Trim whitespace

    // Debug: Print received data
    qDebug() << "Received data: " << receivedData;

    // Process the received data
    if (receivedData == "A") {
        ui->lineEdit_status->setText("Access Authorized");

        // Assuming you have a valid client ID (e.g., 123456) for the update
        int clientIdToUpdate = 123456;

        // Update database for the given ID
        QSqlQuery query;
        query.prepare("UPDATE CLIENT SET access_status = 'ACCES AUTORISE' WHERE idc = :id");
        query.bindValue(":id", clientIdToUpdate);

        if (query.exec()) {
            qDebug() << "Database updated successfully for ID: " << clientIdToUpdate;
        } else {
            qDebug() << "Failed to update database for ID: " << clientIdToUpdate;
        }
    } else if (receivedData == "D") {
        ui->lineEdit_status->setText("Access Denied");
    } else {
        // Add additional handling for unexpected data
        ui->lineEdit_status->setText("Message: " + receivedData);
    }

    // You might need additional logic depending on your communication protocol
}*/



void MainWindow::on_pushButton_24_clicked()
{
        double beneficeTotal = ag.calculbenefice();

            // Créez une instance de la nouvelle fenêtre
            benefice(nouvelleFenetre);

            // Convertir le résultat en QString
            QString resultatStr = QString("Votre bénéfice total pour ces\nmois est  :");
            QString resultatStr1 = QString("N'oubliez pas que\npour augmenter vos\nbénéfices il faut\nque vous choisissez les bon\n plants à mettre en\nterre");

            // Mettez à jour le texte du QLabel dans la nouvelle fenêtre avec le résultat
            nouvelleFenetre.setLabelText(resultatStr);
            nouvelleFenetre.setBeneficeTotalText(QString::number(beneficeTotal));
            //nouvelleFenetre.setLabelText1(resultatStr1);


            // Afficher la nouvelle fenêtre
            nouvelleFenetre.exec();
}

void MainWindow::on_pushButton_25_clicked()
{
    conseil( nouvelleFenetre);
    QString resultatStr1, resultatStr2, resultatStr3, resultatStr4, resultatStr5, resultatStr6, resultatStr7, resultatStr8;
    if(ui->pconseil->text()=="legumes")
    {
        QString t= QString("Les légumes");
        QString m= QString("Les maladies courantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Pratiquez la rotation\ndes cultures pour\néviter l'épuisement\ndu sol.");
        resultatStr2 = QString("Respectez les\ndistances\nrecommandées entre\nles plants pour éviter\nla compétition pour\nles nutriments.");
        resultatStr3= QString("Planifiez les périodes\nde plantation en fonction\ndu cycle de vie de chaque\nlégume et des conditions\nmétéorologiques locales.");
        resultatStr4= QString("Plantez des herbes ou des\nlégumes répulsifs à\nproximité de certains\nlégumes pour bénéficier de\nleurs relations bénéfiques\net dissuader les ravageurs.");
        resultatStr5= QString("Protégez les légumes\nsensibles au gel en\nutilisant des couvertures\nou des tunnels pendant les\npériodes de gel tardif ou\nprécoce.");
        resultatStr6= QString("1. Mildiou : \nMildiou de la tomate.\n2. Oïdium : \nOïdium du concombre.\n3. Pourriture des Racines : \nPourriture des racines des\ncarottes.");
        resultatStr7= QString("Il est important de\nsurveiller régulièrement\nvos légumes pour\ndétecter tout signe de\nmaladie ou de ravageur\net d'adopter des pratiques\nde jardinage saines pour\nminimiser les risques.\nUtilisez des pesticides avec\nprécaution,en privilégiant\nles solutions biologiques et\nnaturelles autant que\npossible. ");
        resultatStr8= QString("-Utilisez des insecticides\nspécifiques pour lutter\ncontre les ravageurs\n"
                              "-Appliquez des\nfongicides pour\nprévenir ou traiter\nles maladies fongiques.\n"
                              "-Utilisez des herbicides\nsélectifs pour le\ncontrôle des mauvaises\nherbes.");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else if(ui->pconseil->text()=="fruits")
    {
        QString t= QString("Les fruits");
        QString m= QString("Les maladies courantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Choisissez des variétés\nadaptées au climat de\nvotre région et résistantes\naux maladies locales.");
        resultatStr2 = QString("Appliquez des engrais\néquilibrés en fonction des\nbesoins nutritifs\nspécifiques de chaque\ntype de fruit.");
        resultatStr3= QString("Contrôlez les mauvaises\nherbes autour des arbres\nfruitiers pour éviter\nla compétition pour les\nnutriments.");
        resultatStr4= QString("Pratiquez une taille\nrégulière pour maintenir la\nforme des arbres et\nfavoriser une meilleure\ncirculation de l'air.");
        resultatStr5= QString("Utilisez des méthodes\nbiologiques et des pièges\npour contrôler les\nravageurs sans recourir\nsystématiquement aux\npesticides.");
        resultatStr6= QString("1. Tavelure : \nTavelure des pommiers.\n2. Chancre : \nChancre des cerisiers.\n3. Feu bactérien  : \nFeu bactérien des poiriers.");
        resultatStr7= QString("Il est crucial de surveiller\nrégulièrement vos arbres\nfruitiers pour détecter\nrapidement tout signe de\nmaladie ou de ravageur.\nAdoptez des pratiques de\ngestion intégrée des\nravageurs (GIR) pour\nminimiser l'utilisation de\npesticides chimiques. ");
        resultatStr8= QString("-Privilégiez des\npesticides naturels,\ntels que les huiles\nessentielles.\n"
                              "-Utilisez des\nherbicides sélectifs pour\nle contrôle des\nmauvaises herbes.\n"
                              "-Utilisez des fongicides\npour prévenir ou\ntraiter les maladies\nfongiques.");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else if(ui->pconseil->text()=="ornement")
    {
        QString t= QString("Les ornements");
        QString m= QString("Les maladies courantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Sélectionnez des variétés\nqui sont résistantes aux\nmaladies courantes dans\nvotre région.");
        resultatStr2 = QString("Assurez-vous de planter\ndes ornements adaptés\naux conditions de votre\nferme en termes de\nsoleil, d'ombre,de type\nde sol et de climat.");
        resultatStr3= QString("Considérez la taille mature\ndes plantes pour éviter la\nsurpopulation à mesure\nqu'elles grandissent.");
        resultatStr4= QString("Plantez certaines\nornements dans des\nconteneurs pour une\nmobilité et une flexibilité\naccrues.");
        resultatStr5= QString("Choisissez des plantes qui\nattirent la faune locale,\ncomme les papillons ou\nles oiseaux.");
        resultatStr6= QString("1. Rouille : \nRouille sur les asters.\n2. Virus des Plantes  : \nMosaïque des bégonias.\n3. Nécrose Foliaire   : \nNécrose foliaire sur les\nérables.");
        resultatStr7= QString("Préférez des méthodes\nmécaniques comme le\ndésherbage manuel,\nl'utilisation de paillis\nou de bâches pour réduire\nla dépendance aux \nherbicides chimiques.");
        resultatStr8= QString("-Utilisez des insecticides\nchimiques tels que le\nmalathion et biologique\ntels que les nématodes\nbénéfiques.\n"
                              "-Utilisez des herbicides\nchimiques,comme le\nglyphosate.\n"
                              "-Utilisez des fongicides\nchimiques tels que le\nchlorothalonil et\nbiologiques à base de\ncuivre...");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else if(ui->pconseil->text()=="aromatique")
    {
        QString t= QString("Les aromatiques");
        QString m= QString("Les maladies courrantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Choisissez un\nemplacement ensoleillé\npour la plupart des\nherbes aromatiques.");
        resultatStr2 = QString("Assurez-vous d'un bon\ndrainage, car la plupart\ndes herbes n'aiment pas\nles sols trop humides.");
        resultatStr3= QString("Taillez régulièrement\npour encourager une\ncroissance buissonnante\net une production\nconstante.");
        resultatStr4= QString("Arrosez modérément,\ncar la plupart des herbes\nn'aiment pas les sols\nconstamment humides.");
        resultatStr5= QString("Récoltez régulièrement\npour encourager une\ncroissance continue et\nmaintenir la qualité des\nfeuilles.");
        resultatStr6= QString("1. Taches foliaires : \nTaches sur l'origan.\n2. Pourriture des tiges : \nPourriture sur le thym.\n3. Moisissure : \nMoisissure grise sur la\nlavande.");
        resultatStr7= QString("Il est important de\nsurveiller régulièrement\nvos herbes pour détecter\ntout signe de maladie ou\nd'infestation,et d'adopter\ndes pratiques de jardinage\nsaines pour minimiser\nles risques.");
        resultatStr8= QString("-L'huile de neem est\nconnue pour ses\npropriétés insecticides\net fongicides.\n"
                              "-La diatomée terre\nagit en absorbant les\nhuiles et cires de la\ncuticule des insectes.\n"
                              "-Les savons insecticides\npeuvent être utilisés\npour lutter contre les\ninsectes nuisibles.");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else if(ui->pconseil->text()=="cereale")
    {
        QString t= QString("Les cereales");
        QString m= QString("Les maladies courantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Respectez la densité de\nsemis recommandée pour\nune croissance optimale.");
        resultatStr2 = QString("Assurez-vous d'une \nrrigation adéquate, en\nparticulier pendant les\nphases critiques de\ncroissance.");
        resultatStr3= QString("Contrôlez les mauvaises\nherbes pour éviter la\ncompétition avec les\ncéréales.");
        resultatStr4= QString("Récoltez les céréales\nau bon stade de maturité\npour assurer la qualité.");
        resultatStr5= QString("Stockez les céréales\ndans des conditions\nappropriées pour éviter\nles problèmes de qualité.");
        resultatStr6= QString("1. Septoriose  : \nSeptoriose de l'avoine.\n2. Fusariose : \nFusariose de l'épi chez\nl'orge.\n3. Taches Foliaires  : \nTaches foliaires du riz.");
        resultatStr7= QString("Il est crucial de maintenir\nune surveillance fréquente\nde vos champs de\ncéréales afin de détecter\nrapidement tout signe\nde maladie ou d'infestation\npar des ravageurs.En\noptant pour des pratiques\nde gestion intégrée des\nravageurs (GIR),vous\nréduisez la nécessité\nd'avoir recours à des\npesticides chimiques.");
        resultatStr8= QString("-Imidaclopride : Un\ninsecticide utilisé pour\nlutter contre les insectes\nqui attaquent les racines.\n"
                              "-Triazoles : Utilisés pour\ncontrôler les maladies\nfongique tels que\nla rouille.\n"
                              "-Atrazine : Un herbicide\nutilisé pour le contrôle\ndes mauvaises herbes\ndans les cultures\nde maïs.");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else if(ui->pconseil->text()=="fourrage")
    {
        QString t= QString("Les fourrages");
        QString m= QString("Les maladies courrantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Adoptez des pratiques\nagricoles durables pour\nminimiser l'impact\nenvironnemental.");
        resultatStr3=QString("Effectuez des coupes\nrégulières pour\nencourager une\ncroissance saine et la\nproduction de qualité.");
        resultatStr2= QString("Respectez les\nrecommandations\npour la densité de semis\net la profondeur de\nplantation en fonction du\ntype de fourrage choisi.");
        resultatStr4= QString("Assurez-vous que les\néquipements de récolte,\ntels que les faucheuses ou\nles andaineurs, sont en\nbon état pour maximiser\nl'efficacité de la récolte.");
        resultatStr5= QString("Gérez correctement les\nrésidus de culture\naprès la récolte pour\npréparer le terrain pour\nla saison suivante.");
        resultatStr6= QString("1. Fusariose  : \nFusariose du ray-grass.\n2. Anthracnose : \nAnthracnose de la luzerne.\n3. Mildiou  : \nMildiou du trèfle rouge.");
        resultatStr7= QString("La vigilance constante\nvis-à-vis de la santé des\ncultures de fourrages est\nune pratique indispensable.\nEn optant pour des\nstratégies de gestion\nintégrée des ravageurs,\non favorise une approche\néquilibrée qui limite lan\nécessité de recourir à des\npesticides chimiques.");
        resultatStr8= QString("-Privilégiez des\nnématocides pour le\ncontrôle des nématodes du sol.\n"
                              "-Utilisez des herbicides\nsélectifs pour le contrôle\ndes mauvaises herbes.\n"
                              "-Utilisez des insecticides\nspécifiques si des\nravageurs insectes\nposent problème.");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else if(ui->pconseil->text()=="oleagineux")
    {
        QString t= QString("Les oleagineux");
        QString m= QString("Les maladies courrantes");
        QString p= QString("Les pesticides");
        resultatStr1=QString("Récoltez au stade de\nmaturité approprié pour\nmaximiser le rendement\net la qualité.");
        resultatStr2 = QString("Assurez-vous d'un sol\nbien drainé et riche\nen matière organique.");
        resultatStr3= QString("Choisissez des cultures\nadaptées à votre objectif\n(huile, graines, etc.)");
        resultatStr4= QString("Assurez-vous d'une\nirrigation adéquate,\nsurtout pendant les\npériodes cruciales de\ndéveloppement.");
        resultatStr5= QString("Respectez les\nrecommandations\nd'espacement pour\nfavoriser une croissance\noptimale.");
        resultatStr6= QString("1. Septoriose : \nprovoquée par Septoria_l.\n2. Kabatiellose : \nProvoqué par Kabatiella_l.\n3. Fusariose  : \nProvoquée par Fusarium.");
        resultatStr7= QString("Il est essentiel de\nsurveiller régulièrement\nles cultures oléagineuses,\nd'adopter des pratiques\nagricoles durables et\nd'utiliser des pesticides\navec précaution pour\nminimiser les risques pour\nla santé humaine et \nl'environnement.");
        resultatStr8= QString("-Privilégiez des\nnématocides à base de\nfipronil pour l'arachide\npar exemple.\n"
                              "-Utilisez des herbicides\nà base de glyphosate\npour le colza par\nexemple.\n"
                              "-Utilisez des fongicides\nà base de tébuconazole\npour le contrôle de\nl'anthracnose par\nexemple.");
        nouvelleFenetre.setLabelText(t);
        nouvelleFenetre.setLabelText1(resultatStr1);
        nouvelleFenetre.setLabelText2(resultatStr2);
        nouvelleFenetre.setLabelText3(resultatStr3);
        nouvelleFenetre.setLabelText4(resultatStr4);
        nouvelleFenetre.setLabelText5(resultatStr5);
        nouvelleFenetre.setLabelText6(resultatStr6);
        nouvelleFenetre.setLabelText7(resultatStr7);
        nouvelleFenetre.setLabelText8(resultatStr8);
        nouvelleFenetre.setLabelTextm(m);
        nouvelleFenetre.setLabelTextp(p);
        nouvelleFenetre.exec();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("essayer de nouveau"),QObject::tr("type invalide."),QMessageBox::Cancel);
    }

}

/* void MainWindow::on_map_clicked()
{    map *fenetremap;
     fenetremap->exec();


}
*/

void MainWindow::on_pushButton_50_clicked()
{
    if (fenetreMaintenance)
    {
        // Assurez-vous que la fenêtre maintenance existe
        fenetreMaintenance->enregistrerEtAfficher();
        fenetreMaintenance->show();

    }
    else
       {
           // Si la fenêtre maintenance n'existe pas, créez-la et affichez-la
           fenetreMaintenance = new maintenance(this);
           fenetreMaintenance->show();
       }
}
/*void MainWindow::on_map_clicked()
{ if (fenetremap)
    {
        // Ensure the map window exists
        fenetremap->show();

        QTimer::singleShot(0, this, [this]() {
            QString machinePosition = ui->position->currentText();
            QString machineSerie = ui->serie->text();
            fenetremap->updateLabelFromMachine(machinePosition, machineSerie);
        });
    }
    else
    {
        // If the map window doesn't exist, create and show it
        fenetremap = new map(this);
        fenetremap->show();

        QTimer::singleShot(0, this, [this]() {
            QString machinePosition = ui->position->currentText();
            QString machineSerie = ui->serie->text();
            fenetremap->updateLabelFromMachine(machinePosition, machineSerie);
        });
    }
    if (!fenetremap) {
            fenetremap = new map(this);
        }
        fenetremap->show();
        QString machinePosition = ui->position->currentText();
            QString machineSerie = ui->serie->text();
            fenetremap->updateLabelFromMachine(machinePosition, machineSerie);
 //map *mapWindow = new map(this);

}*/

