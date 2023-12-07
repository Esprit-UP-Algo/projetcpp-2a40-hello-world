#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "benefice.h"
#include "conseil.h"
#include "agri.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include<iostream>
#include <QSqlQuery>
#include <QtCharts>
#include <QtSql>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    QRegularExpression regex1("^agri\\d+"); // controle de saisie mta3 id
    ui->setupUi(this);
    ui->table->setModel(a.afficher());
    showstat(); // fonction mta3 statistics
    int ret=ar.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"Arduino is available and connected to: "<< ar.getarduino_port_name();
        break;
    case(1):qDebug()<<"Arduino is available but not connected to: "<< ar.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
    }
    //hedhom les controles de saisie
    ui->quantite->setValidator(new QIntValidator (0,300,this));
    ui->id->setValidator(new QRegularExpressionValidator(regex1,this));
    ui->prix_achat->setValidator(new QDoubleValidator(this));
    ui->prix_vente->setValidator(new QDoubleValidator(this));
    // lahna khtr khadma b groupbox fil type w pesticide
    ui->type->addItem("");
    ui->pesticide->addItem("");

    ui->type->setItemData(0, QVariant(), Qt::UserRole - 1);
    ui->pesticide->setItemData(0, QVariant(), Qt::UserRole - 1);

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


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked() // hedhy ki tinzil al bouton ajouter
{
    bool test;
    QString type=ui->type->currentText();
    QString tdp=ui->pesticide->currentText();
    QString ida=ui->id->text();
    float pdv=ui->prix_vente->text().toFloat();
    float pda=ui->prix_achat->text().toFloat();
    int quantite=ui->quantite->text().toInt();
    QDate datep = ui->date->date();
    agri a(ida,type,tdp,datep,pda,pdv,quantite);
    test=a.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
        ui->table->setModel(a.afficher());
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("ajout non effectué.\n "
                                        "click cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_button_clients_clicked()
{
    ui->button_animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet(" QPushButton { background-color:#84B7A4  ;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E ;}");
    ui->button_machines->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_machines_clicked()
{
    ui->button_animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet(" QPushButton { background-color:#7DB5A2;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E ;}");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_employ_clicked()
{
    ui->button_animaux->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ; }");
    ui->button_employ->setStyleSheet(" QPushButton { background-color:#73B19B;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_animaux_clicked()
{
    ui->button_animaux->setStyleSheet(" QPushButton { background-color:#64A991;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E   ;}");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E ; }");
    ui->button_agri->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_button_agri_clicked()
{
    ui->button_animaux->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_clients->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E  ;}");
    ui->button_machines->setStyleSheet("border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E   ;}");
    ui->button_employ->setStyleSheet(" border-radius: 10px; font: 14pt Yu Gothic UI;font-weight: bold;color: #28322E ; }");
    ui->button_agri->setStyleSheet(" QPushButton { background-color:#519B80;border: 1px white;border-radius: 10px;font: 18pt Yu Gothic UI;font-weight: bold;color: #28322E; }");
}

void MainWindow::on_suppression_clicked() // hedhy ki tnzl al icone poubelle mta3 suppression
{
    agri a1;
    a1.setida(ui->idsupp->text());
        bool test=a1.supprimer(a1.getida());
        if(test)
        {
            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\nClick Cancel to exit."),QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Suppression non effectuée.\nClick Cancel to exit."),QMessageBox::Cancel);
        }
        ui->table->setModel(a.afficher());

}

void MainWindow::on_modifier_clicked() // hedhy ki tnzl al modifier
{
    agri a;
        a.setida(ui->id->text());
        a.settype(ui->type->currentText());
        a.settdp(ui->pesticide->currentText());
        a.setpda( ui->prix_achat->text().toFloat());
        a.setpdv( ui->prix_vente->text().toFloat());
        a.setquantite(ui->quantite->text().toInt());
        a.setdatep(ui->date->date());

            bool success = a.updateData(a.getida());

            if (success)
            {
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("mise a jour  effectuer.\n""click cancel to exit."),QMessageBox::Cancel);
                 ui->table->setModel(a.afficher());
            }
            else
            {

                    QMessageBox::critical(this, tr("Échec de l'update"), tr("La mise à jour des données a échoué."));
            }
}

void MainWindow::on_pdf_clicked() //hedhy ki tnzl al icone mta3 exportation
{
    QString nomFichierPdf = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "Fichiers PDF (*.pdf)");

        if (!nomFichierPdf.isEmpty()) {
            bool exportReussi = a.exporterPdf(nomFichierPdf);

            if (exportReussi) {
                QMessageBox::information(this, "Exportation PDF réussie", "Les données ont été exportées en PDF.");
            } else {
                QMessageBox::critical(this, "Échec de l'exportation PDF", "L'exportation des données en PDF a échoué.");
            }
        }
}


