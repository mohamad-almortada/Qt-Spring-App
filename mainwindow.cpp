#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Employee management");
    ui->my_table->setColumnCount(8);
    QStringList headerList{"ID","Firstnmae", "Lastname", "Gender", "Age", "Salary", "Entrance", "Birth"};
    ui->my_table->setHorizontalHeaderLabels(headerList);
    ui->comboBoxLoad->addItems({"URL", "Local"});
    ui->filter->setClearButtonEnabled(true);
    ui->filter->setPlaceholderText("Search...");

    // By default those buttons are hidden
    ui->deleteButton->setHidden(true);
    ui->update->setHidden(true);
    ui->refresh->setHidden(true);
    ui->buttonNew->setHidden(true);

    connect(&urlManager, &UrlManager::dataReadyRead, this, &MainWindow::getData);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_clicked() // LOAD
{
    if(ui->comboBoxLoad->currentText() == "URL")
    {
        urlManager.getApi();
        ui->deleteButton->setHidden(false);
        ui->update->setHidden(false);
        ui->buttonNew->setHidden(false);
    }

    else if(ui->comboBoxLoad->currentText() == "Local")
    {
        QString filter = tr("JSON File (*.json)");
        QString filePath = QFileDialog::getOpenFileName(this,"Open a file", "C:/Users/" , filter);
        controllerLocal.setFilePath(filePath);
        showEmployees(controllerLocal.getAll());

        if(controllerLocal.getAll().size() !=0)
        {
            ui->deleteButton->setHidden(false);
            ui->update->setHidden(false);
            ui->refresh->setHidden(false);
        }
    }

    else
        return;
}



void MainWindow::on_buttonNew_clicked()
{

    Dialog addDialog(this);
    addDialog.setWindowTitle("Add a new employee");
    int res = addDialog.exec();
    if(res == QDialog::Rejected) return;


    Employee employee = addDialog.getEmployeeFromDialog();

    if(ui->comboBoxLoad->currentText() == "URL")
        urlManager.createApi(employee);

    else // ---> Local
    {
        controllerLocal.add(employee);
        showEmployees(controllerLocal.getAll());
        ui->refresh->setHidden(false);
    }

    ui->deleteButton->setHidden(false);
    ui->update->setHidden(false);
}

void MainWindow::on_deleteButton_clicked()     // DELETE
{
    bool ok;
    int id = QInputDialog::getInt(this,"Id to delete","Give pelase which id would you delete",1, 0, 54321, 1, &ok);
    if(ok)
    {
        if ( checkOfId(id) == id )
        {
            if ( ui->comboBoxLoad->currentText() == "URL" ) // -->Url
            {
                urlManager.deleteApi(id);
                showEmployees(urlManager.getAll());
                if ( ui->my_table->rowCount() == 0 )
                {
                    ui->deleteButton->setHidden(true);
                    ui->update->setHidden(true);
                }
            }
            else //-->local
            {
                controllerLocal.deleteEmployee(id);
            }
        }
        else
        {
            QMessageBox::critical(this, "~~404~~","please make sure you have appropriate ID");
            on_refresh_clicked();
            on_deleteButton_clicked();
        }
    }
    else return;
}


void MainWindow::on_refresh_clicked()
{

    if (ui->comboBoxLoad->currentText() == "Local")
        showEmployees(controllerLocal.getAll());
    else
    {
         urlManager.getApi();
         showEmployees(urlManager.getAll());
    }
}

void MainWindow::on_update_clicked() // UPDATE
{
     bool ok;
     int id = QInputDialog::getInt(this,"","Give please below the ID to update",1, 0, 54321, 1, &ok);
     if(ok)
     {
        if(checkOfId(id) == id) // check if id exists in the table after load
        {
            Employee employeeOriginal = getEmployeeFromRow(getRow(id));
            Dialog addDialog(this);
            addDialog.setEmployeeFromDialog(employeeOriginal);
            addDialog.setWindowTitle("Update selected employee");
            addDialog.exec();

            Employee employee = addDialog.getEmployeeFromDialog();
            urlManager.updateApi(id,employee);
        }
        else
        {
            QMessageBox::critical(this, "~~404~~","please make sure you have appropriate ID");
            on_refresh_clicked();
            on_update_clicked();
        }
     }
     else return;
}

