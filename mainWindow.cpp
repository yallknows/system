#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(const QString& databaseLogin, const QString& databasePassword, QWidget* parent)
    : QMainWindow(parent), mMain_ui(new Ui::MainWindow), mDatabaseLogin(databaseLogin), mDatabasePassword(databasePassword)
{
    mMain_ui->setupUi(this);

    mDatabase = QSqlDatabase::addDatabase("QMYSQL", "information_system_data");
    mDatabase.setHostName(mHosteName);
    mDatabase.setUserName(mDatabaseLogin);
    mDatabase.setPassword(mDatabasePassword);
    mDatabase.setDatabaseName(mDatabaseName);

    if (!mDatabase.open())
    {
        mMain_ui->statusbar->showMessage("Failed to connect to database!");
        return;
    }

    mMain_ui->statusbar->showMessage("Database succesfully connected!");

    mQueryModel = new QSqlQueryModel();
    setup_select_all_queryModel(mQueryModel);
    mMain_ui->tableView_data_from_database->setModel(mQueryModel);
}

MainWindow::~MainWindow()
{
    if (mMain_ui != nullptr)
    {
        delete mMain_ui;
        mMain_ui = nullptr;
    }

    if (mAddNewItemWindow != nullptr)
    {
        delete mAddNewItemWindow;
        mAddNewItemWindow = nullptr;
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
    mDatabase.setHostName(mHosteName);
    mDatabase.setUserName(mDatabaseLogin);
    mDatabase.setPassword(mDatabasePassword);
    mDatabase.setDatabaseName(mDatabaseName);

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

        QString searchRequest = mMain_ui->lineEdit_search_request->text();

        if (searchRequest.size() > 0)
        {
            setup_search_queryModel(mQueryModel, searchRequest);
        }
        else
        {
            setup_select_all_queryModel(mQueryModel);
        }

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

        QString searchRequest = mMain_ui->lineEdit_search_request->text();

        if (searchRequest.size() > 0)
        {
            setup_search_tableModel(mTableModel, searchRequest);
        }
        else
        {
            setup_select_all_tableModel(mTableModel);
        }

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

        QString searchRequest = mMain_ui->lineEdit_search_request->text();

        if (searchRequest.size() > 0)
        {
            setup_search_tableModel(mTableModel, searchRequest);
        }
        else
        {
            setup_select_all_tableModel(mTableModel);
        }

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

        QString searchRequest = mMain_ui->lineEdit_search_request->text();

        if (searchRequest.size() > 0)
        {
            setup_search_queryModel(mQueryModel, searchRequest);
        }
        else
        {
            setup_select_all_queryModel(mQueryModel);
        }

        mMain_ui->tableView_data_from_database->setModel(mQueryModel);
        mMain_ui->label_current_mode->setText("You are using reading mode.");
    }

    mMain_ui->statusbar->showMessage("Mode changed!");
}

void MainWindow::on_pushButton_search_clicked()
{
    if (mMain_ui->label_current_mode->text() == "You are using reading mode.")
    {
        if (mQueryModel != nullptr)
        {
            delete mQueryModel;
            mQueryModel = nullptr;
        }

        mQueryModel = new QSqlQueryModel();

        QString searchRequest = mMain_ui->lineEdit_search_request->text();

        if (searchRequest.size() > 0)
        {
            setup_search_queryModel(mQueryModel, searchRequest);
            mMain_ui->statusbar->showMessage("Found the following entries!");
        }
        else
        {
            setup_select_all_queryModel(mQueryModel);
            mMain_ui->statusbar->showMessage("Search field is empty!");
        }

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

        QString searchRequest = mMain_ui->lineEdit_search_request->text();

        if (searchRequest.size() > 0)
        {
            setup_search_tableModel(mTableModel, searchRequest);
            mMain_ui->statusbar->showMessage("Found the following entries!");
        }
        else
        {
            setup_select_all_tableModel(mTableModel);
            mMain_ui->statusbar->showMessage("Search field is empty!");
        }

        mMain_ui->tableView_data_from_database->setModel(mTableModel);
    }
}

void MainWindow::on_pushButton_insert_new_record_clicked()
{
    if (mAddNewItemWindow != nullptr)
    {
        delete mAddNewItemWindow;
        mAddNewItemWindow = nullptr;
    }

    mAddNewItemWindow = new AddNewItemWindow;
    mAddNewItemWindow->show();
}

void MainWindow::setup_select_all_queryModel(QSqlQueryModel* const queryModel) const
{
    queryModel->setQuery("SELECT * FROM `operations`", mDatabase);
    setup_headers_queryModel(queryModel);
}

void MainWindow::setup_select_all_tableModel(QSqlTableModel* const tableModel) const
{
    tableModel->setTable("`operations`");
    tableModel->select();
    setup_headers_tableModel(tableModel);
}

void MainWindow::setup_search_queryModel(QSqlQueryModel* const queryModel, const QString& searchRequest) const
{
    queryModel->setQuery("SELECT * FROM `operations` WHERE operation_id = '" + searchRequest + "' OR payer_name = '" + searchRequest +
        "' OR receiver_name = '" + searchRequest + "' OR source_number = '" + searchRequest + "' OR destination_number = '" + searchRequest +
        "' OR sum = '" + searchRequest + "' OR date_time = '" + searchRequest + "'", mDatabase);
    setup_headers_queryModel(queryModel);
}

void MainWindow::setup_search_tableModel(QSqlTableModel* const tableModel, const QString& searchRequest) const
{
    tableModel->setTable("`operations`");
    tableModel->setFilter("operation_id = '" + searchRequest + "' OR payer_name = '" + searchRequest + "' OR receiver_name = '" + searchRequest +
    "' OR source_number = '" + searchRequest + "' OR destination_number = '" + searchRequest + "' OR sum = '" + searchRequest +
    "' OR date_time = '" + searchRequest + "'");
    tableModel->select();
    setup_headers_tableModel(tableModel);
}

void MainWindow::setup_headers_queryModel(QSqlQueryModel* const queryModel) const
{
    queryModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Payer"));
    queryModel->setHeaderData(2, Qt::Horizontal, tr("Receiver"));
    queryModel->setHeaderData(3, Qt::Horizontal, tr("Payer account"));
    queryModel->setHeaderData(4, Qt::Horizontal, tr("Reciever account"));
    queryModel->setHeaderData(5, Qt::Horizontal, tr("Sum"));
    queryModel->setHeaderData(6, Qt::Horizontal, tr("Date"));
}

void MainWindow::setup_headers_tableModel(QSqlTableModel* const tableModel) const
{
    tableModel->setHeaderData(0, Qt::Horizontal, tr("Id"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Payer"));
    tableModel->setHeaderData(2, Qt::Horizontal, tr("Receiver"));
    tableModel->setHeaderData(3, Qt::Horizontal, tr("Payer account"));
    tableModel->setHeaderData(4, Qt::Horizontal, tr("Reciever account"));
    tableModel->setHeaderData(5, Qt::Horizontal, tr("Sum"));
    tableModel->setHeaderData(6, Qt::Horizontal, tr("Date"));
}
