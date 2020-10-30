#include "employee.h"

Employee::Employee() { }

QString Employee::getVorname() const
{
    return vorname;
}

QString Employee::getNachname() const
{
    return nachname;
}

QString Employee::getGeschlecht() const
{
    return geschlecht;
}

int Employee::getAlter() const
{
    return alter;
}

int Employee::getId()const
{
    return id;
}

double Employee::getGehalt() const
{
    return gehalt;
}

QDate Employee::getEinritt() const
{
    return eintrittsdatum;
}

QDate Employee::getGeburt() const
{
    return geburtsdatum;
}

void Employee::setId(int newId)
{
    id = newId;
}

Employee::Employee(int alt, int i, double geh,
                   QString vor, QString nach, QString gesch,
                   QDate ein, QDate geb) : id(i), alter(alt),
                   gehalt(geh), vorname(vor), nachname(nach),
                   geburtsdatum(geb), eintrittsdatum(ein),
                   geschlecht(gesch)  { }
