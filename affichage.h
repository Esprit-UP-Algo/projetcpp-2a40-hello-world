#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include"machine.h"
#include <QDialog>

namespace Ui {
class affichage;
}

class affichage : public QDialog
{
    Q_OBJECT

public:
    explicit affichage(QWidget *parent = nullptr);
    void setmachine(machine m);
    ~affichage();

private:
    Ui::affichage *ui;
};

#endif // AFFICHAGE_H
