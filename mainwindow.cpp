#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), main_ui(new Ui::MainWindow)
{
    this->main_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if (this->main_ui != nullptr)
    {
        delete this->main_ui;
    }
}

void MainWindow::on_pushButton_database_connection_check_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "check");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("system");

    if (db.open())
    {
        this->main_ui->statusbar->showMessage("Database succesfully connected!");
        db.close();
    }
    else
    {
        this->main_ui->statusbar->showMessage("Failed to connect to database!");
    }
}

void MainWindow::on_pushButton_insert_to_database_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "connection");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("system");

    if (!db.open())
    {
        this->main_ui->statusbar->showMessage("Failed to connect to database!");
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database("connection"));
        query.prepare("SELECT * FFROM operations WHERE client_code = :client_code AND"
                      "employee_code = :employee_code AND cost = :cost AND date = :date");

        query.bindValue(":client_code", "11");
        query.bindValue(":employee_code", "1");
        query.bindValue(":cost", "53.12");
        query.bindValue(":date", "2020-09-16 12:14:54");

        if (!query.exec())
        {
            this->main_ui->statusbar->showMessage("Failed to insert data!");
        }
        else
        {
            this->main_ui->statusbar->showMessage("Data succesfully inserted!");
        }

        db.close();
    }
}

void MainWindow::on_pushButton_search_in_database_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "connection");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("system");

    if (!db.open())
    {
        this->main_ui->statusbar->showMessage("Failed to connect to database!");
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database("connection"));
        query.prepare("SELECT * FFROM operations WHERE date = :date");

        QString date = "2020-09-13 18:54:24";

        query.bindValue(":date", date);

        if (!query.exec())
        {
            this->main_ui->statusbar->showMessage("Failed to search data!");
        }
        else
        {
            while (query.next())
            {
                QString dateFromDB = query.value(1).toString();

                if (dateFromDB != date)
                {
                    this->main_ui->statusbar->showMessage("Failed to find data!");
                }
                else
                {
                    this->main_ui->statusbar->showMessage("Data succesfully founded!");
                }
            }
        }

        db.close();
    }
}
