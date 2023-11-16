#ifndef CONSEIL_H
#define CONSEIL_H

#include <QDialog>

namespace Ui {
class conseil;
}

class conseil : public QDialog
{
    Q_OBJECT

public:
    explicit conseil(QWidget *parent = nullptr);
    ~conseil();
    void setLabelText(const QString &text);
    void setLabelTextm(const QString &text);
    void setLabelTextp(const QString &text);
    void setLabelText1(const QString &text);
    void setLabelText2(const QString &text);
    void setLabelText3(const QString &text);
    void setLabelText4(const QString &text);
    void setLabelText5(const QString &text);
    void setLabelText6(const QString &text);
    void setLabelText7(const QString &text);
    void setLabelText8(const QString &text);
private:
    Ui::conseil *ui;
};

#endif // CONSEIL_H