void MainWindow::on_rech_clicked() //hedhy ki tnzl al icone mta3 recherche
{
    agri a;
      a.setida(ui->idsupp->text());
      QSqlQueryModel *result = a.rechercherPartype(a.getida());
      if (result && result->rowCount() > 0)
      {
           ui->table->setModel(result);
           QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Recherche effectuée.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
      }
      else
      {

           QMessageBox::critical(this, tr("Échec de la recherche"), tr("La recherche a échoué."));
      }
}

void MainWindow::showstat() //hedhy fonction mta3 statistiques
{
    QString sqlQuery = "SELECT TYPE, SUM(QUANTITE) AS quantitetotale FROM agri GROUP BY TYPE";
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
          QListWidget *chartContainer = ui->chartContainer;
          QVBoxLayout *layout = new QVBoxLayout(chartContainer);
          layout->addWidget(chartView);

}



void MainWindow::on_calculbenefice_clicked() // hedhy ki tinzil ala bouton mktoub fih benefice
{
    double beneficeTotal = a.calculbenefice();

        // Créez une instance de la nouvelle fenêtre
        benefice( nouvelleFenetre);

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
// hedhy tab3a metier 2 mt3y
// fma conseil.cpp tab3a metier 2 mt3y
void MainWindow::on_pushButton_clicked() // hedha ki tinzil ala hak il lampe baad matiktib type de plante fil qlineedit illi mktoub fiha conseil
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

void MainWindow::on_pushButton_2_clicked() // hedha bouton mt3 arduino
{
    QString id;
    QStringList liste;
    ar.write_to_arduino("1");
    //QThread::msleep(2000);
    QByteArray datafromarduino= ar.read_from_arduino();
    if(!datafromarduino.isEmpty())
        qDebug()<<"avant traitement: "<< datafromarduino;
    int humidity= ar.gethumiditeFromData(datafromarduino);
    qDebug ()<<"humidite recu: "<<humidity;

    if((400<humidity)&&(humidity<500))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'legumes' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);
            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les légumes sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else if((500<humidity)&&(humidity<600))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'fruits' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);
            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les fruits sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else if((600<humidity)&&(humidity<700))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'oleagineux' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);
            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les oleagineux sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else if((700<humidity)&&(humidity<800))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'ornement' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);
            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les ornements sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else if((800<humidity)&&(humidity<900))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'fourrage' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);
            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les fourrages sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else if((900<humidity)&&(humidity<1000))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'aromatique' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);
            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les aromatiques sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    else if((1000<humidity)&&(humidity<1030))
    {
        QSqlQuery query;
        query.prepare("SELECT IDA FROM agri WHERE TYPE LIKE 'cereale' ");

        if (query.exec()) {
            while (query.next())
            {
                QString id = query.value(0).toString();
                liste.append(id);

            }
        }
        else
        {
        qDebug() << "Échec de l'exécution de la requête SQL. Type d'erreur : " << query.lastError().type();
        }
        ui->arrosage->setText(liste.join(", "));
        QMessageBox::information(nullptr, QObject::tr("Arrosage automatique"), QObject::tr("Les cereales sont arrosés automatiquement.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }

}

