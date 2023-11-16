#include "agri.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QObject>
#include <QPrinter>
#include <QTextDocument>
agri::agri()
{
    ida="";
    type="";
    datep=QDate (1, 1, 1);
    tdp="";
    pda=0.0;
    pdv=0.0;
    quantite=0;
}
agri::agri (QString ida, QString type, QString tdp, QDate datep ,float pda, float pdv ,int quantite)
{
    this->type=type;
    this->tdp=tdp;
    this->ida=ida;
    this->pda=pda;
    this->pdv=pdv;
    this->quantite=quantite;
    this->datep=datep;
    qDebug()<<"type: "<< type;
}

void agri:: settype(QString n){type=n;}
void agri:: settdp(QString n1){tdp=n1;}
void agri:: setida(QString n2){ida=n2;}
void agri:: setdatep(QDate n3){datep=n3;}
void agri:: setpda(float n4){pda=n4;}
void agri:: setpdv(float n5){pdv=n5;}
void agri:: setquantite(int n6){quantite=n6;}


QString agri:: gettype(){return type;}
QString agri:: gettdp(){return tdp;}
QString agri:: getida(){return ida;}
QDate agri:: getdatep(){return datep;}
float agri:: getpda(){return pda;}
float agri:: getpdv(){return pdv;}
int agri:: getquantite(){return quantite;}

bool agri::ajouter()
{
    QSqlQuery query;
    QDateTime datetime=QDateTime::currentDateTime();
    QString res= QString::number(pda);
    QString res1= QString::number(pdv);
    QString res2= QString::number(quantite);
    query.prepare("INSERT INTO agri(IDA,TYPE,TDP,DATEP,PDA,PDV,QUANTITE) VALUES(:ida,:type,:tdp,:datep,:pda,:pdv,:quantite)");
    query.bindValue(":ida",ida);
    query.bindValue(":type",type);
    query.bindValue(":tdp",tdp);
    query.bindValue(":datep",datep);
    query.bindValue(":pda",res);
    query.bindValue(":pdv",res1);
    query.bindValue(":quantite",res2);
    //qDebug()<<"requete sql: "<<query.exec();
    return query.exec();
}
bool agri:: supprimer(QString ida)
{
    QSqlQuery checkQuery;
    QSqlQuery query;
    checkQuery.prepare("SELECT IDA FROM agri where ida=:ida");
    checkQuery.bindValue(0, ida);
    if (checkQuery.exec()&&checkQuery.next())
    {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("Delete from agri where ida=:ida");
        deleteQuery.bindValue(0, ida);
        return deleteQuery.exec();
    }
    else
        return false;
}


QSqlQueryModel* agri::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;
        model->setQuery("SELECT ida,type,tdp,datep,pda,pdv,quantite FROM agri ORDER BY DATEP ASC");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("type de plante"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("type_de_pesticide"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("d_d_plantation"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("prix d'achat"));
        model->setHeaderData(5, Qt::Horizontal,QObject::tr("prix de vente"));
        model->setHeaderData(6, Qt::Horizontal,QObject::tr("quantite de prod"));
    return model;
}
bool agri::updateData( QString ida)
{
    QSqlQuery query;
    QString res= QString::number(pda);
    QString res1= QString::number(pdv);
    QString res2= QString::number(quantite);
    query.prepare("UPDATE agri SET TYPE=:type,TDP=:tdp,DATEP=:datep,PDA=:pda,PDV=:pdv,QUANTITE=:quantite  WHERE IDA=:ida");
    query.bindValue(":type",type);
    query.bindValue(":tdp", tdp);
    query.bindValue(":datep",datep);
    query.bindValue(":pda",res);
    query.bindValue(":pdv", res1);
    query.bindValue(":quantite", res2);
    query.bindValue(":ida", ida);
    //qDebug()<<"requete sql: "<<query.exec();
    return query.exec();
}
QSqlQueryModel* agri::rechercherPartype(QString ida)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM agri WHERE IDA = :ida");
    query.bindValue(":ida", ida);

    if (query.exec())
    {
        QSqlQueryModel *searchResultModel = new QSqlQueryModel();
        searchResultModel->setQuery(query);
        return searchResultModel;

    }
    else
        return nullptr;
}

bool agri::exporterPdf(const QString &nomFichier)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nomFichier);

    QTextDocument document;

    // Obtenez les données à partir de votre modèle SQL (assurez-vous que le modèle inclut les colonnes "type", "quantite", "pdv")
    QSqlQuery query;
    query.prepare("SELECT type, quantite, pdv FROM agri");

    if (query.exec())
    {
        QString html = "<html><body><table border='1'><tr><th>Type</th><th>Quantité</th><th>PDV</th></tr>";

        while (query.next())
        {
            QString type = query.value(0).toString();
            QString quantite = query.value(1).toString();
            QString pdv = query.value(2).toString();
            html += "<tr>";
            html += "<td>" + type + "</td>";
            html += "<td>" + quantite + "</td>";
            html += "<td>" + pdv + "</td>";
            html += "</tr>";
        }

        html += "</table></body></html>";

        document.setHtml(html);
        document.print(&printer);

        //return true; // L'exportation PDF a réussi
    }
    return true;
}

float agri::calculbenefice()
{
    QSqlQuery query("SELECT ida, quantite, pdv, pda FROM agri");
    double beneficeTotal = 0.0;
    while (query.next())
    {
            QString nom = query.value(0).toString();
            int quantite = query.value(1).toInt();
            float pdv = query.value(2).toDouble();
            float pda = query.value(3).toDouble();

            // Calculer le bénéfice pour chaque plante
            float beneficePlante = (quantite * pdv) - pda;
            beneficeTotal += beneficePlante;
    }
    return beneficeTotal;
}
