#include "welcomewindow.h"
#include "ui_welcomewindow.h"

#include <QtSql>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QDialog(parent), welcome_ui(new Ui::WelcomeWindow)
{
    this->welcome_ui->setupUi(this);
}

WelcomeWindow::~WelcomeWindow()
{
    if (this->welcome_ui != nullptr)
    {
        delete this->welcome_ui;
    }

    if (this->mMainWindow != nullptr)
    {
        delete this->mMainWindow;
    }
}

void WelcomeWindow::on_pushButton_login_clicked()
{
    QString login = this->welcome_ui->lineEdit_username->text(),
            password = this->welcome_ui->lineEdit_password->text();

    if (login.size() == 0)
    {
        this->welcome_ui->label_statusbar->setText("Login field is empty!");
        return;
    }

    if (password.size() == 0)
    {
        this->welcome_ui->label_statusbar->setText("Password field is empty!");
        return;
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL", "information_system_login");
    database.setHostName("localhost");
    database.setUserName(login);
    database.setPassword(password);
    database.setDatabaseName("information_system");

    if (!database.open())
    {
        this->welcome_ui->label_statusbar->setText("Failed to connect to database!");
        return;
    }

    database.close();

    this->hide();
    this->mMainWindow = new MainWindow(login, password);
    this->mMainWindow->show();
}
