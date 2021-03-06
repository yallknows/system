#pragma once

#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include "mainWindow.h"

#include <QDialog>

namespace Ui
{
    class WelcomeWindow;
}

class WelcomeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget* parent = nullptr);
    ~WelcomeWindow();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::WelcomeWindow* mWelcome_ui = nullptr;
    MainWindow* mMainWindow = nullptr;

    QString mHosteName = "localhost", mDatabaseName = "information_system";
};

#endif // WELCOMEWINDOW_H
