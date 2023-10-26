#ifndef AFFICHE_H
#define AFFICHE_H
#include "agri.h"
#include <QDialog>

namespace Ui {
class affiche;
}

class affiche : public QDialog
{
    Q_OBJECT

public:
    explicit affiche(QWidget *parent = nullptr);
    void setagri(agri a);
    ~affiche();

private:
    Ui::affiche *ui;
};

#endif // AFFICHE_H
