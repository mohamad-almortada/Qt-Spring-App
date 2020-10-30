#ifndef DIALOG_H
#define DIALOG_H

#include "employee.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    double getGehalt()const;
    QString getVorname()const;
    QString getNachname()const;
    QString getGender()const;
    QDate getEintritt()const;
    QDate getGeburt()const;
    Employee getEmployeeFromDialog();
    void setEmployeeFromDialog(const Employee&);


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
