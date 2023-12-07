#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include"machine.h"
class arduino
{
public:

    arduino();
    ~arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray d);
    QByteArray read_from_arduino();
    QSerialPort* getserial();
    QString getarduino_portname();
    void setDatabase(QSqlDatabase& db);
   int getWateringTimeFromData(const QByteArray &data);
   void handleDataFromArduino(const QByteArray &data);
private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString ardino_port_name;
    bool arduino_is_avaible;
    QByteArray data;


};

#endif // ARDUINO_H
