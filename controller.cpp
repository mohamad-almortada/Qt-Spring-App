#include "controller.h"

Controller::Controller(){ }

QList<Employee> Controller::loadFile() const
{
    QList<Employee> employees;

    QFile jsonFile(filePath);
    jsonFile.open(QIODevice::ReadOnly);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonFile.readAll());
    jsonFile.close();

    QJsonArray jsonArray = jsonDoc.array();
    for(int i=0;i<jsonArray.count();++i)
    {
        QJsonObject o = jsonArray[i].toObject();
        int alter = o["age"].toInt();
        int id = o["id"].toInt();
        double gehalt = o["salary"].toDouble();
        QString vor_name = o["firstname"].toString();
        QString nach_name = o["lastname"].toString();
        QString gender = o["gender"].toString();
        //QString number = o["tel"].toString();
        QDate eintritt_datum = QDate::fromString(o["entrance"].toString(), "yyyy-MM-dd");
        QDate geburt_datum = QDate::fromString(o["birth"].toString(), "yyyy-MM-dd");
        employees.push_back(Employee( alter, id, gehalt, vor_name, nach_name, gender, eintritt_datum, geburt_datum));
    }

    return employees;
}

void Controller::saveFile(const QList<Employee> &employees)
{
     QJsonArray jsonArray;

    for(int index=0; index < employees.size(); ++index)
    {
           QJsonObject newObject ={
                                  {"id", employees.at(index).getId()},
                                  {"age", employees.at(index).getAlter()},
                                  {"salary", employees.at(index).getGehalt()},
                                  {"firstname",employees.at(index).getVorname()},
                                  {"lastname",employees.at(index).getNachname()},
                                  {"gender",employees.at(index).getGeschlecht()},
                                  {"entrance",employees.at(index).getEinritt().toString("yyyy-MM-dd")},
                                  {"birth",employees.at(index).getGeburt().toString("yyyy-MM-dd")}
                                };

           jsonArray.push_back(newObject);
    }

    QJsonDocument json(jsonArray);
    QFile jsonFile(filePath);
    jsonFile.open(QIODevice::WriteOnly);
    jsonFile.write(json.toJson());
    jsonFile.close();
}

void Controller::setFilePath(const QString& fileName)
{
    this->filePath = fileName;
}

void Controller::add(Employee &employee)
{
    int maxId{0};
    QList<Employee> employees = loadFile();
    for(auto employee : employees)
    {
        if(maxId < employee.getId())
        {
            maxId = employee.getId();
        }
    }
    employee.setId(++maxId);

    employees.push_back(employee);
    saveFile(employees);
}

void Controller::updateEmployee(const int id)
{
    QList<Employee> employees = loadFile();

    for(int index=0; index < employees.size(); ++index)
        if ( id == employees.at(index).getId() )
            employees.replace(index, employees.at(index));

  saveFile(employees);
}

void Controller::deleteEmployee(const int deleteCriteria)
{
    QList<Employee> employees = loadFile();

    for(int index=0; index < employees.size(); ++index)
        if ( deleteCriteria == employees.at(index).getId() )
            employees.removeAt(index);

  saveFile(employees);
}

QList<Employee> Controller::getAll() const
{
    return loadFile();
}

