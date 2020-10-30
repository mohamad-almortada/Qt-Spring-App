#include "urlmanager.h"


UrlManager::UrlManager(QObject *parent) : QObject(parent)
{
    url = "http://localhost:1111/api/v1/employees/";  //API
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &UrlManager::onFinished);

}



void UrlManager::getApi()
{
    manager->get(makeRequest(url));
}

void UrlManager::getApiById(const int id)
{
    manager->get(makeRequest(url + QString::number(id)));
}

void UrlManager::createApi(const Employee& employee)
{
    QByteArray postData = createStringFromObject(employee).toUtf8();
    manager->post(makeRequest(url),postData);
}

void UrlManager::deleteApi(const int id)
{
    manager->deleteResource(makeRequest(url + QString::number(id)));
}

void UrlManager::updateApi(const int id, const Employee& employee)
{
    QByteArray payload = createStringFromObject(employee).toUtf8();
    manager->put(makeRequest(url+QString::number(id)), payload);
}

                        // ~~~~~~~~~~auxiliary functions~~~~~~~~~~~~~~~

void UrlManager::onFinished(QNetworkReply*reply){
    data = reply->readAll();
    reply->deleteLater();
    QVariant var = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //state = "Status: " + var.toString();
    state = var.toInt();
    emit dataReadyRead();
}


QNetworkRequest UrlManager::makeRequest(QString urlRequest) const
{
    QNetworkRequest request;
    request.setUrl(QUrl(urlRequest));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return request;
}


QString UrlManager::createStringFromObject(const Employee &employee) const
{
    QJsonObject newObject ={
                           {"age",       employee.getAlter()},
                           {"salary",    employee.getGehalt()},
                           {"firstname", employee.getVorname()},
                           {"lastname",  employee.getNachname()},
                           {"gender",    employee.getGeschlecht()},
                           {"entrance",  employee.getEinritt().toString("yyyy-MM-dd")},
                           {"birth",     employee.getGeburt().toString("yyyy-MM-dd")}
                         };

      QJsonDocument doc(newObject);
      QString strJson(doc.toJson(QJsonDocument::Compact));
      return strJson;
}

Employee UrlManager::getEmployeeFromJson(const QJsonObject& o)const{
    int alter = o["age"].toInt();
    int id = o["id"].toInt();
    double gehalt = o["salary"].toDouble();
    QString vor_name = o["firstname"].toString();
    QString nach_name = o["lastname"].toString();
    QString gender = o["gender"].toString();
    QDate eintritt_datum = QDate::fromString(o["entrance"].toString(), "yyyy-MM-dd");
    QDate geburt_datum = QDate::fromString(o["birth"].toString(), "yyyy-MM-dd");
    return Employee( alter, id, gehalt, vor_name, nach_name, gender, eintritt_datum, geburt_datum);
}

QList<Employee> UrlManager::loadApi()const
{
    QList<Employee> employees;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());

    if(jsonDoc.isObject())                                          // List\jsonArray has only one element
        employees.push_back(getEmployeeFromJson(jsonDoc.object()));

     else
    {
        QJsonArray jsonArray = jsonDoc.array();
        for(int i=0;i<jsonArray.count();++i)
            employees.push_back(getEmployeeFromJson(jsonArray[i].toObject()));
    }

    return employees;
}

QList<Employee> UrlManager::getAll()const
{
    return loadApi();
}

int UrlManager::getState() const
{
    return state;
}
