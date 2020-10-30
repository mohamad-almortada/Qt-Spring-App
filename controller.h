#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "employee.h"

#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class Controller
{
private:
    QString filePath;
    QList<Employee> loadFile()const;
    void saveFile(const QList<Employee>&);

public:
    Controller();
    void setFilePath(const QString& filePathName);
    QList<Employee> getAll()const;
    void add(Employee&);
    void updateEmployee(const int id);
    void deleteEmployee(const int deleteCriteria);

};

#endif // CONTROLLER_H
