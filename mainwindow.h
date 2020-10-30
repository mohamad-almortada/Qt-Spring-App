#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employee.h"
#include "controller.h"
#include "urlmanager.h"

#include <QList>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_load_clicked();
    void on_refresh_clicked();
    void on_filter_textChanged(const QString &arg1);
    void on_buttonNew_clicked();
    void getData();
    void on_deleteButton_clicked();
    void on_update_clicked();



private:
    Ui::MainWindow *ui;
    Controller controllerLocal;
    UrlManager urlManager;


    void showEmployees(const QList<Employee>&);
    int checkOfId(const int);
    Employee getEmployeeFromRow(const int);
    int getRow(const int);
    void setMyState(int);
};
#endif // MAINWINDOW_H



