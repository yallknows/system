#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString& databaseLogin, const QString& databasePassword, QWidget* parent)
    : QMainWindow(parent), mMain_ui(new Ui::MainWindow), mDatabaseLogin(databaseLogin), mDatabasePassword(databasePassword)
{
    mMain_ui->setupUi(this);

    mDatabase = QSqlDatabase::addDatabase("QMYSQL", "information_system_data");
    mDatabase.setHostName("localhost");
    mDatabase.setUserName(mDatabaseLogin);
    mDatabase.setPassword(mDatabasePassword);
    mDatabase.setDatabaseName("information_system");

    if (!mDatabase.open())
    {
        mMain_ui->statusbar->showMessage("Failed to connect to database!");
        return;
    }

    mMain_ui->statusbar->showMessage("Database succesfully connected!");

    mQueryModel = new QSqlQueryModel();
    mQueryModel->setQuery("SELECT * FROM `operations`", mDatabase);

    mQueryModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    mQueryModel->setHeaderData(1, Qt::Horizontal, tr("From"));
    mQueryModel->setHeaderData(2, Qt::Horizontal, tr("To"));
    mQueryModel->setHeaderData(3, Qt::Horizontal, tr("Sum"));
    mQueryModel->setHeaderData(4, Qt::Horizontal, tr("Date"));

    mMain_ui->tableView_data_from_database->setModel(mQueryModel);
}

MainWindow::~MainWindow()
{
    if (mMain_ui != nullptr)
    {
        delete mMain_ui;
        mMain_ui = nullptr;
    }

    if (mDatabase.open())
    {
        mDatabase.close();
    }

    if (mQueryModel != nullptr)
    {
        delete mQueryModel;
        mQueryModel = nullptr;
    }

    if (mTableModel != nullptr)
    {
        delete mTableModel;
        mTableModel = nullptr;
    }
}

void MainWindow::on_pushButton_retry_database_connection_clicked()
{
    if (mDatabase.open())
    {
        mDatabase.close();
    }

    mDatabase = QSqlDatabase::addDatabase("QMYSQL", "information_system_data");
    mDatabase.setHostName("localhost");
    mDatabase.setUserName(mDatabaseLogin);
    mDatabase.setPassword(mDatabasePassword);
    mDatabase.setDatabaseName("information_system");

    if (!mDatabase.open())
    {
        mMain_ui->statusbar->showMessage("Failed to connect to database!");
        return;
    }

    mMain_ui->statusbar->showMessage("Database succesfully connected!");

    if (mMain_ui->label_current_mode->text() == "You are using reading mode.")
    {
        if (mQueryModel != nullptr)
        {
            delete mQueryModel;
            mQueryModel = nullptr;
        }

        mQueryModel = new QSqlQueryModel();
        mQueryModel->setQuery("SELECT * FROM `operations`", mDatabase);

        mQueryModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
        mQueryModel->setHeaderData(1, Qt::Horizontal, tr("From"));
        mQueryModel->setHeaderData(2, Qt::Horizontal, tr("To"));
        mQueryModel->setHeaderData(3, Qt::Horizontal, tr("Sum"));
        mQueryModel->setHeaderData(4, Qt::Horizontal, tr("Date"));

        mMain_ui->tableView_data_from_database->setModel(mQueryModel);
    }
    else if (mMain_ui->label_current_mode->text() == "You are using edit mode.")
    {
        if (mTableModel != nullptr)
        {
            delete mTableModel;
            mTableModel = nullptr;
        }

        mTableModel = new QSqlTableModel(nullptr, mDatabase);
        mTableModel->setTable("`operations`");
        mTableModel->select();

        mTableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
        mTableModel->setHeaderData(1, Qt::Horizontal, tr("From"));
        mTableModel->setHeaderData(2, Qt::Horizontal, tr("To"));
        mTableModel->setHeaderData(3, Qt::Horizontal, tr("Sum"));
        mTableModel->setHeaderData(4, Qt::Horizontal, tr("Date"));

        mMain_ui->tableView_data_from_database->setModel(mTableModel);
    }
}

void MainWindow::on_pushButton_change_mode_clicked()
{
    if (mMain_ui->label_current_mode->text() == "You are using reading mode.")
    {
        if (mQueryModel != nullptr)
        {
            delete mQueryModel;
            mQueryModel = nullptr;
        }

        mTableModel = new QSqlTableModel(nullptr, mDatabase);
        mTableModel->setTable("`operations`");
        mTableModel->select();

        mTableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
        mTableModel->setHeaderData(1, Qt::Horizontal, tr("From"));
        mTableModel->setHeaderData(2, Qt::Horizontal, tr("To"));
        mTableModel->setHeaderData(3, Qt::Horizontal, tr("Sum"));
        mTableModel->setHeaderData(4, Qt::Horizontal, tr("Date"));

        mMain_ui->tableView_data_from_database->setModel(mTableModel);

        mMain_ui->label_current_mode->setText("You are using edit mode.");
    }
    else if (mMain_ui->label_current_mode->text() == "You are using edit mode.")
    {
        if (mTableModel != nullptr)
        {
            delete mTableModel;
            mTableModel = nullptr;
        }

        mQueryModel = new QSqlQueryModel();
        mQueryModel->setQuery("SELECT * FROM `operations`", mDatabase);

        mQueryModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
        mQueryModel->setHeaderData(1, Qt::Horizontal, tr("From"));
        mQueryModel->setHeaderData(2, Qt::Horizontal, tr("To"));
        mQueryModel->setHeaderData(3, Qt::Horizontal, tr("Sum"));
        mQueryModel->setHeaderData(4, Qt::Horizontal, tr("Date"));

        mMain_ui->tableView_data_from_database->setModel(mQueryModel);

        mMain_ui->label_current_mode->setText("You are using reading mode.");
    }
}
