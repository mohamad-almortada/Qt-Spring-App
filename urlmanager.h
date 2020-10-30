#ifndef URLMANAGER_H
#define URLMANAGER_H

#include "employee.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class UrlManager : public QObject
{
    Q_OBJECT
public:
    explicit UrlManager(QObject *parent = nullptr);
    // CRUD
    void createApi(const Employee&);
    void getApi();
    void getApiById(const int);
    void deleteApi(const int);
    void updateApi(const int,const Employee&);


    QList<Employee> getAll()const;
    int getState()const;

signals:
    void dataReadyRead(); // QString as parameter (_alternative_)

public slots:
    void onFinished(QNetworkReply*);

private:
    QNetworkAccessManager* manager;
    QString data;
    QString url;
    int state;

    QList<Employee> loadApi()const;
    QString createStringFromObject(const Employee&)const;
    QNetworkRequest makeRequest(QString)const;
    Employee getEmployeeFromJson(const QJsonObject&)const;
};

#endif // URLMANAGER_H
