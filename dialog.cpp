#include "dialog.h"
#include "ui_dialog.h"

#include <QDate>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->birth_date->setDate(QDate(1990,01,01));
    ui->birth_date->setMaximumDate(QDate(2002,12,31));
    ui->entry_date->setDate(QDate::currentDate());
    ui->entry_date->setMaximumDate(QDate::currentDate());
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonBox_accepted()
{
   accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}


QString Dialog::getVorname()const{
    return ui->mName->text();
}

QString Dialog::getNachname() const{
    return ui->nach_name->text();
}


double Dialog::getGehalt() const{
    return ui->mGehalt->value();
}

QDate Dialog::getGeburt() const{
    return ui->birth_date->date();
}


Employee Dialog::getEmployeeFromDialog()
{
    // Age evaluation
    QDate heute = QDate::currentDate();
    int current_age = heute.year() - getGeburt().year();
    if( (getGeburt().month() > heute.month() ) || ( getGeburt().month() == heute.month()  && getGeburt().day() > heute.day()) )
        current_age -=1;
    return Employee(current_age, 0, getGehalt(), getVorname(), getNachname(), getGender(), getEintritt(), getGeburt());
}

void Dialog::setEmployeeFromDialog(const Employee& employee)
{
    ui->nach_name->setText(employee.getNachname());
    ui->mName->setText(employee.getVorname());
    ui->mGehalt->setValue(employee.getGehalt());
    ui->birth_date->setDate(employee.getGeburt());
    ui->entry_date->setDate(employee.getEinritt());

    QString gen = employee.getGeschlecht();
    if ( gen == "male") ui->male_button->setChecked(true);
    else if(gen == "female") ui->female_button->setChecked(true);
    else if (gen == "other") ui->andere_button->setChecked(true);
    else
    {
        ui->male_button->setChecked(false);
        ui->female_button->setChecked(false);
        ui->female_button->setChecked(false);
    }

}

QDate Dialog::getEintritt() const{
    return ui->entry_date->date();
}

QString Dialog::getGender() const{
    if(ui->male_button->isChecked()) return "male";
    else if(ui->female_button->isChecked()) return "female";
    else return "other";
}

