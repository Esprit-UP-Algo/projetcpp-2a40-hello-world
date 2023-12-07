#include <QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include "arduino.h"
#include "machine.h"
#include <QDebug>
arduino::arduino()
{
serial = new  QSerialPort();

}
arduino::~arduino() {
    delete serial;
}

int arduino::connect_arduino()
{
    foreach(const QSerialPortInfo &serial_port_info,QSerialPortInfo::availablePorts())
    {if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())

       {if (serial_port_info.vendorIdentifier() ==arduino_uno_vendor_id && serial_port_info.productIdentifier()==arduino_uno_producy_id)

           {arduino_is_avaible=true;
            ardino_port_name = serial_port_info.portName();}}}
           qDebug() << "Arduino found!";

                    qDebug() << "Port name: " << ardino_port_name;
    qDebug()<<"arduino_port_name is:"<<getarduino_portname();
    if(arduino_is_avaible){
        serial->setPortName(getarduino_portname());
        if(serial->open(QSerialPort::ReadWrite))
        {serial->setBaudRate(QSerialPort::Baud9600);
         serial->setDataBits(QSerialPort::Data8);
         serial->setParity(QSerialPort::NoParity);
         serial->setStopBits(QSerialPort::OneStop);
         serial->setFlowControl(QSerialPort::NoFlowControl);
         qDebug() << "Arduino connected successfully!";
         return 0;
        }
     }
    qDebug() << "Arduino not found or unable to connect!";
    return 1;
}
int arduino::close_arduino()
{if (serial->isOpen()){
        serial->close();
        return 0;
    }
  return 1;
}
QByteArray arduino:: read_from_arduino()
{if (serial->isReadable())
{data=serial->readAll();
  return data;
}
    return QByteArray();
}
int arduino::getWateringTimeFromData(const QByteArray &data)
{
    // Convertir les données en chaîne pour faciliter le traitement
    qDebug() << "Données brutes depuis Arduino : " << data;
    QString dataString = QString::fromUtf8(data);


    // Recherchez la première occurrence de "Arrosage pendant" dans les données
    int index = dataString.indexOf("Arrosage pendant");

    if (index != -1)
    {
        // Trouvez le nombre suivant "Arrosage pendant" dans les données
        QRegExp rx("\\d+");
        int pos = rx.indexIn(dataString.mid(index));

        // Si un nombre est trouvé
        if (pos != -1)
        {
            QString numberString = rx.cap(0);
            bool conversionOK;
            int wateringTime = numberString.toInt(&conversionOK);

            if (conversionOK)
            {
                // Retournez le temps d'arrosage
                return wateringTime;
            }
        }
    }

    // Si rien n'est trouvé, retournez -1 pour indiquer une erreur
    return -1;
}

QSerialPort* arduino::getserial()
{
    return serial;
}

QString arduino::getarduino_portname()
{
    return ardino_port_name;
}
int arduino::write_to_arduino(QByteArray d) {
    if (serial->isWritable())
    { serial->write(d);}
            else {
            qDebug()<<"couldn't write to serial";
}
 return 0;
}

/*void arduino::handleDataFromArduino(const QByteArray &data) {
    // Traitement des données
    int tempsArrosageSecondes = getWateringTimeFromData(data);
    qDebug() << "Temps d'arrosage par secondes : " << tempsArrosageSecondes << " secondes";

    // Convertir le temps d'arrosage en heures
    int tempsArrosageHeures = tempsArrosageSecondes / 3600;

    // Mettre à jour la valeur de nb_heures dans l'instance de la classe machine
    myMachine.setnb_heures(myMachine.getnb_heures() + tempsArrosageHeures);

    qDebug() << "Temps d'arrosage reçu : " << tempsArrosageHeures << " heures";

    // Vérifier si la série de la machine commence par "000tunisie" suivi de 4 chiffres
    QString serie = myMachine.getserie();
    qDebug() << "Série de la machine : " << serie;
    qDebug() << "Longueur de la série : " << serie.length();

    if (serie.startsWith("000tunisie") && serie.length() == 14) {
        // Mettre à jour cette valeur dans votre base de données
        QSqlQuery query(database);
        query.prepare("UPDATE machines SET nombre_heure = :nb_heures WHERE serie = :serie");
        query.bindValue(":nb_heures", myMachine.getnb_heures());
        query.bindValue(":serie", serie);

        if (query.exec()) {
            qDebug() << "Heures d'arrosage mises à jour dans la base de données.";
        } else {
            qDebug() << "Échec de la mise à jour des heures d'arrosage dans la base de données.";
        }
    } else {
        qDebug() << "La série de la machine n'est pas dans le bon format pour la mise à jour de nb_heures.";
    }
}*/
