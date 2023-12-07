#include "arduino.h"
#include <QDebug>
arduino::arduino()
{
    serial=new QSerialPort;
}
QString arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *arduino::getserial()
{
   return serial;
}
int arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_produducy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug()<< "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray arduino::read_from_arduino()
{
    if(serial->isReadable())
    {
         data=serial->readAll(); //récupérer les données reçues

    }
    return data;
}


 int arduino::write_to_arduino(QByteArray d)
 {
     if(serial->isWritable())
     {
        serial->write(d);
     }
     else
     {
         qDebug() <<"couldn't write to serial! ";
     }
     return (0);
 }
int arduino::gethumiditeFromData(const QByteArray &data)
 {
    qDebug() << "Raw Data: " << data;
     // Convertir les données en chaîne pour faciliter le traitement
     QString datastring = QString::fromUtf8(data);
     qDebug() << "Data String: " << datastring;
     // Recherchez la première occurrence de "Arrosage pendant" dans les données
     int index = datastring.indexOf("humidite");
     qDebug()<<"index: "<<index;
     if (index != -1)
     {
         // Trouvez le nombre suivant "Arrosage pendant" dans les données
         QRegExp rx("\\d+");
         int pos = rx.indexIn(datastring.mid(index));
         qDebug()<<"pos: "<<pos;

         // Si un nombre est trouvé
         if (pos != -1)
         {
             QString numberString = rx.cap(0);
             bool conversionOK;
             int humidite = numberString.toInt(&conversionOK);
             qDebug()<<"humidite1: "<<humidite;
             if (conversionOK)
             {
                 // Retournez le temps d'arrosage
                 return humidite;
             }
         }
     }

     // Si rien n'est trouvé, retournez -1 pour indiquer une erreur
     return -1;
 }
