#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animaux.h"
#include <QMessageBox>
#include <QApplication>
#include<QObject>
#include<QDebug>
#include<QTabWidget>
#include<dialog.h>
#include"dialog1.h"
#include"arduino.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableauanimaux->setModel(A.afficher());
    int ret=AA.connect_arduino();
        switch(ret)
        {
        case (0):qDebug()<<"arduino is avilble and connected to :"<<AA.getarduino_port_name();
            break;
        case (1):qDebug()<<"arduino is avilble but not connected to :"<<AA.getarduino_port_name();
            break;
        case (-1):qDebug()<<"arduino is not avilble ";
        }
        QObject::connect(AA.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_valider_clicked()
{
    int identifiant=ui->lineEdit_id->text().toInt();
    QString categorie=ui->lineEdit_ca->text();
    float masse=ui->lineEdit_ma->text().toFloat();
    float taille=ui->lineEdit_taille->text().toFloat();
    QString etat=ui->lineEdit_etat->text();
    QString ida=ui->lineEdit_ida->text();
    //controle de saisie
    if(identifiant<100000||identifiant>999999)
    {

        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("l'identifiant doit contenir 6 chiffres exactement.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_id->setStyleSheet("QLineEdit { border: 2px solid red; }");
          return;
    }
    else {
        ui->lineEdit_id->setStyleSheet("");
    }
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

     if (ida.isEmpty()){ QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ida ne doit pas etre vide .\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->lineEdit_ida->setStyleSheet("QLineEdit { border: 2px solid red; }");
         return;

     }
     else{
         ui->lineEdit_ida->setStyleSheet("");
     }







int nbr=0;
    QSqlQuery query;
     query.prepare("SELECT * FROM ANNIMAUX WHERE IDENTIFIANT=:IDENTIFIANT");
     query.bindValue(":IDENTIFIANT",ui->lineEdit_id->text());
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
         ui->lineEdit_id->setStyleSheet("QLineEdit { border: 2px solid red; }");
     }
     else{

    animaux A(identifiant,categorie,masse,taille,etat,ida);
      bool test =A.ajouter();
      if (test)

      {
          QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("ajout effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tableauanimaux->setModel(A.afficher());
    }
      else
          QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                      QObject::tr("Ajout non effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}}





void MainWindow::on_pushButton_modifier_clicked()
{
    int identifiant=ui->lineEdit_id->text().toInt();
    QString categorie=ui->lineEdit_ca->text();
    float masse=ui->lineEdit_ma->text().toFloat();
    float taille=ui->lineEdit_taille->text().toFloat();
    QString etat=ui->lineEdit_etat->text();
    QString ida=ui->lineEdit_ida->text();
// controle de saisie
    if(identifiant<100000||identifiant>999999)
    {

        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("l'identifiant doit contenir 6 chiffres exactement.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_id->setStyleSheet("QLineEdit { border: 2px solid red; }");
          return;
    }
    else {
        ui->lineEdit_id->setStyleSheet("");
    }
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

     if (ida.isEmpty()){ QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("ida ne doit pas etre vide .\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->lineEdit_ida->setStyleSheet("QLineEdit { border: 2px solid red; }");
         return;

     }
     else{
         ui->lineEdit_ida->setStyleSheet("");
     }










    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM ANNIMAUX WHERE IDENTIFIANT=:IDENTIFIANT");
       query.bindValue(":IDENTIFIANT", identifiant);
       query.exec();

       if (query.next()) {
           int count = query.value(0).toInt();
           if (count > 0) {
      animaux a(identifiant,categorie,masse,taille,etat,ida);
      a.Modifier(identifiant,categorie,masse,taille,etat,ida);
        ui->tableauanimaux->setModel(a.afficher());

            }
           else {
                   QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                               QObject::tr("ID N'EXISTE PAS.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}

    }   }


void MainWindow::on_pushButton_supprimer_clicked()
{
  animaux A1;A1.setidentifiant(ui->lineEdit_supp->text().toInt());
 bool test=A1.supprimer(A1.get_identifiant());
 if (test)
 {
     QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Suppression effectué avec succés.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tableauanimaux->setModel(A.afficher());
}
 else{
     QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                 QObject::tr("Suppression non effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);}}

void MainWindow::on_pushButton_refresh_clicked()
{
  ui->tableauanimaux->setModel(A.afficher());
}
void MainWindow::on_pb_recherche_ich_clicked()
{

        QString critere=ui->critere_rech_acc->currentText();
        QString rech= ui->critere_rech_acc_2->text();

        if(ui->critere_rech_acc_2->text() == "")
            {
                ui->tableauanimaux->setModel(A.afficher());
            }
            else
            {

                  ui->tableauanimaux->setModel(A.chercher(critere,rech));
            }

    }

void MainWindow::on_pushButton_trierid_ich_clicked()
{
    animaux E;

    ui->tableauanimaux->setModel(E.tri());

    bool test=E.tri();
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


void MainWindow::on_pushButton_triernom_ich_clicked()
{

        animaux E;

        ui->tableauanimaux->setModel(E.trinom());

        bool test=E.tri();
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


void MainWindow::on_pushButton_triernom_ich_2_clicked()
{
    animaux E;

    ui->tableauanimaux->setModel(E.tricapacite());

    bool test=E.tri();
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

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPainter>

void MainWindow::on_pushButton_stat_ich_clicked()
{
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        QSqlQueryModel model;
        model.setQuery("SELECT * FROM ANNIMAUX WHERE CATEGORIE='cheval'");
        int number1 = model.rowCount();
        series->append("Mammifères", number1);
        series->setLabelsVisible(true);
        series->slices().at(0)->setLabel("Mammifères");

        model.setQuery("SELECT * FROM ANNIMAUX WHERE CATEGORIE='Oiseaux'");
        int number2 = model.rowCount();
        series->append("Oiseaux", number2);
        series->setLabelsVisible(true);
        series->slices().at(1)->setLabel("Oiseaux");

        model.setQuery("SELECT * FROM ANNIMAUX WHERE CATEGORIE='Reptiles'");
        int number3 = model.rowCount();
        series->append("Reptiles", number3);
        series->setLabelsVisible(true);
        series->slices().at(2)->setLabel("Reptiles");

        model.setQuery("SELECT * FROM ANNIMAUX WHERE CATEGORIE='mouton'");
        int number4 = model.rowCount();
        series->append("Amphibiens", number4);
        series->setLabelsVisible(true);
        series->slices().at(3)->setLabel("Amphibiens");

    int total = number1 + number2 + number3 + number4;

    QString a = QString("cheval" + QString::number((number1 * 100) / total, 'f', 2) + "%");
    QString b = QString("Oiseaux " + QString::number((number2 * 100) / total, 'f', 2) + "%");
    QString c = QString("Reptiles" + QString::number((number3 * 100) / total, 'f', 2) + "%");
    QString d = QString("mouton" + QString::number((number4 * 100) / total, 'f', 2) + "%");



    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage des Animaux selon la Catégorie");
    chart->legend()->setFont(QFont("Arial", 10));


    chart->setBackgroundBrush(QColor("#ffaaff"));

    QtCharts::QChart::AnimationOptions options = QtCharts::QChart::AllAnimations;
    chart->setAnimationOptions(options);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitleFont(QFont("Arial", 25));
    chartView->resize(1000, 500);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);

    chartView->show();
}


#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>


void MainWindow::on_pb_valider_pdf_clicked()
         {
    QString pdf_name = ui->le_pdf_name->text();
       QString name = "C:/Users/21694/Desktop/trvail/Atelier_Connexion" + pdf_name + ".pdf";


       QPrinter printer;
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName(name);


       printer.setOrientation(QPrinter::Landscape);

       QPainter painter;

       if (!printer.isValid()) {
           qWarning("Failed to create PDF printer. Check the output file path.");
           return;
       }

       if (!painter.begin(&printer)) {
           qWarning("Failed to open file. Is it writable?");
           return;
       }




       QFont titleFont("Arial", 20, QFont::Bold);
       QPen titlePen(Qt::black);
       painter.setFont(titleFont);
       painter.setPen(titlePen);
       painter.drawText(0, 30, printer.width(), 50, Qt::AlignCenter, "Liste des Animaux");


       QFont companyFont("Arial", 16, QFont::Bold);
       QPen companyPen(Qt::black);
       painter.setFont(companyFont);
       painter.setPen(companyPen);
       painter.drawText(0, 70, printer.width(), 50, Qt::AlignCenter, "Application : Boss Abdelli ");


       QDateTime currentDateTime = QDateTime::currentDateTime();
       QString dateTimeString = "Exporté le " + currentDateTime.toString("dd/MM/yyyy à hh:mm:ss");
       QFont dateTimeFont("Arial", 12);
       QPen dateTimePen(Qt::black);
       painter.setFont(dateTimeFont);
       painter.setPen(dateTimePen);
       painter.drawText(0, 110, printer.width(), 30, Qt::AlignCenter, dateTimeString);

       QSqlQuery query;
       qDebug() << query.exec("SELECT * FROM ANNIMAUX");

       if (query.isActive()) {
           const int tableStartX = 50;
           const int tableStartY = 150;
           const int columnWidth = 120;
           const int columnSpacing = 10;
           const int additionalWidthForFournisseur = 80;
           int currentX = tableStartX;
           int currentY = tableStartY;

           QFont headerFont("Arial", 14, QFont::Bold);
           QFont cellFont("Arial", 12);
           QPen headerPen(Qt::black);
           QPen cellPen(Qt::black);

           painter.setFont(headerFont);
           painter.setPen(headerPen);

           // Lignes horizontales entre les rangées
           painter.drawLine(tableStartX, tableStartY, 10 * (columnWidth + columnSpacing) + tableStartX, tableStartY);
           currentY += 30;

           // Draw table headers avec un fond coloré
           painter.setBrush(QColor(200, 200, 200));
           painter.drawRect(tableStartX, tableStartY, 10 * (columnWidth + columnSpacing), 30);
           QStringList headers = {"IDENTIFIANT", "CATEGORIE", "MASSE", "TAILLE", "ETAT", "IDA"};


           currentX = tableStartX;
           currentY += 30;

           painter.setFont(cellFont);
           painter.setPen(cellPen);

           while (query.next()) {
               // Lignes horizontales entre les rangées
               painter.drawLine(tableStartX, currentY, 10 * (columnWidth + columnSpacing) + tableStartX, currentY);
               for (int column = 0; column < 9; ++column) {
                   int columnWidthWithSpacing = (column == 8) ? columnWidth + columnSpacing + additionalWidthForFournisseur : columnWidth + columnSpacing;
                   painter.drawText(currentX, currentY, columnWidthWithSpacing, 20, Qt::AlignCenter, query.value(column).toString());
                   currentX += columnWidthWithSpacing;
               }
               currentY += 20;
               currentX = tableStartX;
           }
       } else {
           qWarning("Failed to execute SQL query.");
       }

       painter.end();
       QMessageBox::information(nullptr, QObject::tr("Exportation_PDF"),
        QObject::tr("Exportation PDF avec succès\n"
             "Click Cancel to exit."), QMessageBox::Ok);
       ui->le_pdf_name->hide();

       ui->pb_valider_pdf->hide();
       ;}




void MainWindow::on_pushButton_annuler_ich_clicked()
{
    ui->lineEdit_id->setText("");
    ui->lineEdit_ca->setText("");
    ui->lineEdit_ma->setText("");
    ui->lineEdit_taille->setText("");
    ui->lineEdit_etat->setText("");
    ui->lineEdit_ida->setText("");
    ui->lineEdit_id->setStyleSheet("");
    ui->lineEdit_ca->setStyleSheet("");
    ui->lineEdit_ma->setStyleSheet("");
    ui->lineEdit_taille->setStyleSheet("");
    ui->lineEdit_etat->setStyleSheet("");
    ui->lineEdit_ida->setStyleSheet("");
}



void MainWindow::on_pushButton_modifier_2_clicked()
{
    Dialog d;
    d.exec();
}

void MainWindow::on_pushButton_modifier_3_clicked()
{
    Dialog1 d1;
    d1.exec();
}

void MainWindow::on_pushButton_stat_ich_2_clicked()
{
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        QSqlQueryModel model;
        model.setQuery("SELECT * FROM ANNIMAUX WHERE IDA='Viande'");
        int number1 = model.rowCount();
        series->append("Viande", number1);
        series->setLabelsVisible(true);
        series->slices().at(0)->setLabel("Viande");

        model.setQuery("SELECT * FROM ANNIMAUX WHERE IDA='Graines'");
        int number2 = model.rowCount();
        series->append("Graines", number2);
        series->setLabelsVisible(true);
        series->slices().at(1)->setLabel("Graines");

        model.setQuery("SELECT * FROM ANNIMAUX WHERE IDA='Insectes'");
        int number3 = model.rowCount();
        series->append("Insectes", number3);
        series->setLabelsVisible(true);
        series->slices().at(2)->setLabel("Insectes");

        model.setQuery("SELECT * FROM ANNIMAUX WHERE IDA='Plante'");
        int number4 = model.rowCount();
        series->append("Plante", number4);
        series->setLabelsVisible(true);
        series->slices().at(3)->setLabel("Plante");

    int total = number1 + number2 + number3 + number4;

    QString a = QString("Viande" + QString::number((number1 * 100) / total, 'f', 2) + "%");
    QString b = QString("Graines " + QString::number((number2 * 100) / total, 'f', 2) + "%");
    QString c = QString("Insectes" + QString::number((number3 * 100) / total, 'f', 2) + "%");
    QString d = QString("Plante" + QString::number((number4 * 100) / total, 'f', 2) + "%");



    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage des Animaux selon l'IDA");
    chart->legend()->setFont(QFont("Arial", 10));


    chart->setBackgroundBrush(QColor("#ffaaff"));

    QtCharts::QChart::AnimationOptions options = QtCharts::QChart::AllAnimations;
    chart->setAnimationOptions(options);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitleFont(QFont("Arial", 25));
    chartView->resize(1000, 500);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);

    chartView->show();
}
void MainWindow::update_label()
{
    data=AA.read_from_arduino();
    if(data=="1")
    {
        QMessageBox::critical(nullptr, QObject::tr("ok"),
                    QObject::tr("animal passed"), QMessageBox::Cancel);
    }

}
