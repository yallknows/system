#include "welcomeWindow.h"
#include "ui_welcomeWindow.h"

#include <QtSql>

WelcomeWindow::WelcomeWindow(QWidget* parent)
    : QDialog(parent), mWelcome_ui(new Ui::WelcomeWindow)
{
    mWelcome_ui->setupUi(this);
}

WelcomeWindow::~WelcomeWindow()
{
    if (mWelcome_ui != nullptr)
    {
        delete mWelcome_ui;
        mWelcome_ui = nullptr;
    }

    if (mMainWindow != nullptr)
    {
        delete mMainWindow;
        mMainWindow = nullptr;
    }
}

void WelcomeWindow::on_pushButton_login_clicked()
{
    QString login = mWelcome_ui->lineEdit_username->text(),
            password = mWelcome_ui->lineEdit_password->text();

    if (login.size() == 0)
    {
        mWelcome_ui->label_statusbar->setText("Login field is empty!");
        return;
    }

    if (password.size() == 0)
    {
        mWelcome_ui->label_statusbar->setText("Password field is empty!");
        return;
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL", "information_system_login");
    database.setHostName(mHosteName);
    database.setUserName(login);
    database.setPassword(password);
    database.setDatabaseName(mDatabaseName);

    if (!database.open())
    {
        mWelcome_ui->label_statusbar->setText("Failed to connect to database!");
        return;
    }

    database.close();
    close();

    mMainWindow = new MainWindow(mHosteName, login, password, mDatabaseName);
    mMainWindow->show();

    if (mWelcome_ui != nullptr)
    {
        delete mWelcome_ui;
        mWelcome_ui = nullptr;
    }
}
