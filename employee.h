#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDate>
#include <QString>

class Employee
{
public:
    Employee();
    Employee(int alt, int i, double geh, QString vor, QString nach, QString gesch, QDate ein, QDate geb);
    QString getVorname()const;
    QString getNachname()const;
    QString getGeschlecht()const;
    int getAlter()const;
    int getId()const;
    double getGehalt()const;
    QDate getEinritt()const;
    QDate getGeburt()const;
    //QString getTel()const;
    void setId(int);
    operator QString(); // converter from object(Employee) to QString.

private:
    int id;
    int alter;
    double gehalt;
    QString vorname;
    QString nachname;
    QDate geburtsdatum;
    QDate eintrittsdatum;
    QString geschlecht;
    //QString tel;
};

#endif // EMPLOYEE_H
