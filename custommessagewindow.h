#ifndef CUSTOMMESSAGEWINDOW_H
#define CUSTOMMESSAGEWINDOW_H


#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCalendarWidget>
#include <QDate>
#include <QDebug>

class CustomMessageWindow : public QMainWindow {
    Q_OBJECT

public:
    CustomMessageWindow(QWidget *parent = nullptr);

private slots:

  void updateTableDataFromSQL(QTableWidget *tableWidget);
private:
    QString currentSeason;
    QString currentType;
};

#endif // CUSTOMMESSAGEWINDOW_H