Employee MainWindow::getEmployeeFromRow(const int row)
{
    int id = ui->my_table->item(row,0)->text().toInt();
    QString firstname = ui->my_table->item(row,1)->text();
    QString lastname = ui->my_table->item(row,2)->text();
    QString gender = ui->my_table->item(row,3)->text();
    int age = ui->my_table->item(row,4)->text().toInt();
    double salary = ui->my_table->item(row,5)->text().toDouble();
    QDate entrance = QDate::fromString(ui->my_table->item(row,6)->text(),"yyyy-MM-dd");
    QDate birth = QDate::fromString(ui->my_table->item(row,7)->text(),"yyyy-MM-dd");
    qInfo() << entrance << birth;
    return Employee(age, id, salary,firstname, lastname, gender, entrance, birth);
}

int MainWindow::getRow(const int id)
{
    for(int row=0; row < ui->my_table->rowCount(); ++row)
        if( ui->my_table->item(row,0)->text().toInt() == id)
            return row;
    return 0;
}

int MainWindow::checkOfId(const int myId){
    for(int row=0; row < ui->my_table->rowCount(); ++row)
    {
        int id = ui->my_table->item(row,0)->text().toInt();
        if( id == myId)
            return myId;
    }
 return 0;
}

void MainWindow::showEmployees(const QList<Employee>& employees)
{
    ui->my_table->clearContents();
    ui->my_table->setRowCount(0);
    for(int row=0; row < employees.size(); ++row)
    {
        ui->my_table->insertRow(ui->my_table->rowCount());
        ui->my_table->setItem(row, 0, new QTableWidgetItem(QString::number(employees.at(row).getId())));
        ui->my_table->setItem(row, 1, new QTableWidgetItem(employees.at(row).getVorname()));
        ui->my_table->setItem(row, 2, new QTableWidgetItem(employees.at(row).getNachname()));
        ui->my_table->setItem(row, 3, new QTableWidgetItem(employees.at(row).getGeschlecht()));
        ui->my_table->setItem(row, 4, new QTableWidgetItem(QString::number(employees.at(row).getAlter())));
        ui->my_table->setItem(row, 5, new QTableWidgetItem(QString::number(employees.at(row).getGehalt())));
        ui->my_table->setItem(row, 6, new QTableWidgetItem(employees.at(row).getEinritt().toString("yyyy-MM-dd") ));
        ui->my_table->setItem(row, 7, new QTableWidgetItem(employees.at(row).getGeburt().toString("yyyy-MM-dd") ));
     }
}

void MainWindow::setMyState(int state)
{
    if(state == 200)
        ui->label->setText("State: Ok");
    else if (state == 201)
        ui->label->setText("State: created");
    else if (state == 404)
        ui->label->setText("State: not found");
    else
        ui->label->setText("Somethng wrong!");
}

void MainWindow::getData() // can have a QString as parameter
{
    setMyState(urlManager.getState());
    //ui->label->setText(QString::number(urlManager.getState()));
    showEmployees(urlManager.getAll());
    ui->refresh->setHidden(false);
}

void MainWindow::on_filter_textChanged(const QString &arg1) // Search
{
    for(int row = 0; row < ui->my_table->rowCount(); ++row)
    {
        bool matchFilter = false;
        for(int column = 0; column < ui->my_table->columnCount(); ++column)
        if( ui->my_table->item(row,column)->text().contains(arg1) )
        {
            matchFilter = true;
            break;
        }

        ui->my_table->setRowHidden(row, !matchFilter);
    }
}
