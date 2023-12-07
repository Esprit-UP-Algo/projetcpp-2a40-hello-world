#ifndef BENEFICE_H
#define BENEFICE_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class benefice;
}

class benefice : public QDialog
{
    Q_OBJECT

public:
    explicit benefice(QWidget *parent = nullptr);
    ~benefice();
    void setLabelText(const QString &text);
    void setBeneficeTotalText(const QString& text);


private:
    Ui::benefice *ui;
};

#endif // BENEFICE_H



