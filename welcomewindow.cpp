#include "welcomewindow.h"
#include "ui_welcomewindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QDialog(parent), welcome_ui(new Ui::WelcomeWindow)
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
    this->hide();
    this->mMainWindow = new MainWindow;
    this->mMainWindow->show();
}

void WelcomeWindow::on_pushButton_show_text_clicked()
{
    this->welcome_ui->label_statusbar->setText("Check it out!");
}
