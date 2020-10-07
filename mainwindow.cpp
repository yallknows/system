#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString& databaseLogin, const QString& databasePassword, QWidget *parent)
    : QMainWindow(parent), main_ui(new Ui::MainWindow), mDatabaseLogin(databaseLogin), mDatabasePassword(databasePassword)
{
    this->main_ui->setupUi(this);

    mDatabase = QSqlDatabase::addDatabase("QMYSQL", "information_system_data");
    mDatabase.setHostName("localhost");
    mDatabase.setUserName(mDatabaseLogin);
    mDatabase.setPassword(mDatabasePassword);
    mDatabase.setDatabaseName("information_system");

    if (!mDatabase.open())
    {
        this->main_ui->statusbar->showMessage("Failed to connect to database!");
        return;
    }

    this->main_ui->statusbar->showMessage("Database succesfully connected!");
}

MainWindow::~MainWindow()
{
    if (this->main_ui != nullptr)
    {
        delete this->main_ui;
    }

    if (mDatabase.open())
    {
        mDatabase.close();
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
        return;
    }

    this->main_ui->statusbar->showMessage("Database succesfully connected!");

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
        db.close();
        return;
    }

    this->main_ui->statusbar->showMessage("Data succesfully inserted!");

    db.close();
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
        return;
    }

    QSqlQuery query(QSqlDatabase::database("connection"));
    query.prepare("SELECT * FFROM operations WHERE date = :date");

    QString date = "2020-09-13 18:54:24";

    query.bindValue(":date", date);

    if (!query.exec())
    {
        this->main_ui->statusbar->showMessage("Failed to search data!");
        db.close();
        return;
    }

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

    db.close();
}
