#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>
#include <QString>
#include<QDate>
namespace Ui {
class maintenance;
}

class maintenance : public QDialog
{
    Q_OBJECT

public:
    explicit maintenance(QWidget *parent = nullptr);
     //static void qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a);
    ~maintenance();
    maintenance();
    maintenance(QString,QDate,double);
    void setserie(QString s);
    void setdate(QDate d);
    void setcout(double c);
    QString getserie();
    QDate getdate();
   double getcout();
   void enregistrerEtAfficher();
private slots:
   void on_save_clicked();

private:
    Ui::maintenance *ui;
private:
   QString serie  ;
   QDate date;
   double cout;
};

#endif // MAINTENANCE_H
