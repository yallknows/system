#include "addNewItemWindow.h"
#include "ui_addNewItemWindow.h"

AddNewItemWindow::AddNewItemWindow(const QString& hosteName, const QString& databaseLogin,
    const QString& databasePassword, const QString& databaseName, QWidget* parent)
    : QDialog(parent), mAddNewItem_ui(new Ui::AddNewItemWindow)
{
    mAddNewItem_ui->setupUi(this);

    mDatabase = QSqlDatabase::addDatabase("QMYSQL", "information_system_add_new_item");
    mDatabase.setHostName(hosteName);
    mDatabase.setUserName(databaseLogin);
    mDatabase.setPassword(databasePassword);
    mDatabase.setDatabaseName(databaseName);

    if (!mDatabase.open())
    {
        mAddNewItem_ui->label_statusbar->setText("Failed to connect to database!");
        return;
    }

    mAddNewItem_ui->label_statusbar->setText("Database succesfully connected!");
}

AddNewItemWindow::~AddNewItemWindow()
{
    if (mAddNewItem_ui != nullptr)
    {
        delete mAddNewItem_ui;
        mAddNewItem_ui = nullptr;
    }

    if (mDatabase.open())
    {
        mDatabase.close();
    }
}

void AddNewItemWindow::on_pushButton_addItem_clicked()
{
    QString payer = mAddNewItem_ui->lineEdit_payer->text(), receiver = mAddNewItem_ui->lineEdit_receiver->text(),
    payerAccount = mAddNewItem_ui->lineEdit_payerAccount->text(), receiverAccount = mAddNewItem_ui->lineEdit_receiverAccount->text(),
    sum = mAddNewItem_ui->lineEdit_sum->text(), date = mAddNewItem_ui->dateTimeEdit_date->text();

    if (payer.size() == 0)
    {
        mAddNewItem_ui->label_statusbar->setText("Payer field is empty!");
        return;
    }

    if (receiver.size() == 0)
    {
        mAddNewItem_ui->label_statusbar->setText("Receiver field is empty!");
        return;
    }

    if (payerAccount.size() == 0)
    {
        mAddNewItem_ui->label_statusbar->setText("Payer account field is empty!");
        return;
    }

    if (receiverAccount.size() == 0)
    {
        mAddNewItem_ui->label_statusbar->setText("Receiver account field is empty!");
        return;
    }

    if (sum.size() == 0)
    {
        mAddNewItem_ui->label_statusbar->setText("Sum field is empty!");
        return;
    }

    if (date.size() == 0)
    {
        mAddNewItem_ui->label_statusbar->setText("Date field is empty!");
        return;
    }

    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO operations (payer_name, receiver_name, source_number,"
        " destination_number, sum, date_time) VALUES (?, ?, ?, ?, ?, ?)");

    query.addBindValue(payer);
    query.addBindValue(receiver);
    query.addBindValue(payerAccount);
    query.addBindValue(receiverAccount);
    query.addBindValue(std::stod(sum.toStdString()));
    query.addBindValue(QDateTime::fromString(date, "yyyy-MM-dd H:mm:ss"));

    if (!query.exec())
    {
        mAddNewItem_ui->label_statusbar->setText("Error while adding!");
    }
    else
    {
        mAddNewItem_ui->label_statusbar->setText("Item added successfully!");

        mAddNewItem_ui->lineEdit_payer->setText("");
        mAddNewItem_ui->lineEdit_receiver->setText("");
        mAddNewItem_ui->lineEdit_payerAccount->setText("");
        mAddNewItem_ui->lineEdit_receiverAccount->setText("");
        mAddNewItem_ui->lineEdit_sum->setText("");
    }
}

void AddNewItemWindow::on_pushButton_cancel_clicked()
{
    close();

    if (mAddNewItem_ui != nullptr)
    {
        delete mAddNewItem_ui;
        mAddNewItem_ui = nullptr;
    }

    if (mDatabase.open())
    {
        mDatabase.close();
    }
}
