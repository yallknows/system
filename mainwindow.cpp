#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        ui->statusbar->showMessage("Database succesfully connected!");
        db.close();
    }
    else
    {
        ui->statusbar->showMessage("Failed to connect to database!");
    }
}

//system("systeminfo >> text.txt"); // Windows
