#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& databaseLogin, const QString& databasePassword, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_insert_to_database_clicked();

    void on_pushButton_search_in_database_clicked();

private:
    Ui::MainWindow *main_ui = nullptr;

    QString mDatabaseLogin, mDatabasePassword;
    QSqlDatabase mDatabase;
};

#endif // MAINWINDOW_H
