#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>

class Client
{
private:
    QString nom, prenom, id, mail, tel, rech;
    QDate date;

public:
    void setnom(QString n);
    void setprenom(QString n);
    void setid(QString n);
    void setmail(QString n);
    void setdate(QDate n);
    void settel(QString n);
    void setrech (QString n);
    QString get_nom();
    QString get_prenom();
    QString get_id();
    QString get_mail();
    QDate get_date();
    QString get_tel();
    QString get_rech();
    Client();
};

#endif // CLIENT_H
