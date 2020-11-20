#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(const QString& hosteName, const QString& databaseLogin, const QString& databasePassword,
    const QString& databaseName, QWidget* parent)
    : QMainWindow(parent), mMain_ui(new Ui::MainWindow), mHosteName(hosteName), mDatabaseLogin(databaseLogin),
      mDatabasePassword(databasePassword), mDatabaseName(databaseName)
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

    mSortFilterProxyModel = new QSortFilterProxyModel();
    mSortFilterProxyModel->setSourceModel(mQueryModel);
    mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
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

    if (mSortFilterProxyModel != nullptr)
    {
        delete mSortFilterProxyModel;
        mSortFilterProxyModel = nullptr;
    }
}

void MainWindow::on_pushButton_update_database_clicked()
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
            mSortFilterProxyModel->setSourceModel(mQueryModel);
        }
        else
        {
            setup_select_all_queryModel(mQueryModel);
            mSortFilterProxyModel->setSourceModel(mQueryModel);
        }

        mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
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
            mSortFilterProxyModel->setSourceModel(mTableModel);
        }
        else
        {
            setup_select_all_tableModel(mTableModel);
            mSortFilterProxyModel->setSourceModel(mTableModel);
        }

        mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
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
            mSortFilterProxyModel->setSourceModel(mTableModel);
        }
        else
        {
            setup_select_all_tableModel(mTableModel);
            mSortFilterProxyModel->setSourceModel(mTableModel);
        }

        mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
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
            mSortFilterProxyModel->setSourceModel(mQueryModel);
        }
        else
        {
            setup_select_all_queryModel(mQueryModel);
            mSortFilterProxyModel->setSourceModel(mQueryModel);
        }

        mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
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
            mSortFilterProxyModel->setSourceModel(mQueryModel);
            mMain_ui->statusbar->showMessage("Found the following entries!");
        }
        else
        {
            setup_select_all_queryModel(mQueryModel);
            mSortFilterProxyModel->setSourceModel(mQueryModel);
            mMain_ui->statusbar->showMessage("Search field is empty!");
        }

        mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
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
            mSortFilterProxyModel->setSourceModel(mTableModel);
            mMain_ui->statusbar->showMessage("Found the following entries!");
        }
        else
        {
            setup_select_all_tableModel(mTableModel);
            mSortFilterProxyModel->setSourceModel(mTableModel);
            mMain_ui->statusbar->showMessage("Search field is empty!");
        }

        mMain_ui->tableView_data_from_database->setModel(mSortFilterProxyModel);
    }
}

void MainWindow::on_pushButton_insert_new_record_clicked()
{
    if (mAddNewItemWindow != nullptr)
    {
        delete mAddNewItemWindow;
        mAddNewItemWindow = nullptr;
    }

    QString payer, receiver, payerAccount, receiverAccount, sum, date;

    mAddNewItemWindow = new AddNewItemWindow(mHosteName, mDatabaseLogin, mDatabasePassword, mDatabaseName);
    mAddNewItemWindow->show();

    mMain_ui->statusbar->showMessage("Refresh the connection!");
}

void MainWindow::on_pushButton_delete_selected_item_clicked()
{
    if (!mMain_ui->tableView_data_from_database->selectionModel()->hasSelection())
    {
        mMain_ui->statusbar->showMessage("Select the item to remove!");
        return;
    }

    QModelIndexList selection = mMain_ui->tableView_data_from_database->selectionModel()->selectedRows();
    QModelIndex selectedIndex = selection.at(0);
    QString removableId = mMain_ui->tableView_data_from_database->model()->index(selectedIndex.row(), 0).data().toString();

    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM `operations` WHERE operation_id='" + removableId + "'");

    if (!query.exec())
    {
        mMain_ui->statusbar->showMessage("Failed to delete item!");
    }
    else
    {
        on_pushButton_update_database_clicked();
        mMain_ui->statusbar->showMessage("Item deleted successfully!");
    }
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
