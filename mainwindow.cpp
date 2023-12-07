#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QDebug>
#include<QtCharts>
#include<QtSql>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include "review.h"
#include "ui_review.h"
#include <QTextStream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QSerialPort>
#include <QSerialPortInfo>


QSerialPort serial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
displayTableView();



   ui->lineEdit_id->setPlaceholderText("xxxxxx");
    ui->lineEdit_nom->setPlaceholderText("Nom");
    ui->lineEdit_prenom->setPlaceholderText("Prenom");
   ui->lineEdit_tel->setPlaceholderText("xx xxx xxx");
    ui->lineEdit_mail->setPlaceholderText("email@adresse.com");
    ui->lineEdit_rech->setPlaceholderText("Chercher");


    // Contrôle le champ de téléphone
    QRegExp rxTelephone("^(2|4|5|7|9)[0-9]{1} [0-9]{3} [0-9]{3}$");
    QValidator *telValidator = new QRegExpValidator(rxTelephone, this);
    ui->lineEdit_tel->setValidator(telValidator);

    // Controle le champ d'identifiant
        QIntValidator *intValidator = new QIntValidator(0, 999999, this);
        ui->lineEdit_id->setValidator(intValidator);

    // Controle le champ de nom et prenom
        QRegExp rxNom("^[A-Z][a-zA-Z ]*$");  // Expression régulière pour le nom avec espaces
        QRegExp rxPrenom("^[A-Z][a-zA-Z ]*$");  // Expression régulière pour le prénom avec espaces

        QValidator *nomValidator = new QRegExpValidator(rxNom, this);
        QValidator *prenomValidator = new QRegExpValidator(rxPrenom, this);

        ui->lineEdit_nom->setValidator(nomValidator);
        ui->lineEdit_prenom->setValidator(prenomValidator);

    // Controle le champ de mail
        QRegExp rxEmail("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");
        QValidator *emailValidator = new QRegExpValidator(rxEmail, this);
        ui->lineEdit_mail->setValidator(emailValidator);


        connect(ui->pb_review, SIGNAL(clicked()), this, SLOT(on_pb_review_clicked()));

        // Initialize QSerialPort
        serial = new QSerialPort(this);
        serial->setPortName("COM7");  // Set your correct port name
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->open(QIODevice::ReadOnly);

        // Connect the readyRead signal to the processSerialData slot
        connect(serial, SIGNAL(readyRead()), this, SLOT(processSerialData()));

        // You can remove the following line, as it duplicates the connection
        // connect(serial, SIGNAL(readyRead()), this, SLOT(readSerial()));



}

MainWindow::~MainWindow()
{

    delete ui;

}
void MainWindow::displayTableView()
{
    ui->tableView->setModel(C.afficher());
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_pb_ajouter_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    int id = ui->lineEdit_id->text().toInt();
    QString mail = ui->lineEdit_mail->text();
    QDate date = ui->dateEdit->date();
    QString tel = ui->lineEdit_tel->text();

    Client C(nom, prenom, mail, id, tel, date);
    bool ajoutReussi = C.ajouter();

    if (ajoutReussi) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué! \nClick cancel to exit."), QMessageBox::Cancel);

        // Refresh the QTableView with the updated data
        ui->tableView->setModel(C.afficher());
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajout failed. \nClick cancel to exit"), QMessageBox::Cancel);
    }
}


void MainWindow::on_pb_supp_clicked()
{
    Client C;
    int id = ui->lineEdit_rech->text().toInt();
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

void MainWindow::on_pb_modif_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    int id = ui->lineEdit_id->text().toInt();
    QString mail = ui->lineEdit_mail->text();
    QDate date = ui->dateEdit->date();
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

void MainWindow::on_pb_afficher_clicked()
{
    ui->tableView->setModel(C.afficher());

    ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
}



void MainWindow::on_pb_tri_clicked()
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
void MainWindow::on_pb_cherch_clicked()
{
    int id = ui->lineEdit_rech->text().toInt();
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

void MainWindow::on_pb_pdf_clicked()
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

void MainWindow::on_pb_stat_clicked()
{
    // Clear le contenu actuel du listWidget
    ui->listWidget->clear();

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
            ui->listWidget->addItem(new QListWidgetItem("Erreur lors de la récupération des statistiques"));
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
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, chartView);
}
void MainWindow::on_pb_review_clicked() //metier zeyda theb khaliha wela nahiha, client yaati review te3o ll application
{
    // Create an instance of the Review class
    Review *reviewDialog = new Review(this);

    // Show the dialog
    reviewDialog->exec();
}

void MainWindow::on_pb_rdvv_clicked() //metier1
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    QString startTimeStr = ui->start->time().toString("hh:mm");
    int id = ui->lineEdit_rech->text().toInt();

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
}

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
}
